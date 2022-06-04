// Fill out your copyright notice in the Description page of Project Settings.


#include "Findplayerlocationtask.h"
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
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


UFindplayerlocationtask::UFindplayerlocationtask() {
	NodeName = TEXT("Findplayerlocation");
	radiussearch = 150.0f;
	randomsearch = false;
}

EBTNodeResult::Type UFindplayerlocationtask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp,NodeMemory);
	UBlackboardComponent* ownblackboard = OwnerComp.GetBlackboardComponent();
	if (randomsearch) {
		FNavLocation navloc;
		UNavigationSystemV1* navsystem = UNavigationSystemV1::GetCurrent(GetWorld());
		AMainaicontroller* enemy = Cast<AMainaicontroller>(OwnerComp.GetAIOwner());
		FVector origin = enemy->GetCharacter()->GetActorLocation();
		if (navsystem) {
			navsystem->GetRandomPointInNavigableRadius(GetWorld(), origin, radiussearch);
			ownblackboard->SetValueAsVector(bb_keys::Targetlocation, navloc.Location);
		}
	}
	else {
		ACharacter* player=UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (player) {
			ownblackboard->SetValueAsVector(bb_keys::Targetlocation, player->GetActorLocation());
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
