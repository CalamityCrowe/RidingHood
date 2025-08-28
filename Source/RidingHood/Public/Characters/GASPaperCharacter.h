// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	FVector FaceRightOffset = FVector(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	FVector FaceLeftOffset = FVector(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	FRotator FaceRightRotation = FRotator(0.f, 0.f, 0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite")
	FRotator FaceLeftRotation = FRotator(0.f, 180.f, 0.f);
	

};

UCLASS()
class RIDINGHOOD_API AGASPaperCharacter : public APaperZDCharacter, public IAbilitySystemInterface
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
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetMana() const;
	UFUNCTION(BlueprintPure, Category = "GAS|GASCharacter|Attributes")
	float GetMaxMana() const;


	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "GAS|GASCharacter")
	virtual void FinishDying();

	UFUNCTION(BlueprintPure)
	bool IsAttacking() const { return bIsAttacking; }

	void SetIsAttacking(bool bNewIsAttacking) { bIsAttacking = bNewIsAttacking; }

	UFUNCTION()
	void StartHitStop(float Time);

	void StopHitStop();

protected:

	virtual void BeginPlay() override;

	TWeakObjectPtr<UGASAbilitySystemComponent> ASC;
	TWeakObjectPtr<UAttributeSetBase> AttributeSetBase;

	FGameplayTag DeadTag;

	FTimerHandle HitStopTimerHandle;

	bool bIsAttacking = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Config")
	TObjectPtr<UCharacterConfig> CharacterConfig;



	void Tick(float DeltaSeconds) override;


	virtual void AddCharacterAbilities();

	virtual void IntializeAttributes();

	virtual void SetHealth(float NewHealth);

	virtual void SetMana(float NewMana);
};
