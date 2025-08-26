// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/StartMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetSwitcher.h"


UStartMenuWidget::UStartMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UStartMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnStartGameClicked);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnOptionsClicked);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnExitGameClicked);
	}

}

void UStartMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UStartMenuWidget::OnStartGameClicked()
{
	if (!LevelToLoad.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelToLoad is not valid!"));
		return;
	}
	UGameplayStatics::OpenLevelBySoftObjectPtr(this,LevelToLoad);

}

void UStartMenuWidget::OnOptionsClicked()
{
	if (UWidgetSwitcher* Switch = Cast<UWidgetSwitcher>(GetParent())) 
	{
		Switch->SetActiveWidgetIndex(1);
	}
}

void UStartMenuWidget::OnExitGameClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false); 
}
