// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_ResetAttack.h"
#include "Characters/GASPaperCharacter.h"
#include "AbilitySystemComponent.h"
#include "PaperZDAnimInstance.h"


UAN_ResetAttack::UAN_ResetAttack()
{
}

void UAN_ResetAttack::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance)
	{
		if (AGASPaperCharacter* Character = Cast<AGASPaperCharacter>(OwningInstance->GetOwningActor()))
		{
			Character->SetIsAttacking(false);
			if (Character->GetAbilitySystemComponent())
			{
				Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.BlockInput")));
				Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Attack.Attack1")));
				Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Attack.Attack2")));
			}
		}
	}
}
