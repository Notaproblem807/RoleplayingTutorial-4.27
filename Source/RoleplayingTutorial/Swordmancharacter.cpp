// Fill out your copyright notice in the Description page of Project Settings.


#include "Swordmancharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Baseweapon.h"
#include "TimerManager.h"
#include "thirdroleGameInstance.h"
#include "manahud.h"
#include "Swordmainhud.h"
#include "Mainbossenemy.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
ASwordmancharacter::ASwordmancharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//default constructor in FAttachtransformrule attached to constructor
	//setup finished for spawn weapon
	//for ability1 in swordman in initialization
	swordslash = false;

	//health and mana initializtion
	Health = 0.5f;
	Mana = 0.4f;

	//initializing cooldown in the hud
	sword1cooldown = 1.0f;
	sword2cooldown = 1.0f;

	//boss fight initialization
	Bosscollider = CreateDefaultSubobject<USphereComponent>(TEXT("bosscollider"));
	Bosscollider->SetupAttachment(GetRootComponent());

	//boss fight stats
	//setting stimuli
	setupstimuli();
	
}

// Called when the game starts or when spawned
void ASwordmancharacter::BeginPlay()
{
	Super::BeginPlay();
	//to spawnn weapon properties
	attachweapon();
	//hud to show in view port
	UthirdroleGameInstance* swordgameinstance = Cast<UthirdroleGameInstance>(GetGameInstance());
	if (setupswordhud) {
		swordhudref = CreateWidget<USwordmainhud>(swordgameinstance, setupswordhud);
	}
	swordhudref->AddToViewport();
	//boss coliided function to execute

	

	
}

// Called every frame
void ASwordmancharacter::Tick(float  DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//timer to regenarate haeath and mana
	GetWorldTimerManager().SetTimerForNextTick(this, &ASwordmancharacter::healthmanaregen);
	//jump animation initialization
	swordinair = GetCharacterMovement()->IsFalling();
	if (swordinair) {
		UE_LOG(LogTemp, Warning, TEXT("not in air"));
	}
	//boss stats
}

// Called to bind functionality to input
void ASwordmancharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASwordmancharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASwordmancharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASwordmancharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASwordmancharacter::LookUpAtRate);

	//ability1 setup
	PlayerInputComponent->BindAction("swordability1",IE_Pressed,this, &ASwordmancharacter::ability1press);



}

void ASwordmancharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASwordmancharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASwordmancharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASwordmancharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASwordmancharacter::attachweapon()
{
	Weaponloc = GetMesh()->GetSocketLocation(FName("weaponholding"));
	weaponref = GetWorld()->SpawnActor<ABaseweapon>(subweaponspawn, Weaponloc, GetActorRotation(), weaponparam);
	weaponref->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("weaponholding"));
}


void ASwordmancharacter::ability1press()
{
	if ((!swordslash )&& (sword1cooldown==1.0f)) {
		//off the disable and stop movement to play ability1 slash word to swing in while running
		//GetCharacterMovement()->DisableMovement();
		//GetCharacterMovement()->StopMovementImmediately();
		swordslash = true;
		UE_LOG(LogTemp, Warning, TEXT("Works in swordslash"));
		sword1cooldown = 0.f;

		//delay time is animation seconds
		GetWorldTimerManager().SetTimer(ability1delay,this,&ASwordmancharacter::ability1delayfunc,1.0f, false, 0.9f);
		
		//delay timer to regenarate the cooldown func
		if (sword1cooldown < 1.f) {
			GetWorldTimerManager().SetTimer(sword1time, this, &ASwordmancharacter::sword1regen, 1.0f, true, 0.5);
		}
	}
}

//delay function for the ability1 animation to finish;
void ASwordmancharacter::ability1delayfunc()
{
	//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking, 0);
	swordslash = false;
}

void ASwordmancharacter::healthmanaregen()
{
	if (Health < 1.0f) {
		Health = Health + 0.0001f;
	}
	if (Health >= 1.0f) {
		Health = 1.0f;
	}
	if (Mana < 1.0f) {
		Mana = Mana + 0.0001f;
	}
	if (Mana >= 1.0f) {
		Mana = 1.0f;
	}
}

void ASwordmancharacter::sword1regen()
{
	if (sword1cooldown < 1.f) {
		sword1cooldown = sword1cooldown + 0.25;
	}
	if (sword1cooldown >= 1.f) {
		sword1cooldown = 1.f;
		GetWorldTimerManager().ClearTimer(sword1time);
	}
}

void ASwordmancharacter::sword2regen()
{

	if (sword2cooldown < 1.f) {
		sword2cooldown = sword2cooldown + 0.25;
	}
	if (sword2cooldown >= 1.f) {
		GetWorldTimerManager().ClearTimer(sword2time);
	}
}

//hera after function of boss fights
void ASwordmancharacter::setupstimuli()
{
	stimule = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulicomp"));
	stimule->RegisterWithPerceptionSystem();
	stimule->RegisterForSense(TSubclassOf<UAISense_Sight>());
}

