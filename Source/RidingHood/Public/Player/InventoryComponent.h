// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName Name = "Not Set";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<UGameplayEffect> ItemEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float Cooldown;
};

USTRUCT(BlueprintType)
struct FInventorySlot 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	FItemStruct Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Slot")
	int32 Quantity;

};

USTRUCT(BlueprintType)
struct FItemDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FItemStruct ItemDetails;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RIDINGHOOD_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:

public: 

	virtual void BeginPlay() override;

	void AddItem(FName,int32); 
	void NextItem(); 
	void PreviousItem(); 
	FInventorySlot* UseItem(); 

	UFUNCTION(BlueprintPure)
	UTexture2D* GetCurrentItemIcon() const;
	UFUNCTION(BlueprintPure)
	int32 GetCurrentItemQuantity() const;

protected: 


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TMap<FName, FInventorySlot> InventoryItems;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = true))
	int32 StartingItems = 3;

	TArray<FName> ItemsOrder; 
	int32 CurrentItemIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = true))
	TObjectPtr<UDataTable> ItemDataTable;

	FInventorySlot* CurrentItem;

};
