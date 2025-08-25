// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_DeathNotify.h"
#include "Characters/GASPaperCharacter.h"
#include "PaperZDAnimInstance.h"

UAN_DeathNotify::UAN_DeathNotify()
{
}

void UAN_DeathNotify::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance) 
	{
		if (AGASPaperCharacter* Character = Cast<AGASPaperCharacter>(OwningInstance->GetOwningActor()))
		{
			Character->FinishDying();
		}
	}
}
