// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemDisplayWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

UItemDisplayWidget::UItemDisplayWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UItemDisplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UItemDisplayWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UItemDisplayWidget::UpdateItemDisplay(UTexture2D* ItemIcon, int32 Quantity)
{
	if (ItemIconImage)
	{
		ItemIconImage->SetBrushFromTexture(ItemIcon);
	}
	if (ItemQuantityText)
	{
		ItemQuantityText->SetText(FText::AsNumber(Quantity));
	}
}
