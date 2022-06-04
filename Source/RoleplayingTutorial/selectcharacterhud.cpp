// Fill out your copyright notice in the Description page of Project Settings.


#include "selectcharacterhud.h"
#include "Components/Button.h"
#include "Swordmancharacter.h"
#include "RoleplayingTutorialCharacter.h"
#include "Kismet/GameplayStatics.h"


//this widget to be setupped in level blueprint in editor
void Uselectcharacterhud::NativeConstruct() {
	Super::NativeConstruct();
	//get pawn of constructor
	Pawn = GetOwningPlayerPawn();
	Spawnparm.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	APlayerController* playercontroller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playercontroller->bShowMouseCursor = true;
	Sword->OnClicked.AddDynamic(this, &Uselectcharacterhud::settingswordman);
	Magic->OnClicked.AddDynamic(this, &Uselectcharacterhud::settingmagic);
	


}

void Uselectcharacterhud::settingswordman()
{
	//spawning swordman as default pawn
	UE_LOG(LogTemp,Warning,TEXT(" settingwordman"))
	FTransform transform;
	// transfor of player start in world
	transform.SetLocation(FVector(-970.0f, -346.4434204f, 202.0006714f));
	Swordref = GetWorld()->SpawnActor<ASwordmancharacter>(subswordref, transform, Spawnparm);
	APlayerController* playercontroller=UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playercontroller->Possess(Swordref);
	playercontroller->bShowMouseCursor = false;
	RemoveFromParent();
}

void Uselectcharacterhud::settingmagic()
{
	//spawning magicgirl as default pawn
	//spawning swordman as default pawn
	FTransform transform;
	// transfor of player start in world
	transform.SetLocation(FVector(-970.0f, -346.4434204f, 202.0006714f));
	Magicref = GetWorld()->SpawnActor<ARoleplayingTutorialCharacter>(submagicref, transform, Spawnparm);
	APlayerController* playercontroller=UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playercontroller->Possess(Magicref);
	playercontroller->bShowMouseCursor = false;
	RemoveFromParent();
}
