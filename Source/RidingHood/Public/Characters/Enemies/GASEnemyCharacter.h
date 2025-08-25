// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GASPaperCharacter.h"
#include "GameplayEffectTypes.h"
#include "GASEnemyCharacter.generated.h"

class UWidgetComponent; 
/**
 * 
 */
UCLASS()
class RIDINGHOOD_API AGASEnemyCharacter : public AGASPaperCharacter
{
	GENERATED_BODY()
public: 
	AGASEnemyCharacter();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Die() override;

	virtual void FinishDying() override;

private: 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> HealthBarComponent;

	UPROPERTY()
	class UAttributeSetBase* HardRefAttributeSet = nullptr;
	UPROPERTY()
	class UGASAbilitySystemComponent* HardASCRef = nullptr;

	FDelegateHandle OnHealthChangedDelegateHandle;

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
};
