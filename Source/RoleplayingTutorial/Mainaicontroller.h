// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Mainaicontroller.generated.h"

/**
 * 
 */
UCLASS()
class ROLEPLAYINGTUTORIAL_API AMainaicontroller : public AAIController
{
	GENERATED_BODY()

public:
	AMainaicontroller(const FObjectInitializer& object_initializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//player to follow
	APawn* player;

	//refence to the enemy
	class AMainbossenemy* Mainboss;

	//bool to communicate with ai
	bool commu;

//blackboard and behavour tree functions
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI|Behaviour")
	class UBehaviorTreeComponent* BehaviourtreeComponent;

	class UBlackboardComponent* getblackboard();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|blackboard")
	class UBlackboardComponent* Blackboardcomponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Behavioursetted")
	class UBehaviorTree* Behavtiortree;

	virtual void OnPossess(APawn* InPawn) override;

	//Aiperception for chasing player setup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|perceptionprop")
	class UAISenseConfig_Sight* sight;
	//func to targetperception updated
	UFUNCTION()
	void Targetupdated(AActor* Actor, FAIStimulus Stimulus);
	//initialize the AI perception
	void Setup_perceptioncomp();
	
};
