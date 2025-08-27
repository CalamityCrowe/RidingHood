// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Abilities/GA_Magic.h"
#include "AbilityIDDefine.h"
#include "Characters/Player/PaperPlayerCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Projectiles/GASProjectileBase.h"

UGA_Magic::UGA_Magic()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	AbilityID = EGASAbilityInputID::Ability2;
	AbilityInputID = EGASAbilityInputID::Ability2;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill.Ability2")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Attack")));
}

void UGA_Magic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (GetOwningActorFromActorInfo())
	{
		APaperPlayerCharacter* Player = Cast<APaperPlayerCharacter>(GetAvatarActorFromActorInfo());
		if (Player)
		{
			if (Player->IsCasting())
			{
				EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
				return;
			}
			Player->SetIsCasting(true);

			FVector Start = Player->GetSprite()->GetComponentLocation();
			FVector Forward = Player->GetSprite()->GetRightVector();
			FVector End = Start + Forward;

			FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel(Handle, ActorInfo));

			SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage.GetValueAtLevel(GetAbilityLevel()));

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			if (AGASProjectileBase* Projectile = GetWorld()->SpawnActor<AGASProjectileBase>(ProjectileClass, Start, FRotator::ZeroRotator, SpawnParams))
			{
				Projectile->InitProjectile(Speed.GetValue(), Range.GetValue(), Forward);
				Projectile->DamageEffect = SpecHandle;
				Projectile->SetInstigator(Player);
			}
		}
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


