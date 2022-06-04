// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAicontroller.generated.h"

/**
 * 
 */
UCLASS()
class ROLEPLAYINGTUTORIAL_API AEnemyAicontroller : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAicontroller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//property to move ai
	FAIMoveRequest Followai;
	FNavPathSharedPtr Navpath;

	APawn* player;
	//boolean to gve true to the aicontrolleyer the player is spotted;
	bool playerseen;
	//function of maitain
	void movetotarget();

	//player indicator
	ACharacter* chardup;

	//function and properties to give random movement for the enemy ai
	FTimerHandle followtimeran;
	FTimerHandle delayintick;
	FTimerDynamicDelegate timertickdele;
    //NOT SETUPPED AND USED
	



	//functoin to delay of followness of character
	UFUNCTION()
	void followrandomness();
	//boolean to set enemy ai is moving in random;
	bool enemymoving;


	//navigation system to be enabled to get reach random location
	class UNavigationSystemV1* Navsystem;

	//this function and implementation belongs to get reach random location and return bool to move the ai give the parameters
	bool getrandomlocation(const FVector& Origin, float Radius, FVector& OutResult);
	//given proper random location move to laction
	bool navsuccess;
	//if you no implement this function enemy confuse location and rotates
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;





	//casting purpose to get location of th e enemyai
	class ASimpleAI* enemyaidup;

	//timer to make stealth ai
	UFUNCTION()
	void settingfocuslos();
	bool focusbol;
	bool focus;
	void movefocus();
	int32 a;

	FTimerHandle handle;
	FLatentActionInfo actioninfo;

	
};
