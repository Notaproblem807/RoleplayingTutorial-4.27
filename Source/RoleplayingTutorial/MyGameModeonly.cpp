// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeonly.h"
#include "SaveGameclass.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AMyGameModeonly::AMyGameModeonly() {
	Quest =FText::FromString("No Quest");
	//setter for levelxp
	Level = 1;
	maxexperiencelevel = 5;
	Exerpiencelevel = 0;
	//save properties

	

}

void AMyGameModeonly::BeginPlay()
{
	Super::BeginPlay();
	//cast to our savegameclass
	if (!(UGameplayStatics::DoesSaveGameExist(Saveslotname,0))) {
		Saveoriginal=UGameplayStatics::LoadGameFromSlot(Saveslotname, 0);
		Saveref = Cast<USaveGameclass>(Saveoriginal);
		Level = Saveref->Savedlevel;
		maxexperiencelevel = Saveref->Savedmaxexperiencelevel;
		Exerpiencelevel = Saveref->Savedexperiencelevel;
	}
	else {
		Saveoriginal = UGameplayStatics::CreateSaveGameObject(subsaveref);
		Saveref = Cast<USaveGameclass>(Saveoriginal);
		//for saving purpose
		UGameplayStatics::SaveGameToSlot(Saveref, Saveslotname, 0);
	}
}

void AMyGameModeonly::UpdateXplevels()
{
	Saveref = Cast<USaveGameclass>(Saveoriginal);
	Saveref->Savedmaxexperiencelevel = maxexperiencelevel;
	Saveref->Savedexperiencelevel = Exerpiencelevel;
	Saveref->Savedlevel = Level;
	UGameplayStatics::SaveGameToSlot(Saveref, Saveslotname, 0);
}
