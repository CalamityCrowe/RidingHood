// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDisplayWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UItemDisplayWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UItemDisplayWidget(); 

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void UpdateItemDisplay(UTexture2D* ItemIcon, int32 Quantity);

protected: 

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantityText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> ItemIconImage;
};
