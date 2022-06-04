// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjitileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjitileActor::AProjitileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	projectilrsphere = CreateDefaultSubobject<USphereComponent>(TEXT("projectilesphere"));
	RootComponent = projectilrsphere;
	Projectileparticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectileparticle"));
	Projectileparticle->SetupAttachment(GetRootComponent());
	Projectileparticle->Activate(true);
	Projectilemovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectilemovement"));
	Projectilemovement->SetUpdatedComponent(projectilrsphere);
	Projectilemovement->Activate(true);
}

// Called when the game starts or when spawned
void AProjitileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjitileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

