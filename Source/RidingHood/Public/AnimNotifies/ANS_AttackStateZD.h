// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotifyState.h"
#include "GameplayEffect.h"
#include "ANS_AttackStateZD.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Attack Window"))
class RIDINGHOOD_API UANS_AttackStateZD : public UPaperZDAnimNotifyState
{
	GENERATED_BODY()
public: 

	UANS_AttackStateZD();

	virtual void OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const override;
	virtual FName GetDisplayName_Implementation() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack State")
	float CurrentRadius = 100.0f; // Radius of the attack state sphere trace

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack State")
	float Offset = 50.0f; // Offset from the character's location to start the sphere trace

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack State")
	float CurrentDamage = 20.0f; // Damage to apply on hit

protected: 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack State")
	TSubclassOf<UGameplayEffect> DamageEffect;
};
