// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_ResetHurt.h"
#include "Characters/GASPaperCharacter.h"
#include "AbilitySystemComponent.h"
#include "PaperZDAnimInstance.h"


UAN_ResetHurt::UAN_ResetHurt()
{
}

void UAN_ResetHurt::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if(OwningInstance)
	{
		if (AGASPaperCharacter* Character = Cast<AGASPaperCharacter>(OwningInstance->GetOwningActor())) 
		{
			if (Character->GetAbilitySystemComponent())
			{
				Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Stun")));
				Character->SetIsHurt(false);
			}
		}
	}
}
