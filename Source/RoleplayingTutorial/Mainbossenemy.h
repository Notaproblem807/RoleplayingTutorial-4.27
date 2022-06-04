// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bosscombatent.h"
#include "Mainbossenemy.generated.h"

/**
 * 
 */
UCLASS()
class ROLEPLAYINGTUTORIAL_API AMainbossenemy : public ABosscombatent
{
	GENERATED_BODY()
public:

	AMainbossenemy();
	//for attaching weapon to mainboss
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, category = "Mainboss|weapon")
		class USkeletalMeshComponent* anyweapon;

	virtual void BeginPlay() override;


	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "senseobject")
		class UPawnSensingComponent* pawnsense;

	//to follow the character
	UFUNCTION()
		void followcharacter(APawn* Pawn);



	
};
