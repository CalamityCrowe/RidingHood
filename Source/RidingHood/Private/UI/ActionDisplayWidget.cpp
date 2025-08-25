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

void UActionDisplayWidget::ButtonPressed(bool Pressed)
{
	
	if (Pressed)
	{
		PlayAnimationForward(PressedAnim); 
		ActionIcon->SetBrushFromTexture(PressedImage,false); // Example of visual feedback
	}
	else
	{
		PlayAnimationReverse(PressedAnim);
		ActionIcon->SetBrushFromTexture(UnPressedImage, false); // Example of visual feedback
	}

	// Additional logic for button press can be added here
}
