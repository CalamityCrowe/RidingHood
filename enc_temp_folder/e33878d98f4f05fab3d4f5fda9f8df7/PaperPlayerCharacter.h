// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/GASPaperCharacter.h"
#include "PaperPlayerCharacter.generated.h"

/**
 * 
 */

class USpringArmComponent;
class UCameraComponent;

class UInputAction;
class UInputMappingContext;


UCLASS(BlueprintType)
class RIDINGHOOD_API UPlayerInputData: public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

};

UCLASS()
class RIDINGHOOD_API APaperPlayerCharacter : public AGASPaperCharacter
{
	GENERATED_BODY()
public: 
	APaperPlayerCharacter(); 

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	FVector2D GetMovementAxis() const { return MoveAxis; }

	UCameraComponent* GetCamera() const { return Camera; }
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Inputs")
	TObjectPtr<UPlayerInputData> PlayerInputData;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void SendAbilityLocalInput(const FInputActionValue& Value, int32 InputID);

private: 

	FVector2D MoveAxis; 

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Magic(const FInputActionValue& Value);
};
