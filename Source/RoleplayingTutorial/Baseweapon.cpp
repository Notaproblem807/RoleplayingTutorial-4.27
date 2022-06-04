// Fill out your copyright notice in the Description page of Project Settings.


#include "Baseweapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseweapon::ABaseweapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
	Box =CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(GetRootComponent());
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABaseweapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseweapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

