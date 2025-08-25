// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PaperPlayerController.h"
#include "Player/PaperPlayerState.h"
#include "AbilitySystemComponent.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "UI/PaperPlayerHUD.h"

APaperPlayerController::APaperPlayerController()
{
}

void APaperPlayerController::CreateHUD()
{
	//TODO
	if (!HUDWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUDWidgetClass is not set!"));
		return;
	}
	if (HUDWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUDWidget is already created!"));
		return;
	}
	// create the HUD for the player controller and get a reference for the class and validate it

	APaperPlayerState* PS = GetPlayerState<APaperPlayerState>();
	if (!PS)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerState is not valid!"));
		return;
	}

	// TODO
	// Create the HUD widget from the reference, assign to the viewport and initialize the HUD
	HUDWidget = CreateWidget<UPaperPlayerHUD>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	HUDWidget->InitializeHUDWidget(PS->GetAttributeSetBase());
}

void APaperPlayerController::RemoveHUD()
{
	if (HUDWidget)
	{
		HUDWidget->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HUD Removed"));
	}
}

void APaperPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	APaperPlayerState* PS = GetPlayerState<APaperPlayerState>();
	if (PS)
	{
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void APaperPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CreateHUD();

}
