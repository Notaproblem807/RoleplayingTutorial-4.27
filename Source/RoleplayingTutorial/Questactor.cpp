// Fill out your copyright notice in the Description page of Project Settings.


#include "Questactor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "RoleplayingTutorialCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "Swordmancharacter.h"
#include "MyGameModeonly.h"

// Sets default values
AQuestactor::AQuestactor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxQuest = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxQuest"));
	RootComponent = BoxQuest;


}

// Called when the game starts or when spawned
void AQuestactor::BeginPlay()
{
	Super::BeginPlay();
	BoxQuest->OnComponentBeginOverlap.AddDynamic(this, &AQuestactor::Questonoverlapped);
	
}

// Called every frame
void AQuestactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AQuestactor::Questonoverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Allcharacter = Cast<ACharacter>(OtherActor);
	if (Allcharacter) {
		AGameModeBase* mode = UGameplayStatics::GetGameMode(GetWorld());
		AMyGameModeonly* Gamemodemy = Cast<AMyGameModeonly>(mode);
		Gamemodemy->Quest = FText::FromString("Evolved Quest");
	}
}

