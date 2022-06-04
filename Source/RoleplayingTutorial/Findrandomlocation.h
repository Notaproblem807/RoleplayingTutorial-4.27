// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Findrandomlocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ROLEPLAYINGTUTORIAL_API UFindrandomlocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindrandomlocation();
	//for random movement
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
	//location in radius
	float searchradius = 1000.f;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector MyBlackboardKey;



	
};
