// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotify.h"
#include "AN_ResetHurt.generated.h"

/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UAN_ResetHurt : public UPaperZDAnimNotify
{
	GENERATED_BODY()
public:
	UAN_ResetHurt();

	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;
};
