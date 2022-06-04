// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAicontroller.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Swordmancharacter.h"
#include "RoleplayingTutorialCharacter.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "SimpleAI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/LatentActionManager.h"

#include <time.h>

AEnemyAicontroller::AEnemyAicontroller() {
	//for delay of focus on player
}

void AEnemyAicontroller::BeginPlay() {
	Super::BeginPlay();
	//initailize enmy seen the player
	playerseen = false;
	//ai randommovement
	enemymoving = false;
	//navigation system to be enabled to get reach random location
	Navsystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (Navsystem) {
		//UE_LOG(LogTemp, Warning, TEXT("navsystem works"));
	}
	player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	enemyaidup = Cast<ASimpleAI>(GetPawn());
	if (enemyaidup) {
		//UE_LOG(LogTemp, Warning, TEXT("enemydup ref"));
	}
	followrandomness();
	//focus boolean
	focusbol = true;
	focus = true;
	int32 a = 60;
}

void AEnemyAicontroller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//timertickdele.BindUFunction(this, FName("followrandomness"));
	//GetWorldTimerManager().SetTimerForNextTick(timertickdele);
	//function proceeeded from simple ai when seen player
	if (playerseen) {
		//UE_LOG(LogTemp, Warning, TEXT("playerseeen  works"));
		enemymoving = true;
		player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		ASwordmancharacter* sworddup = Cast<ASwordmancharacter>(player);
		if (sworddup) {
			chardup = sworddup;
			//UE_LOG(LogTemp, Warning, TEXT("swordup ref"));
		}
		ARoleplayingTutorialCharacter* Roledup = Cast<ARoleplayingTutorialCharacter>(player);
		if (Roledup) {
			chardup = Roledup;
			//UE_LOG(LogTemp, Warning, TEXT("Roleup ref"));
		}
		Followai.SetGoalActor(chardup);
		Followai.SetAcceptanceRadius(0.5f);
		Followai.SetUsePathfinding(true);
		movetotarget();
	}
}

void AEnemyAicontroller::movetotarget()
{
	if (focus) {
		GetWorldTimerManager().SetTimerForNextTick(this, &AEnemyAicontroller::settingfocuslos);
	}
	else {
		movefocus();
	}
	//MoveTo(Followai, &Navpath);
	//setup losing focus on player for particular time
}

void AEnemyAicontroller::followrandomness()
{
	FVector result;
	//UE_LOG(LogTemp, Warning, TEXT("followrandom ref"));
	if (!enemymoving) {
		if (getrandomlocation(enemyaidup->GetActorLocation(), 1000.f, result)) {
			//UE_LOG(LogTemp, Warning, TEXT("true ref"));
			MoveToLocation(result);
		}
	}
	
}

bool AEnemyAicontroller::getrandomlocation(const FVector& Origin, float Radius, FVector& OutResult)
{
	//location is new random location
	FVector newresult;

	navsuccess=Navsystem->K2_GetRandomReachablePointInRadius(GetWorld(),Origin,newresult,Radius);
	OutResult = newresult;//it is procedure already been in blueprint in c++ looking different initialization
	return navsuccess;
}

void AEnemyAicontroller::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	followrandomness();
}

void AEnemyAicontroller::settingfocuslos()
{
	UE_LOG(LogTemp, Warning, TEXT("settingfocus"));
	if (focusbol) {
		UE_LOG(LogTemp, Warning, TEXT("focusbol  works"));
		GetCharacter()->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		SetFocus(chardup);
		MoveToActor(chardup);
		focusbol = false;
	}
	focus = false;
	a--;
}

void AEnemyAicontroller::movefocus()
{
	UE_LOG(LogTemp, Warning, TEXT("focus not works"));
	SetFocus(NULL);
	MoveToActor(NULL);
	GetCharacter()->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	focusbol = true;
	if (a <= 0) {
		focus = true;
	}
}
