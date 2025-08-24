// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Abilities/GASGameplayAbility.h"
#include "GA_Attack.generated.h"

/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UGA_Attack : public UGASGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Attack();

	// Called when the ability is activated
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


};
