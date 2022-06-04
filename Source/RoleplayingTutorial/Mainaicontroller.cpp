// Fill out your copyright notice in the Description page of Project Settings.


#include "Mainaicontroller.h"
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
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "GameFramework/Character.h"
#include "blackboard_keys.h"

AMainaicontroller::AMainaicontroller(const FObjectInitializer& object_initializer) {
	commu = false;
//initialize the behaviourcomponent
	BehaviourtreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	//initalize the blackboard
	Blackboardcomponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboardcomponent"));
	//initialize the tree 
	static ConstructorHelpers::FObjectFinder<class UBehaviorTree>obj(TEXT("BehaviorTree'/Game/mainenemyai/AIcomponents/Mainbehaviour_Bp.Mainbehaviour_Bp'"));
	if (obj.Succeeded()) {
		Behavtiortree = obj.Object;
	}
	//initialize AIperception
	Setup_perceptioncomp();

}

void AMainaicontroller::BeginPlay() {
	Super::BeginPlay();
	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Mainboss = Cast<AMainbossenemy>(GetPawn());
	//behavoiur tree setups
	RunBehaviorTree(Behavtiortree);
	BehaviourtreeComponent->StartTree(*Behavtiortree);
	
}


void AMainaicontroller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!commu) {
		//UE_LOG(LogTemp, Warning, TEXT("mainboss equal"));
		player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		ASwordmancharacter* sworddup = Cast<ASwordmancharacter>(player);
		if (sworddup) {
			//SetFocus(sworddup);
			//MoveToActor(sworddup,0.5f);
		}
		ARoleplayingTutorialCharacter* Roledup = Cast<ARoleplayingTutorialCharacter>(player);
		if (Roledup) {
			//SetFocus(Roledup);
			//MoveToActor(Roledup, 0.5f);
		}
	}
	
}

UBlackboardComponent* AMainaicontroller::getblackboard()
{
	return Blackboardcomponent;
}

void AMainaicontroller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (Blackboardcomponent) {
		Blackboardcomponent->InitializeBlackboard(*Behavtiortree->BlackboardAsset);
	}
}

void AMainaicontroller::Targetupdated(AActor* Actor, FAIStimulus Stimulus)
{
	ACharacter* player=UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	if (player==Actor) {
		getblackboard()->SetValueAsBool(bb_keys::Canseeplayer, Stimulus.WasSuccessfullySensed());
	}
}

void AMainaicontroller::Setup_perceptioncomp()
{
	sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("sensesight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perceptcomponent")));
	//setting sight sense to perception componnet
	GetPerceptionComponent()->ConfigureSense(*sight);
	GetPerceptionComponent()->SetDominantSense(*sight->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AMainaicontroller::Targetupdated);
	//sight prop
	sight->DetectionByAffiliation.bDetectEnemies = true;
	sight->DetectionByAffiliation.bDetectFriendlies = true;
	sight->DetectionByAffiliation.bDetectNeutrals = true;
	sight->SightRadius = 500.f;
	sight->LoseSightRadius = sight->SightRadius + 50.f;
	sight->SetMaxAge(5.0f);
	sight->AutoSuccessRangeFromLastSeenLocation = 900.f;
	sight->PeripheralVisionAngleDegrees = 90.f;

}

