// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"


class UButton;
class UVerticalBox;
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

	UFUNCTION()
	void OnStartGameClicked();
	UFUNCTION()
	void OnOptionsClicked();
	UFUNCTION()
	void OnExitGameClicked();
	UFUNCTION()
	void OnStartHovered();
	UFUNCTION()
	void OnOptionsHovered();
	UFUNCTION()
	void OnExitHovered();

	UFUNCTION()
	void OnStartUnhovered();
	UFUNCTION()
	void OnOptionsUnhovered();
	UFUNCTION()
	void OnExitUnhovered();


	UFUNCTION(BlueprintCallable)
	void MenuSelectionUp();
	UFUNCTION(BlueprintCallable)
	void MenuSelectionDown();
	UFUNCTION(BlueprintCallable)
	void MenuSelect();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OptionsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitGameButton;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MenuBox;

	UPROPERTY(EditDefaultsOnly, Category = "Level")
	TSoftObjectPtr<UWorld> LevelToLoad;
	

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> StartSelectedAnim;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OptionsSelectedAnim;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ExitSelectedAnim;

	int32 CurrentIndex;
	int32 MaxIndex;
};
