// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjitileActor.generated.h"

UCLASS()
class ROLEPLAYINGTUTORIAL_API AProjitileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjitileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    //particle to project
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectileprops)
		class UParticleSystemComponent*  Projectileparticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectileprops)
		class UProjectileMovementComponent* Projectilemovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectileprops)
		class USphereComponent* projectilrsphere;
};
