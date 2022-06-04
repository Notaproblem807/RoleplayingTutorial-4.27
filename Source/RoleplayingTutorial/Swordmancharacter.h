// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Character.h"
#include "Swordmancharacter.generated.h"




UCLASS()
class ROLEPLAYINGTUTORIAL_API ASwordmancharacter : public ACharacter 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	
	ASwordmancharacter();
	//default constructor for Fattachmentrule

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float  DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void MoveForward(float Value);

	/** Called for side to side input */
	
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/*Base turn rate, in deg / sec.Other scaling may affect final turn rate.*/
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	//location to spawn weapon and their properties
	
	FVector Weaponloc;
	FActorSpawnParameters weaponparam;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="swordman|weaponref")
		class ABaseweapon* weaponref;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="swordman|weaponref")
	TSubclassOf<ABaseweapon> subweaponspawn;

public:
	// attachment rules of weapon
	void attachweapon();
	//FAttachmentTransformRules Ruleofweapon; to find more about this remender to solve problem it do not works properly when name given;
	//spawning animation to play swordattack animation when pressed left mouse button
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "swordman|ability1")
		bool swordslash;
	//when left mouse pressed
	void ability1press();
	//delay of attack animation
	FTimerHandle ability1delay;
	void ability1delayfunc();


	//health and mana initialization
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "swordman|hud")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "swordman|hud")
	float Mana;
	//health mana regeneration func
	FTimerHandle heamantime;
	void healthmanaregen();
	//hud refence to show in viewport
	class USwordmainhud* swordhudref;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "swordman|hud")
	TSubclassOf<USwordmainhud> setupswordhud;
	//ability1 cooldown system in the hud
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "swordman|hud")
	float sword1cooldown;
	//ability2 cooldownsystem in the hud
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "swordman|hud")
	float sword2cooldown;
	//timer to regenrate swordcooldown
	FTimerHandle sword1time;
	FTimerHandle sword2time;
	//func to regenerate to 1.f in cooldown
	void sword1regen();
	//func to regenarate to 1.f in sword2 cooldown
	void sword2regen();

	//jump animation setups
	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="swordJump|stats")
	bool swordinair;

	//boss fight properties
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "boss|collider")
		class USphereComponent* Bosscollider;

	//boss stats

	//setting stimuli for ai perception
	class UAIPerceptionStimuliSourceComponent* stimule;
	void setupstimuli();


};
