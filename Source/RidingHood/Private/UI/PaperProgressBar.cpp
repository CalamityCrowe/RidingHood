// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PaperProgressBar.h"
#include "Components/ProgressBar.h"


UPaperProgressBar::UPaperProgressBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentMaxValue = 100.f; 
}

void UPaperProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPaperProgressBar::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPaperProgressBar::UpdateBar(float Value)
{
	if(StatBar)
	{
		StatBar->SetPercent(Value / CurrentMaxValue);
	}
}
