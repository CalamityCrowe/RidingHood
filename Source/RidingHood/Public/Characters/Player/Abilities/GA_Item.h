// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Abilities/GASGameplayAbility.h"
#include "GA_Item.generated.h"

/**
 * 
 */
UCLASS(abstract)
class RIDINGHOOD_API UGA_Item : public UGASGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Item();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	const FGameplayTagContainer* GetCooldownTags() const override; 

	void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
};
