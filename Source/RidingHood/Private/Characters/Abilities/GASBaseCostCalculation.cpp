// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Abilities/GASBaseCostCalculation.h"
#include "Characters/Abilities/GASGameplayAbility.h"

float UGASBaseCostCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UGASGameplayAbility* Ability = Cast<UGASGameplayAbility>(Spec.GetContext().GetAbility());

    if(!Ability)
    {
        return 0.0f;
    }

    return Ability->Cost.GetValue(); 
}
