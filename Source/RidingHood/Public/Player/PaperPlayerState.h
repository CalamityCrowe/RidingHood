// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "PaperPlayerState.generated.h"

class UGASAbilitySystemComponent;
class UAttributeSetBase;

/**
 * 
 */
UCLASS()
class RIDINGHOOD_API APaperPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public: 
	APaperPlayerState();

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintPure, Category = "GAS|PlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintPure, Category = "GAS|PlayerState")
	float GetHealth() const;
	UFUNCTION(BlueprintPure, Category = "GAS|PlayerState")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintPure, Category = "GAS|PlayerState")
	float GetMana() const;
	UFUNCTION(BlueprintPure, Category = "GAS|PlayerState")
	float GetMaxMana() const;


protected: 

	UPROPERTY()
	TObjectPtr<UGASAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<UAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag; 

	FDelegateHandle HealthChangeDelegateHandle;
	FDelegateHandle MaxHealthChangeDelegateHandle;
	FDelegateHandle ManaChangeDelegateHandle;
	FDelegateHandle MaxManaChangeDelegateHandle;

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
};
