// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameModeonly.generated.h"

/**
 * 
 */
UCLASS()
class ROLEPLAYINGTUTORIAL_API AMyGameModeonly : public AGameMode
{
	GENERATED_BODY()
public:
	AMyGameModeonly();
	//to set quest 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Mygamemode|Quest")
	FText Quest;

	//for xp level and level changing behaviour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mygamemode|levelstat")
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mygamemode|levelstat")
	int32 Exerpiencelevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mygamemode|levelstat")
	int32 maxexperiencelevel;
	//function to getsavegameclasss and create 
	virtual void BeginPlay() override;

	//reference to savgameoriginal object
	class USaveGame* Saveoriginal;
	//reference to the savegamereference class of my game
	class USaveGameclass* Saveref;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mygamemode|saveclasssetter")
	TSubclassOf<USaveGameclass> subsaveref;

	//function to save xp level in savegame class
	void UpdateXplevels();
	//property to save game
	FString Saveslotname = TEXT("slotxp");

	
};
