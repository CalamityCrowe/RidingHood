// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthHUD.generated.h"

class UPaperProgressBar; 
class UTextBlock;
class UAsyncTaskAttributeChange;
class UAttributeSetBase;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UEnemyHealthHUD : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UEnemyHealthHUD();

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void InitializeHUDWidget(const UAttributeSetBase* Attributes,UAbilitySystemComponent* ASC, AActor* OwningActor);

	UFUNCTION()
	void UpdateHealth(FGameplayAttribute Attribute, float CurrentHealth, float MaxHealth);
protected: 
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UPaperProgressBar> HealthBar;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> EnemyName;

private: 
	UPROPERTY()
	TObjectPtr<UAsyncTaskAttributeChange> AttributeChangeTask;
};
