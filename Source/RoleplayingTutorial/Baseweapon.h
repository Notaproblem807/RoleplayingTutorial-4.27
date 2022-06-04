// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Baseweapon.generated.h"

UCLASS()
class ROLEPLAYINGTUTORIAL_API ABaseweapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseweapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//mesh to show weapon
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="baseweapon|weapon")
	USkeletalMeshComponent* Weapon;

	//collision component to interact the damage with ai
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "baseweapon|collision")
	class UBoxComponent* Box;

	USceneComponent* Scene;


};
