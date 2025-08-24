// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_AdjustTags.h"
#include "Characters/GASPaperCharacter.h"
#include "AbilitySystemComponent.h"
#include "PaperZDAnimInstance.h"

UAN_AdjustTags::UAN_AdjustTags()
{
}

void UAN_AdjustTags::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance)
	{
		if (AGASPaperCharacter* Character = Cast<AGASPaperCharacter>(OwningInstance->GetOwningActor()))
		{
			if (TagsToAdd.Num() > 0)
			{
				if (!Character->GetAbilitySystemComponent()->HasAllMatchingGameplayTags(TagsToAdd)) 
				{
					Character->GetAbilitySystemComponent()->AddLooseGameplayTags(TagsToAdd);
				}
			}
			for (const FGameplayTagContainer& Tags : TagsToRemove)
			{
				if(Character->GetAbilitySystemComponent()->HasAllMatchingGameplayTags(Tags))
				Character->GetAbilitySystemComponent()->RemoveLooseGameplayTags(Tags);
			}
		}
	}
}
