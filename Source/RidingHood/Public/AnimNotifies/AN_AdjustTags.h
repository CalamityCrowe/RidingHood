// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotify.h"
#include "GameplayTagContainer.h"
#include "AN_AdjustTags.generated.h"

/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UAN_AdjustTags : public UPaperZDAnimNotify
{
	GENERATED_BODY()
public: 
	UAN_AdjustTags();

	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer TagsToAdd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	TArray<FGameplayTagContainer> TagsToRemove;

};
