// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pages/StartMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

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

}

void UStartMenuWidget::OnOptionsClicked()
{
}

void UStartMenuWidget::OnExitGameClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false); 
}
