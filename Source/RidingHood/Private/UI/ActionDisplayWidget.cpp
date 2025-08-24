// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActionDisplayWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UActionDisplayWidget::UActionDisplayWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UActionDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UActionDisplayWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UActionDisplayWidget::SetActionName(FText NewAction)
{
	if (ActionName) 
	{
		ActionName->SetText(NewAction);
	}
}
