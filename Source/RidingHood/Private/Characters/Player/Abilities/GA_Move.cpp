// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Abilities/GA_Move.h"
#include "Characters/Player/PaperPlayerCharacter.h"
#include <Kismet/KismetMathLibrary.h>

UGA_Move::UGA_Move()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	// Set the ability input ID and ability ID
	AbilityInputID = EGASAbilityInputID::Move;
	AbilityID = EGASAbilityInputID::Move;
}

void UGA_Move::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (APaperPlayerCharacter* PlayerCharacter = Cast<APaperPlayerCharacter>(ActorInfo->AvatarActor.Get()))
	{
		if (CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			FVector2D Axis = PlayerCharacter->GetMovementAxis();
			FRotator ControlRotation = PlayerCharacter->GetControlRotation();
			const FVector XWorldVector = UKismetMathLibrary::GetRightVector(FRotator(0, ControlRotation.Yaw, ControlRotation.Roll));
			const FVector YWorldVector = UKismetMathLibrary::GetForwardVector(FRotator(0, ControlRotation.Yaw, 0));
			PlayerCharacter->AddMovementInput(XWorldVector, Axis.X, false);
			PlayerCharacter->AddMovementInput(YWorldVector, Axis.Y, false);
		}
	}
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
