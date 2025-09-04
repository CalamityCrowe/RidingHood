// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ItemDataTable)
	{
		for (auto& Row : ItemDataTable->GetRowMap())
		{
			FName RowName = Row.Key;
			FItemDataRow* ItemData = (FItemDataRow*)Row.Value;

			if (ItemData)
			{
				FInventorySlot NewSlot;
				NewSlot.Item = ItemData->ItemDetails;
				NewSlot.Quantity = 3; // Default quantity, can be modified as needed
				InventoryItems.Add(RowName, NewSlot);
				ItemsOrder.Add(RowName);
			}
		}
		// we grab the list of items to assign to the struct 

		CurrentItem = InventoryItems[ItemsOrder[0]];

	}
	

	// ...
}

void UInventoryComponent::AddItem(FName Item,int32 Amount)
{
	if(FInventorySlot* Slot = InventoryItems.Find(Item))
	{
		Slot->Quantity += Amount; 
	}
}

void UInventoryComponent::NextItem()
{
	if (ItemsOrder.IsEmpty())
	{
		return;
	}
	CurrentItemIndex = (CurrentItemIndex + 1) % ItemsOrder.Num();
	FName ItemID = ItemsOrder[CurrentItemIndex];
	if (FInventorySlot* Slot = InventoryItems.Find(ItemID))
	{
		CurrentItem = *Slot;
	}
}

void UInventoryComponent::PreviousItem()
{
	if (ItemsOrder.IsEmpty())
	{
		return;
	}
	CurrentItemIndex = (CurrentItemIndex - 1) % ItemsOrder.Num();
	FName ItemID = ItemsOrder[CurrentItemIndex];
	if (FInventorySlot* Slot = InventoryItems.Find(ItemID))
	{
		CurrentItem = *Slot;
	}
}

FItemStruct UInventoryComponent::UseItem()
{
	if(CurrentItem.Quantity > 0)
	{
		CurrentItem.Quantity--; 
		return CurrentItem.Item; 
	}
	return FItemStruct(); 
}

UTexture2D* UInventoryComponent::GetCurrentItemIcon() const
{
	return CurrentItem.Item.Icon;
}

int32 UInventoryComponent::GetCurrentItemQuantity() const
{
	return CurrentItem.Quantity;
}