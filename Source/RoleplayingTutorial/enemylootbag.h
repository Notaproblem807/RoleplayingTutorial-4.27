// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "enemylootbag.generated.h"

UCLASS()
class ROLEPLAYINGTUTORIAL_API Aenemylootbag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aenemylootbag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//mesh
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=enemylootbag)
	class UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemylootbag)
		class UBoxComponent* Box;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = enemylootbag)
		class UParticleSystemComponent* lootparticle;

	//actor begin overlap 
	UFUNCTION()
	void lootonoverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//particle to shown when overlapeed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "enemylootbag | overlapparticle ")
	class UParticleSystem* overlapparticleloot;

	//material to set in bag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "enemylootbag | material" )
	UMaterialInterface* bagmaterial;
};
