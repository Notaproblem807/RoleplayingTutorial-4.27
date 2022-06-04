// Fill out your copyright notice in the Description page of Project Settings.


#include "Mainbossenemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Swordmancharacter.h"
#include "RoleplayingTutorialCharacter.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "Mainbossenemy.h"
#include "TimerManager.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "EnemyAicontroller.h"
#include "MyGameModeonly.h"
#include "SaveGameclass.h"
#include "levelupwidget.h"
#include "thirdroleGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Mainaicontroller.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMainbossenemy::AMainbossenemy() {
//create weapon to attach to hand
	anyweapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weapon"));
	anyweapon->SetupAttachment(GetMesh(), "attachweaponsocket");
	anyweapon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//follow character
	pawnsense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawnsense"));
	pawnsense->SetComponentTickEnabled(true);
	pawnsense->SetSensingUpdatesEnabled(true);
	
}

void AMainbossenemy::BeginPlay()
{
	Super::BeginPlay();
	//followscript
	FScriptDelegate fScriptDelegate;
	fScriptDelegate.BindUFunction(this, "followcharacter");
	pawnsense->OnSeePawn.AddUnique(fScriptDelegate);
}

void AMainbossenemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainbossenemy::followcharacter(APawn* Pawn)
{
	UE_LOG(LogTemp,Warning,TEXT("pawn follow in main boss"))
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	AMainaicontroller* control = Cast<AMainaicontroller>(GetController());
	control->commu = true;
}



