// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaperMenuWidget.generated.h"

class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UPaperMenuWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UPaperMenuWidget();
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;
};
