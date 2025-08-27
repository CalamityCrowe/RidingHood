// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GASBaseCooldownCalculation.generated.h"

/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UGASBaseCooldownCalculation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

};
