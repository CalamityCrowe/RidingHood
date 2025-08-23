// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaperProgressBar.generated.h"


class UProgressBar; 
/**
 * 
 */
UCLASS(abstract)
class RIDINGHOOD_API UPaperProgressBar : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	UPaperProgressBar(); 

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* StatBar;

	UFUNCTION(BlueprintCallable, Category = "Paper|ProgressBar")
	void UpdateBar(float Value); 

	void SetMaxValue(float NewMaxValue)
	{
		CurrentMaxValue = NewMaxValue;
	}
private: 

	float CurrentMaxValue; 
};
