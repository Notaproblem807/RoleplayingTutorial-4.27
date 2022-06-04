// Fill out your copyright notice in the Description page of Project Settings.


#include "pickupactor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/BoxComponent.h"
#include "RoleplayingTutorialCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Swordmancharacter.h"

// Sets default values
Apickupactor::Apickupactor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Boxcollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Boxcollision"));
	RootComponent = Boxcollision;
	Pickupmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickupmesh"));
	Pickupmesh->SetupAttachment(GetRootComponent());

	Boxcollision->OnComponentBeginOverlap.AddDynamic(this, &Apickupactor::pickupoverlap);

}

// Called when the game starts or when spawned
void Apickupactor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Apickupactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Apickupactor::pickupoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//for the magic charater
	ARoleplayingTutorialCharacter* Player = Cast<ARoleplayingTutorialCharacter>(OtherActor);
	if (Player) {
		if (Player->Health < 1.0f) {
			Player->Health = 0.15 + Player->Health;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Pickupparticle, GetActorLocation(), GetActorRotation(), FVector(1.0f), true, EPSCPoolMethod::None);
			Destroy();
		}
		if (Player->Health >= 1.0f) {
			Player->Health = 1.0f;
		}
	}
	ASwordmancharacter* swordman = Cast<ASwordmancharacter>(OtherActor);
	if (swordman) {
		if (swordman->Health < 1.0f) {
			swordman->Health = 0.15 + swordman->Health;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Pickupparticle, GetActorLocation(), GetActorRotation(), FVector(1.0f), true, EPSCPoolMethod::None);
			Destroy();
		}
		if (swordman->Health >= 1.0f) {
			swordman->Health = 1.0f;
		}
	}
}

