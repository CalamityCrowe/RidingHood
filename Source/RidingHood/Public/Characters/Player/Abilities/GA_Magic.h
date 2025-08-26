// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Abilities/GASGameplayAbility.h"
#include "GA_Magic.generated.h"

/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UGA_Magic : public UGASGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Magic();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
};
