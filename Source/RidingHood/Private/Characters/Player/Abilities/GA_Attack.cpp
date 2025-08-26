// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Abilities/GA_Attack.h"
#include "Characters/GASPaperCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


UGA_Attack::UGA_Attack()
{
	// Set this ability to be activated by the player
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	AbilityID = EGASAbilityInputID::Ability1;
	AbilityInputID = EGASAbilityInputID::Ability1;

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.BlockInput")));
}

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (AGASPaperCharacter* Character = Cast<AGASPaperCharacter>(ActorInfo->AvatarActor.Get())) 
	{
		if (Character->GetCharacterMovement()->IsFalling()) 
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
			return;
		} // Don't allow attacking while in air (jumping

		if (CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
			if (ASC)
			{
				Character->SetIsAttacking(true);
				if (!ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Attack.Attack1"))))
				{
					ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.BlockInput")));
					ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Attack.Attack1")));
					EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
					return;
				}
				if (!ASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Attack.Attack2"))))
				{
					ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Attack.Attack2")));
					EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
					return;
				}
			}
		}
	
	}

	// End the ability immediately after activation for this example
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
