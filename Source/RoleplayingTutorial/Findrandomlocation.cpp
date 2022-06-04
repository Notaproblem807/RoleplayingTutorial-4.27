// Fill out your copyright notice in the Description page of Project Settings.


#include "Findrandomlocation.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Mainaicontroller.h"
#include "Mainbossenemy.h"
#include "blackboard_keys.h"
#include "Navigation/PathFollowingComponent.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UFindrandomlocation::UFindrandomlocation() {
	NodeName = TEXT("Find location");
}

EBTNodeResult::Type UFindrandomlocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UE_LOG(LogTemp, Warning, TEXT("bttask"));
	AMainaicontroller* controller = Cast<AMainaicontroller>(OwnerComp.GetAIOwner());
	AMainbossenemy* Pawn =Cast<AMainbossenemy>(controller->GetPawn());
	UBlackboardComponent* ownblackboard = OwnerComp.GetBlackboardComponent();
	//for the random movement
	FVector originofpawn = Pawn->GetActorLocation();
	FNavLocation navloc;
	UNavigationSystemV1* navsystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (navsystem) {
		navsystem->GetRandomPointInNavigableRadius(GetWorld(), originofpawn, searchradius);
		ownblackboard->SetValueAsVector(bb_keys::Targetlocation, navloc.Location);
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
