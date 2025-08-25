// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PaperMenuWidget.h"
#include "Components/WidgetSwitcher.h"

UPaperMenuWidget::UPaperMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UPaperMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MenuSwitcher->SetActiveWidgetIndex(0);
}

void UPaperMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
