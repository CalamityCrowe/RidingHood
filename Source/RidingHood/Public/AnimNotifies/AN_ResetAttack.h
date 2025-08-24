// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotify.h"
#include "AN_ResetAttack.generated.h"

/**
 * 
 */
UCLASS()
class RIDINGHOOD_API UAN_ResetAttack : public UPaperZDAnimNotify
{
	GENERATED_BODY()

public: 
	UAN_ResetAttack(); 
	
	void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance = nullptr) const override;


};
