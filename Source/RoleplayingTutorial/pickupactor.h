// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "pickupactor.generated.h"

UCLASS()
class ROLEPLAYINGTUTORIAL_API Apickupactor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Apickupactor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//staticmesh to overlape
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = pickupstats)
	class UStaticMeshComponent* Pickupmesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = pickupstats)
		class UParticleSystem* Pickupparticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = pickupstats)
		class UBoxComponent* Boxcollision;

	//begin overlap function;
	UFUNCTION()
	void pickupoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
