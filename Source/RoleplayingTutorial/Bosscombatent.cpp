// Fill out your copyright notice in the Description page of Project Settings.


#include "Bosscombatent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"

// Sets default values
ABosscombatent::ABosscombatent()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABosscombatent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABosscombatent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABosscombatent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
