// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoleplayingTutorialCharacter.generated.h"

class AProjitileActor;

UCLASS(config=Game)
class ARoleplayingTutorialCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ARoleplayingTutorialCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

public:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	UFUNCTION()
	void MoveForward(float Value);

	/** Called for side to side input */
	UFUNCTION()
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	UFUNCTION()
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	UFUNCTION()
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// insert virtual before to inherit to the child class

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds)override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	//Gameinstance
	class UthirdroleGameInstance* thirdgameinstance;

	//thirdmainhud properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = thirdmainhud)
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = thirdmainhud)
	float Manner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = thirdmainhud)
		TSubclassOf<class UMythirdmainhud> Subthirdmainhud;
	class UMythirdmainhud* thirdmainhud;

	//manahud properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = manahud)
	TSubclassOf<class Umanahud> submanahud;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = manahud)
	class Umanahud* Manahud;

	//casting spell ability
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CastingHealth)
	bool bCastingH;
	void Casting1H();
	//handle timing
	FTimerHandle Timerhandle;
	void castingtimedelay();

	//ability 1
	void ability1();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ability1)
	UParticleSystem* abilty1particle;
	//copy of particle 
	UParticleSystem* ability1parref;
	// timer for particle to destroy
	FTimerHandle Particletonull;
	//function to nullify the particle
	void nullparticlefunc();

	FVector ability1location;
	//ability1 cool down system ith hud
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ability1 | hud")
	float abiliy1cool;
	//delay setup for abilityallcool down in hud 
	FTimerHandle delay1cooldown;
	//filling function for 1ability
	void ability1filling();
	//abilitytimerhandle for 2ability
	FTimerHandle delay2cooldown;
	void ability2filling();

	//health regeneration and manner regeneration
	void Healthmanaregen();
	void regenfunc();
	
	
	//delay
	FLatentActionInfo Latent;
	//latentfunction
	UFUNCTION(BlueprintCallable)
	bool healthmanadelay();
	bool returnheamana;

	//ability2 properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ability2)
	bool bcastingcombat;
	void ability2();
	//ability2 cool down system ith hud
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ability2 | hud")
	float abiliy2cool;
	//delay for the projectile to release
	FTimerHandle delayability2;
	void ability2delay();
	//location to release projectile
	FVector ability2location;
	FTransform ability2transform;
	//spawning ability2 projectile parameters
	FActorSpawnParameters abitlity2param;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ability2)
	TSubclassOf<class AProjitileActor> ability2spawn;
	class AProjitileActor* ability2projectile;



	//jump animation setups
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="MagicJump|stats")
	bool magicinair;


	//new boss fight properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="boss|collider")
	class USphereComponent* collidesphere;

	//boss stats

	
};

