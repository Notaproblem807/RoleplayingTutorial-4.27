// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AITypes.h"


#include "SimpleAI.generated.h"

UCLASS()
class ROLEPLAYINGTUTORIAL_API ASimpleAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASimpleAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//ai behavoiur to our character
	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="mainobject")
	class UPawnSensingComponent* pawnsense;

	//function to make ai follow the character
	UFUNCTION()
	void followcharacter(APawn* Pawn);
	
	//method to be override to work proper in pawnsense component
	virtual void PostInitializeComponents() override;


	//health of AI
	float Health;
	

	//projectile overlap this actor reduce health and play effects
	//UFUNCTION()
	//void projectileoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//particle system to play when overlaped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = overlapparticlesimpleai)
	UParticleSystem* overlapparticle;


	//projectile overlap this actor reduce health and play effects
	UFUNCTION()
	void projitileactorover(AActor* OverlappedActor, AActor* OtherActor);

	//function to execute after death occured
	void afterdeath();

	//spawning the loot bag func
	FActorSpawnParameters lootparam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "overlapparticlesimpleai | spawnloot")
	TSubclassOf<class Aenemylootbag>spawnlootbag;
	class Aenemylootbag* lootbagref;

	//spawning location vector in 
	FVector lootspawnloc;

	//func to deal damage by the swordcharacter
	UFUNCTION()
	void swordoverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//paricle to spawn when overlap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "overlapparticlesimpleai |weaponparticle")
	UParticleSystem* weaponparticleoverlap;

	
	//delay to set back to default;
	FTimerHandle swordcanhitdelay;
	void swordcangeneral();
	//weapon colliding one action in two times so use some condition to fix it
	bool swordcanhit;

    //create widget for levelup display
	class Ulevelupwidget* levelupop;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="levelupwidge|widgeref")
	TSubclassOf<Ulevelupwidget> levelupref;
	class UthirdroleGameInstance* Gameinstance;

	

};
