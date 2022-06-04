// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameclass.generated.h"

/**
 * 
 */
UCLASS()
class ROLEPLAYINGTUTORIAL_API USaveGameclass : public USaveGame
{
	GENERATED_BODY()
public:
	USaveGameclass();

	//setting load and save prop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Savegame|stat")
	int32 Savedlevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Savegame|stat")
	int32 Savedmaxexperiencelevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Savegame|stat")
	int32 Savedexperiencelevel;


	

	
};
