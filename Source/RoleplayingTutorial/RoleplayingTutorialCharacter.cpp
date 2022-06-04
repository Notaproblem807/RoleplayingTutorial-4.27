// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RoleplayingTutorialCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Mythirdmainhud.h"
#include "thirdroleGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/LatentActionManager.h"
#include "ProjitileActor.h"
#include "manahud.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Mainbossenemy.h"


//////////////////////////////////////////////////////////////////////////
// ARoleplayingTutorialCharacter

ARoleplayingTutorialCharacter::ARoleplayingTutorialCharacter()
{
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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	//thirdmainhud constructor reference
	Health = 0.4;
	Manner = 0.5;

	//ability1
	bCastingH = false;

	//constructor for particle1 
	static ConstructorHelpers::FObjectFinder<UParticleSystem>particle1asset(TEXT("ParticleSystem'/Game/InfinityBladeEffects/Effects/FX_Skill_Aura/P_AuraCircle_Temp.P_AuraCircle_Temp'"));
	if (particle1asset.Succeeded()) {
		abilty1particle = particle1asset.Object;
		ability1parref = particle1asset.Object;
	}

	

	//ability1cooldown initialize
	abiliy1cool = 1.f;
	abiliy2cool = 1.f;

	//health and mana regeneration return bool
	returnheamana = false;

	//delay latent 
	Latent.CallbackTarget = this;
	Latent.UUID = 0;
	Latent.Linkage = 0;
	Latent.ExecutionFunction = FName("healthmanadelay");

	//boss fight initialization
	collidesphere = CreateDefaultSubobject<USphereComponent>(TEXT("bosscollider"));
	collidesphere->SetupAttachment(GetRootComponent());


}

//////////////////////////////////////////////////////////////////////////
// Input

void ARoleplayingTutorialCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Getting my gameinstance
	thirdgameinstance = Cast<UthirdroleGameInstance>(GetGameInstance());
	//creating thirdmainhud widget 
	if (Subthirdmainhud) {
		thirdmainhud = CreateWidget<UMythirdmainhud>(thirdgameinstance, Subthirdmainhud);
	}
	thirdmainhud->AddToViewport(0);
	//boss collided function to execute
}

void ARoleplayingTutorialCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//healthregen and Manaregen
	Healthmanaregen();
	if (healthmanadelay()) {
		regenfunc();
		//UE_LOG(LogTemp, Warning, TEXT("regenfunc")
	}
	//jump animation initialization
	magicinair = GetCharacterMovement()->IsFalling();
	if (magicinair) {
		UE_LOG(LogTemp, Warning, TEXT("magic not in air"));
	}
		
}

void ARoleplayingTutorialCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARoleplayingTutorialCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARoleplayingTutorialCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ARoleplayingTutorialCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ARoleplayingTutorialCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ARoleplayingTutorialCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ARoleplayingTutorialCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ARoleplayingTutorialCharacter::OnResetVR);

	//casting spell ability
	PlayerInputComponent->BindAction("castinghealth", IE_Pressed, this, &ARoleplayingTutorialCharacter::Casting1H);
	//ability1
	PlayerInputComponent->BindAction("ability1", IE_Pressed, this, &ARoleplayingTutorialCharacter::ability1);
	//ability2
	PlayerInputComponent->BindAction("ability2", IE_Pressed, this, &ARoleplayingTutorialCharacter::ability2);
}

//casting spell ability
void ARoleplayingTutorialCharacter::Casting1H()
{
	bCastingH = true;
	//GetWorldTimerManager().SetTimer(Timerhandle,this,&ARoleplayingTutorialCharacter::castingtimedelay,1.0f, false, 2.0f);
}

void ARoleplayingTutorialCharacter::castingtimedelay()
{
	
	//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking, 0);
	bCastingH = false;
	bcastingcombat = false;
	UE_LOG(LogTemp, Warning, TEXT("castingtimedelay"));
}

void ARoleplayingTutorialCharacter::ability1()
{
	if (abiliy1cool==1.f) {
		if (!bCastingH) {
			if (Manner >= 0.2) {
				//disabling this for the gameplay purpose
				//GetCharacterMovement()->DisableMovement();
				//GetCharacterMovement()->StopMovementImmediately();
				Manner = Manner - 0.2;
				Health = Health + 0.15;
				bCastingH = true;
				ability1location = GetMesh()->GetSocketLocation(FName("RightFoot"));
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), abilty1particle, ability1location, GetActorRotation(),true,EPSCPoolMethod::None);
				//timer to set particle to null
				GetWorldTimerManager().SetTimer(Particletonull, this, &ARoleplayingTutorialCharacter::nullparticlefunc, 1.0f, false, 3.0f);
				abiliy1cool = 0.f;
				if (abiliy1cool < 1.f) {
					GetWorldTimerManager().SetTimer(delay1cooldown, this, &ARoleplayingTutorialCharacter::ability1filling, 1.0f,true, 2.0f);
				}
				GetWorldTimerManager().SetTimer(Timerhandle, this, &ARoleplayingTutorialCharacter::castingtimedelay, 1.0f, false, 2.0f);
			}
			else {
				//creating manahud widget
				if (submanahud) {
					Manahud = CreateWidget<Umanahud>(thirdgameinstance, submanahud);
				}
				Manahud->AddToViewport(0);
			}
		}	
	}
}


//particle to set null after timing
void ARoleplayingTutorialCharacter::nullparticlefunc()
{
 
}

void ARoleplayingTutorialCharacter::ability1filling()
{
	//timespan to cancel loop not works properly
	abiliy1cool = abiliy1cool + 0.1;
	//setting ability cool down system 
	UE_LOG(LogTemp, Warning, TEXT("ability 1 timedelay"));
	if (abiliy1cool >= 1.f) {
		abiliy1cool = 1.f;
		GetWorldTimerManager().ClearTimer(delay1cooldown);
	}
}
void ARoleplayingTutorialCharacter::ability2filling()
{
	abiliy2cool = abiliy2cool + 0.1;
	UE_LOG(LogTemp, Warning, TEXT("ability 2 timedelay"));
	if (abiliy2cool >= 1.f) {
		abiliy2cool = 1.f;
		GetWorldTimerManager().ClearTimer(delay2cooldown);
	}
}

void ARoleplayingTutorialCharacter::Healthmanaregen()
{
	//GetWorldTimerManager().SetTimer(Fhealthmanadelay, this, &ARoleplayingTutorialCharacter::healthmanadelay, 1.0f, false, 2.0f);
	//UE_LOG(LogTemp, Warning, TEXT("tick 1 works"));
	returnheamana = false;
	UKismetSystemLibrary::Delay(this, 5000.0f, Latent);
	
}


void ARoleplayingTutorialCharacter::regenfunc()
{
	if (Health < 1.0f) {
		Health = Health + 0.001f;
	}
	if (Health >= 1.0f) {
		Health = 1.0f;
	}
	if (Manner < 1.0f) {
		Manner = Manner + 0.001f;
	}
	if (Manner >= 1.0f) {
		Manner = 1.0f;
	}
}



bool ARoleplayingTutorialCharacter::healthmanadelay()
{
	//UE_LOG(LogTemp, Warning, TEXT("tick 3 works"));
	returnheamana = true;
	return returnheamana;
}

void ARoleplayingTutorialCharacter::ability2()
{
	if (abiliy2cool==1.f) {
		if (!bCastingH || !bcastingcombat) {
			if (Manner >= 0.15) {
				//GetCharacterMovement()->DisableMovement();
				//GetCharacterMovement()->StopMovementImmediately();
				Manner = Manner - 0.2;
				bcastingcombat = true;
				ability2location = GetMesh()->GetSocketLocation(FName("RightHandRing1"));
				ability2location = (GetActorForwardVector() * 15) + ability2location;
				abiliy2cool = 0.f;
				//time delay for projectile
				GetWorldTimerManager().SetTimer(delayability2, this, &ARoleplayingTutorialCharacter::ability2delay, 1.0f, false, 1.0f);
				//cool down abilty system
				if (abiliy2cool < 1.f) {
					GetWorldTimerManager().SetTimer(delay2cooldown, this, &ARoleplayingTutorialCharacter::ability2filling, 1.0f, true, 2.0f);
				}
				//normal delay
				GetWorldTimerManager().SetTimer(Timerhandle, this, &ARoleplayingTutorialCharacter::castingtimedelay, 1.0f, false, 2.0f);
			}
			else {
				//creating manahud widget
				if (submanahud) {
					Manahud = CreateWidget<Umanahud>(thirdgameinstance,submanahud);
				}
				Manahud->AddToViewport(0);
			}
		}
	}
}


//time delay for projectile release
void ARoleplayingTutorialCharacter::ability2delay()
{
	ability2projectile=GetWorld()->SpawnActor<AProjitileActor>(ability2spawn, ability2location, GetActorRotation(), abitlity2param);
}



void ARoleplayingTutorialCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ARoleplayingTutorialCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ARoleplayingTutorialCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ARoleplayingTutorialCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ARoleplayingTutorialCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}



void ARoleplayingTutorialCharacter::MoveForward(float Value)
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

void ARoleplayingTutorialCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
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

//boss fight
