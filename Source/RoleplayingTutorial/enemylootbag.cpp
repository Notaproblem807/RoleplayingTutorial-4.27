// Fill out your copyright notice in the Description page of Project Settings.


#include "enemylootbag.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RoleplayingTutorialCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "Swordmancharacter.h"

// Sets default values
Aenemylootbag::Aenemylootbag()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(GetRootComponent());
	lootparticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Lootparticle"));
	lootparticle->SetupAttachment(GetRootComponent());

	Box->OnComponentBeginOverlap.AddDynamic(this, &Aenemylootbag::lootonoverlapped);

	//constructor for material to set 
	static ConstructorHelpers::FObjectFinder<UMaterialInterface>Materialset(TEXT("Material'/Game/InfinityBladeEffects/Effects/FX_Materials/M_GoldBag.M_GoldBag'"));
	if (Materialset.Succeeded()) {
		bagmaterial = Materialset.Object;
	}
	mesh->SetMaterial(0, bagmaterial);

}

// Called when the game starts or when spawned
void Aenemylootbag::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aenemylootbag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Aenemylootbag::lootonoverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARoleplayingTutorialCharacter* charref = Cast<ARoleplayingTutorialCharacter>(OtherActor);
	if (charref) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), overlapparticleloot, GetActorTransform(), true,EPSCPoolMethod::None);
		Destroy();
	}
	ASwordmancharacter* swordref = Cast<ASwordmancharacter>(OtherActor);
	if (swordref) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), overlapparticleloot, GetActorTransform(), true, EPSCPoolMethod::None);
		Destroy();
	}
}

