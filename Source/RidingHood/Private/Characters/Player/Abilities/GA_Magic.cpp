// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Abilities/GA_Magic.h"
#include "AbilityIDDefine.h"

UGA_Magic::UGA_Magic()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityID = EGASAbilityInputID::Ability2;
	AbilityInputID = EGASAbilityInputID::Ability2;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Ability2")));
}

void UGA_Magic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		ApplyCost(Handle, ActorInfo, ActivationInfo);

		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}
}

void UGA_Magic::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CostGE = GetCostGameplayEffect();
	if (CostGE)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CostGE->GetClass(), GetAbilityLevel(Handle, ActorInfo));
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(CostTag, Cost.GetValueAtLevel(GetAbilityLevel()));
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}
