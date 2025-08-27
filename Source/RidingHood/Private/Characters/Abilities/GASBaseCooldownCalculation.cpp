// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Abilities/GASBaseCooldownCalculation.h"
#include "Characters/Abilities/GASGameplayAbility.h"

float UGASBaseCooldownCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UGASGameplayAbility* Ability = Cast<UGASGameplayAbility>(Spec.GetContext().GetAbility());

	if (!Ability)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UGASBaseCooldownCalculation::CalculateBaseMagnitude_Implementation: Ability is null"));
		return 0.0f;
	}
	return Ability->CooldownDuration.GetValue();
}
