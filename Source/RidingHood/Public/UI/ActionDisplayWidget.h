// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionDisplayWidget.generated.h"


class UImage; 
class UTextBlock;
/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UActionDisplayWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public:
	UActionDisplayWidget();

	virtual void NativeConstruct() override; 
	virtual void NativeDestruct() override;

	virtual void SetActionName(FText);

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* ActionIcon;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ActionName;

};
