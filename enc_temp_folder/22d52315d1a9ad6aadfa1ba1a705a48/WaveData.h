#pragma once

#include "CoreMinimal.h"
#include "WaveData.generated.h"

class AGASEnemyCharacter;

USTRUCT(BlueprintType)
struct FWaveModifiers
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TSubclassOf<AGASEnemyCharacter>, int32> EnemyPool; 
};

USTRUCT(BlueprintType)
struct FWaveeDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FWaveModifiers WaveModifiers;
};