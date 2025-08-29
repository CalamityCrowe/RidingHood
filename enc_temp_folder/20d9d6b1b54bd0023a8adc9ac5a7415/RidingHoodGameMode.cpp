// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamefiles/RidingHoodGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Enemies/BaseSpawner.h"
#include "Characters/Enemies/GASEnemyCharacter.h"
#include "Enemies/WaveData.h"

ARidingHoodGameMode::ARidingHoodGameMode()
{
	EnemyMaxCount = 5; 
}

void ARidingHoodGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetSpawners();
	NewWave();
}

void ARidingHoodGameMode::GetSpawners()
{
	TArray<AActor*> FoundSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseSpawner::StaticClass(), FoundSpawners);

	for (AActor* Actor : FoundSpawners)
	{
		ABaseSpawner* Spawner = Cast<ABaseSpawner>(Actor);
		if (Spawner)
		{
			Spawners.Add(Spawner);
		}
	}
}

void ARidingHoodGameMode::StartWave()
{
	BuildEnemyPool();
	for (int32 i = 0; i < FMath::Min(GetPoolSize(), EnemyMaxCount); i++) 
	{
		Spawners[FMath::RandRange(0, Spawners.Num() - 1)]->AddEnemyToQueue(GetEnemyFromPool());

	}
}

void ARidingHoodGameMode::NewWave()
{
	WaveNumber++;
	StartWave();
}

void ARidingHoodGameMode::EndWave()
{
}

void ARidingHoodGameMode::EnterTransition(float Timer)
{
	GetWorld()->GetTimerManager().SetTimer(TransitionTimerHandle, this, &ARidingHoodGameMode::NewWave, Timer, false);
}

void ARidingHoodGameMode::BuildEnemyPool()
{
	FName RowName = FName(*FString::FromInt(WaveNumber));

	if (WaveDataTable)
	{
		if (FWaveDataRow* WaveData = WaveDataTable->FindRow<FWaveDataRow>(RowName, TEXT(""))) 
		{
			EnemyPool = WaveData->WaveModifiers.EnemyPool;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No data found for wave number: %d"), WaveNumber);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("WaveDataTable is not assigned in the GameMode"));
	}

	EnemyRemaining = GetPoolSize();
}

int32 ARidingHoodGameMode::GetPoolSize() const
{
	int32 LocalSum = 0;
	TArray<int32> Values;
	EnemyPool.GenerateValueArray(Values);
	for (int32 Value : Values)
	{
		LocalSum += Value;
	}
	return LocalSum;
}

TSubclassOf<AGASEnemyCharacter> ARidingHoodGameMode::GetEnemyFromPool()
{
	TArray<TSubclassOf<AGASEnemyCharacter>> Keys;
	EnemyPool.GetKeys(Keys);
	TSubclassOf<AGASEnemyCharacter> SelectedEnemy = Keys[FMath::RandRange(0, Keys.Num() - 1)];
	int32* Value = EnemyPool.Find(SelectedEnemy);
	if(Value)
	{
		*Value--; 
		if (*Value > 0) 
		{
			EnemyPool.Add(SelectedEnemy, *Value);
		}
		else
		{
			EnemyPool.Remove(SelectedEnemy); 
		}
	}

	return SelectedEnemy;
}

void ARidingHoodGameMode::OnEnemyDefeated()
{
	EnemyRemaining--; 
	if (EnemyRemaining < EnemyMaxCount)
	{
		if (EnemyRemaining <= 0) 
		{
			EnterTransition(5); 
		}
	}
	else
	{
		Spawners[FMath::RandRange(0, Spawners.Num() - 1)]->AddEnemyToQueue(GetEnemyFromPool());
	}
}
