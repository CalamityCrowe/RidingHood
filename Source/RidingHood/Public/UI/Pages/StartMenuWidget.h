// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"


class UButton;
/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UStartMenuWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()
public: 
	UStartMenuWidget(); 

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable, Category = "StartMenu")
	void OnStartGameClicked();

	UFUNCTION(BlueprintCallable, Category = "StartMenu")
	void OnOptionsClicked();

	UFUNCTION(BlueprintCallable, Category = "StartMenu")
	void OnExitGameClicked();
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;
};
