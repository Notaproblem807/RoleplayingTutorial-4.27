// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleAI.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjitileActor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "enemylootbag.h"
#include "Baseweapon.h"
#include "Swordmancharacter.h"
#include "TimerManager.h"
#include "Perception/PawnSensingComponent.h"
#include "RoleplayingTutorialCharacter.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "EnemyAicontroller.h"
#include "MyGameModeonly.h"
#include "SaveGameclass.h"
#include "levelupwidget.h"
#include "thirdroleGameInstance.h"

// Sets default values
ASimpleAI::ASimpleAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//constructor for pawn sensing
	pawnsense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawnsense"));
	pawnsense->SetComponentTickEnabled(true);
	pawnsense->SetSensingUpdatesEnabled(true);
	//it will give error add publicdependency "AIModule"
	//initialize path folloowing component
	
	//health initialize
	Health = 1.0f;
	//initialize for sword can hit only once; and no damage to be occured for reverse play
	swordcanhit = true;
	

	



}

// Called when the game starts or when spawned
void ASimpleAI::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ASimpleAI::projitileactorover);
	//weapon on overlap dealing damage
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASimpleAI::swordoverlap);
	lootspawnloc= GetMesh()->GetSocketLocation(FName("foot_r"));

	FScriptDelegate fScriptDelegate;
	fScriptDelegate.BindUFunction(this, "followcharacter");
	pawnsense->OnSeePawn.AddUnique(fScriptDelegate);
}


// Called every frame
void ASimpleAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

// Called to bind functionality to input
void ASimpleAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//pawn sense movement function
void ASimpleAI::followcharacter(APawn* Pawn)
{
	//ai controller initialization to get their function to move ai to player;
	AEnemyAicontroller* Aicontroller = Cast<AEnemyAicontroller>(GetController());
	auto player=UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (player==Pawn && Aicontroller) {
		UE_LOG(LogTemp, Warning, TEXT("equal works"));
		Aicontroller->playerseen = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void ASimpleAI::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (pawnsense) {
		UE_LOG(LogTemp, Warning, TEXT("pawnsense works"));
		//ai to see the character we have build follow them
		//pawnsense->OnSeePawn.AddDynamic(this, &ASimpleAI::followcharacter);
	}
}


void ASimpleAI::projitileactorover(AActor* OverlappedActor, AActor* OtherActor)
{
	AProjitileActor* refernceofprojectile = Cast<AProjitileActor>(OtherActor);
	if (refernceofprojectile) {
		UE_LOG(LogTemp, Warning, TEXT("overlap works"));
		Health = Health - 0.25f;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), overlapparticle, refernceofprojectile->GetActorTransform(), true, EPSCPoolMethod::None);
		refernceofprojectile->Destroy();
		if (Health <= 0.f) {
			//Destroy();
			afterdeath();
			refernceofprojectile->Destroy();
		}
	}
}

void ASimpleAI::afterdeath()
{
	lootbagref=GetWorld()->SpawnActor<Aenemylootbag>(spawnlootbag, lootspawnloc, GetActorRotation(), lootparam);
	//setting level and experience level in the hud;
	//get game mode for setting level;
	AGameModeBase* Base = UGameplayStatics::GetGameMode(GetWorld());
	AMyGameModeonly* MyGamemode = Cast<AMyGameModeonly>(Base);
	MyGamemode->Exerpiencelevel = MyGamemode->Exerpiencelevel++;
	if (MyGamemode->Exerpiencelevel >= MyGamemode->maxexperiencelevel) {
		MyGamemode->Level = MyGamemode->Level++;
		//creating and gameinstance to show widget
		Gameinstance = Cast<UthirdroleGameInstance>(GetGameInstance());
		if (levelupref) {
			levelupop = CreateWidget<Ulevelupwidget>(Gameinstance, levelupref);
		}
		levelupop->AddToViewport(0);
		MyGamemode->maxexperiencelevel = MyGamemode->maxexperiencelevel * 1.8;
	}
	MyGamemode->UpdateXplevels();
	if (!IsPendingKill()) {
		Destroy();
	}
}

void ASimpleAI::swordoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseweapon* weaponref = Cast<ABaseweapon>(OtherActor);
	if (weaponref) {
		ACharacter* caster=UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		UE_LOG(LogTemp, Warning, TEXT("overlap works"));
		if (caster) {
			UE_LOG(LogTemp, Warning, TEXT("caster works"));
			ASwordmancharacter* sworref = Cast<ASwordmancharacter>(caster);
			if (sworref) {
				UE_LOG(LogTemp, Warning, TEXT("sworref works"));
				if (sworref->swordslash) {
					if (swordcanhit) {
						Health = Health - 0.175;
						//intialize sword can damage once
						swordcanhit = false;
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), weaponparticleoverlap, GetActorLocation(), GetActorRotation(), true, EPSCPoolMethod::None);
						//delay timer to set back default swordcanhit
						GetWorldTimerManager().SetTimer(swordcanhitdelay, this, &ASimpleAI::swordcangeneral, 1.0f, false, 1.0f);
						if (Health <= 0.f) {
							afterdeath();
							//swordcanhit= true;
						}
					}
				}
			}
		}
	}
}

void ASimpleAI::swordcangeneral()
{
	swordcanhit = true;
}

