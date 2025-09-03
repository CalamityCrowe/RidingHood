// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/StartMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/VerticalBox.h"
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
		StartGameButton->OnHovered.AddDynamic(this, &UStartMenuWidget::OnStartHovered);
		StartGameButton->OnUnhovered.AddDynamic(this, &UStartMenuWidget::OnStartUnhovered);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnOptionsClicked);
		OptionsButton->OnHovered.AddDynamic(this, &UStartMenuWidget::OnOptionsHovered);
		OptionsButton->OnUnhovered.AddDynamic(this, &UStartMenuWidget::OnOptionsUnhovered);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UStartMenuWidget::OnExitGameClicked);
		ExitGameButton->OnHovered.AddDynamic(this, &UStartMenuWidget::OnExitHovered);
		ExitGameButton->OnUnhovered.AddDynamic(this, &UStartMenuWidget::OnExitUnhovered);
	}

	MaxIndex = MenuBox->GetChildrenCount() - 1;
	CurrentIndex = 0;

}

void UStartMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UStartMenuWidget::OnStartGameClicked()
{

	if (LevelToLoad.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelToLoad is not valid!"));
		return;
	}	
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelToLoad);
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

void UStartMenuWidget::OnStartHovered()
{
	CurrentIndex = 0;
	PlayAnimationForward(StartSelectedAnim);
}

void UStartMenuWidget::OnOptionsHovered()
{
	CurrentIndex = 1;
	PlayAnimationForward(OptionsSelectedAnim);
}

void UStartMenuWidget::OnExitHovered()
{
	CurrentIndex = 2;
	PlayAnimationForward(ExitSelectedAnim);
}

void UStartMenuWidget::OnStartUnhovered()
{
	PlayAnimationReverse(StartSelectedAnim);
}

void UStartMenuWidget::OnOptionsUnhovered()
{
	PlayAnimationReverse(OptionsSelectedAnim);
}

void UStartMenuWidget::OnExitUnhovered()
{
	PlayAnimationReverse(ExitSelectedAnim);
}

void UStartMenuWidget::MenuSelectionUp()
{
	CurrentIndex--;
	if (CurrentIndex < 0)
	{
		CurrentIndex = MaxIndex;
	}
	switch (CurrentIndex)
	{
	case 0:
		PlayAnimationForward(StartSelectedAnim);
		PlayAnimationReverse(OptionsSelectedAnim);
		break;
	case 1:
		PlayAnimationForward(OptionsSelectedAnim);
		PlayAnimationReverse(ExitSelectedAnim);
		break;
	case 2:
		PlayAnimationForward(ExitSelectedAnim);
		PlayAnimationReverse(StartSelectedAnim);
		break;
	default:
		break;
	}

}

void UStartMenuWidget::MenuSelectionDown()
{
	CurrentIndex++;
	if (CurrentIndex > MaxIndex)
	{
		CurrentIndex = 0;
	}
	switch (CurrentIndex)
	{
	case 0:
		PlayAnimationForward(StartSelectedAnim);
		PlayAnimationReverse(ExitSelectedAnim);
		break;
	case 1:
		PlayAnimationForward(OptionsSelectedAnim);
		PlayAnimationReverse(StartSelectedAnim);
		break;
	case 2:
		PlayAnimationForward(ExitSelectedAnim);
		PlayAnimationReverse(OptionsSelectedAnim);
		break;
	}
}

void UStartMenuWidget::MenuSelect()
{
	switch (CurrentIndex)
	{
	case 0:
		OnStartGameClicked();
		break;
	case 1:
		OnOptionsClicked();
		break;
	case 2:
		OnExitGameClicked();
		break;
	default:
		break;
	}
}
