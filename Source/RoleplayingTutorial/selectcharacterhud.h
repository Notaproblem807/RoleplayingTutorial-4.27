// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "selectcharacterhud.generated.h"

/**
 * 
 */
UCLASS()
class ROLEPLAYINGTUTORIAL_API Uselectcharacterhud : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	//pawn
	class APawn* Pawn;
	//parameter of actor to spawn
	FActorSpawnParameters Spawnparm;

	//button to bind to select specific character
	UPROPERTY(meta=(BindWidget))
	class UButton* Sword;
	//function to execute when clicked
	UFUNCTION()
	void settingswordman();
	UPROPERTY(meta =(BindWidget))
	class UButton* Magic;
	//function to execute when clicked
	UFUNCTION()
	void settingmagic();
	//reference to the character
	class ARoleplayingTutorialCharacter* Magicref;
	class ASwordmancharacter* Swordref;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "selectcharacterhud|playerref")
	TSubclassOf<ARoleplayingTutorialCharacter> submagicref;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "selectcharacterhud|playerref")
	TSubclassOf<ASwordmancharacter> subswordref;
};
