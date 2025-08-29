// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RidingHoodGameMode.generated.h"

class ABaseSpawner; 
class AGASEnemyCharacter;
/**
 * 
 */
UCLASS()
class RIDINGHOOD_API ARidingHoodGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public: 
	ARidingHoodGameMode();

	virtual void BeginPlay() override;


	void GetSpawners();
	void StartWave();
	void NewWave();
	void EndWave();
	void EnterTransition(float Timer);
	void BuildEnemyPool();
	int32 GetPoolSize() const; 
	TSubclassOf<AGASEnemyCharacter> GetEnemyFromPool();
	void OnEnemyDefeated(); 
private:

	TArray<TObjectPtr<ABaseSpawner>> Spawners;
	int32 WaveNumber; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 EnemyMaxCount; 
	int32 EnemyRemaining;

	TMap<TSubclassOf<AGASEnemyCharacter>, int32> EnemyPool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> WaveDataTable;

	FTimerHandle TransitionTimerHandle;
};
