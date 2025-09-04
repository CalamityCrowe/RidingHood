// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Abilities/GA_Item.h"
#include "AbilityIDDefine.h"
#include "Characters/Player/PaperPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Player/InventoryComponent.h"

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
	if (APaperPlayerCharacter* Player = Cast<APaperPlayerCharacter>(ActorInfo->AvatarActor))
	{
		FInventorySlot*  UsedItem = Player->GetInventoryComponent()->UseItem(); 
		if(!UsedItem)
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		}
		UsedItem->Quantity--; 
		CooldownDuration = UsedItem->Item.Cooldown; 
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return; 
		}
		if (UsedItem->Item.ItemEffect) 
		{
			FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(UsedItem->Item.ItemEffect, GetAbilityLevel(Handle, ActorInfo));

			FGameplayEffectContextHandle EffectContext = SpecHandle.Data.Get()->GetEffectContext();
			EffectContext.AddSourceObject(Player);
			
			SpecHandle.Data.Get()->SetContext(EffectContext);

			Player->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
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
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Ability.Cooldown")), CooldownDuration.GetValueAtLevel(GetAbilityLevel(Handle, ActorInfo)));
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}
