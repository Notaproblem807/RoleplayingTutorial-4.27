// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Findplayerlocationtask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ROLEPLAYINGTUTORIAL_API UFindplayerlocationtask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindplayerlocationtask();

	//for random movement and chasing player
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	//for random movement
	bool randomsearch;

	//radius to search for player
	float radiussearch;

	
};
