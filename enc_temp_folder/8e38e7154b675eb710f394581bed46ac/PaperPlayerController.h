// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaperPlayerController.generated.h"

/**
 *
 */
UCLASS()
class RIDINGHOOD_API APaperPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	APaperPlayerController();

	void CreateHUD();

protected:

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UPaperPlayerHUD> HUDWidgetClass;

	TObjectPtr<UPaperPlayerHUD> HUDWidget;

};
