// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "AbilityIDDefine.h"
#include "GASPaperCharacter.generated.h"


class UGameplayEffect;
class UGASGameplayAbility;
class UGASAbilitySystemComponent;
class UAttributeSetBase;
/**
 * 
 */
UCLASS(BlueprintType)
class RIDINGHOOD_API UCharacterConfig : public UDataAsset 
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	TArray<TSubclassOf<UGASGameplayAbility>> DefaultAbilities;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributes;
};

UCLASS()
class RIDINGHOOD_API AGASPaperCharacter : public APaperCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public: 
	AGASPaperCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter")
	virtual int32 GetAbilityLevel(EGASAbilityInputID AbilityInputID) const;

	virtual void RemoveCharacterAbilities();

	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetMaxHealth() const;


	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "GAS|GASCharacter")
	virtual void FinishDying();

protected:

	virtual void BeginPlay() override;

	TWeakObjectPtr<UGASAbilitySystemComponent> ASC;
	TWeakObjectPtr<UAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Config")
	TObjectPtr<UCharacterConfig> CharacterConfig;


	virtual void AddCharacterAbilities();

	virtual void IntializeAttributes();

	virtual void SetHealth(float NewHealth);

	virtual void SetMana(float NewMana);
};
