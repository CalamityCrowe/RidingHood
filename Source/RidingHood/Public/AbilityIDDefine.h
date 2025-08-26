#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM(BlueprintType)
enum class EGASAbilityInputID : uint8
{
	None			UMETA(DisplayName = "None"),
	Confirm			UMETA(DisplayName = "Confirm"),
	Cancel			UMETA(DisplayName = "Cancel"),
	Ability1		UMETA(DisplayName = "Ability 1"),
	Ability2		UMETA(DisplayName = "Ability 2"),
	Item			UMETA(DisplayName = "Item"),
	Move 			UMETA(DisplayName = "Move"),
	Look 			UMETA(DisplayName = "Look"),
	Jump 			UMETA(DisplayName = "Jump")

};