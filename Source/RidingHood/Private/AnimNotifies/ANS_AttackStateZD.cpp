// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_AttackStateZD.h"

UANS_AttackStateZD::UANS_AttackStateZD()
{
#if WITH_EDITORONLY_DATA
	Color = FColor(255, 0, 0, 255); // Red color for attack state
#endif
}


void UANS_AttackStateZD::OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const
{
	// we do the hit logic stuff in here
}

FName UANS_AttackStateZD::GetDisplayName_Implementation() const
{
	return Super::GetDisplayName_Implementation();
}
