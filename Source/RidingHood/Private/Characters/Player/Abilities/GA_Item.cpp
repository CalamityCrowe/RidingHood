// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Abilities/GA_Item.h"
#include "AbilityIDDefine.h"
#include "Characters/Player/PaperPlayerCharacter.h"

UGA_Item::UGA_Item()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityID = EGASAbilityInputID::Item;
	AbilityInputID = EGASAbilityInputID::Item;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Item")));
	
}

void UGA_Item::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		if (APaperPlayerCharacter* Player = Cast<APaperPlayerCharacter>(ActorInfo->AvatarActor))
		{
			//TODO: Use Item
		//	Player->UseItem();

			ApplyCooldown(Handle, ActorInfo, ActivationInfo);
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

}

const FGameplayTagContainer* UGA_Item::GetCooldownTags() const
{
	FGameplayTagContainer* MutableTags = const_cast<FGameplayTagContainer*>(&TempCooldownTags);
	MutableTags->Reset();
	const FGameplayTagContainer* ParentTags = Super::GetCooldownTags();
	if (ParentTags)
	{
		MutableTags->AppendTags(*ParentTags);
	}
	return MutableTags;
}

void UGA_Item::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE) 
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel(Handle, ActorInfo));
		SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTags);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Ability.Cooldown")), CooldownDuration.GetValueAtLevel(GetAbilityLevel()));
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}
