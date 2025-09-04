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
class UInventoryComponent;

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
	TObjectPtr<UInputAction> JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> AttackAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MagicAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> ItemAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> NextItemAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> PreviousItemAction;

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

	virtual void Die() override;
	virtual void FinishDying() override;

	bool IsCasting() const { return bIsCasting; }
	void SetIsCasting(bool bNewIsCasting) { bIsCasting = bNewIsCasting; }

	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Camera")
	TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Inputs")
	TObjectPtr<UPlayerInputData> PlayerInputData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInventoryComponent> InventoryComponent;
	

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual void SendAbilityLocalInput(const FInputActionValue& Value, int32 InputID);

private: 

	FVector2D MoveAxis; 

	bool bIsCasting; 

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Magic(const FInputActionValue& Value);

	UFUNCTION()
	void Attack(const FInputActionValue& Value);

	UFUNCTION()
	void Item(const FInputActionValue& Value);
	
	UFUNCTION()
	void NextItem(const FInputActionValue& Value); 
	UFUNCTION()
	void PreviousItem(const FInputActionValue& Value);

	virtual void Jump() override;
};
