// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Questactor.generated.h"

UCLASS()
class ROLEPLAYINGTUTORIAL_API AQuestactor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuestactor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BoxQuest)
	class UBoxComponent* BoxQuest;

	//when character overlapped the component quest to be changed
	//actor begin overlap 
	UFUNCTION()
	void Questonoverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
