// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Mythirdmainhud.generated.h"

/**
 * 
 */
UCLASS()
class ROLEPLAYINGTUTORIAL_API UMythirdmainhud : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
};
