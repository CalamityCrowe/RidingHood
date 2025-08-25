#include "UI/PaperPlayerHUD.h"
#include "Components/TextBlock.h"
#include "UI/PaperProgressBar.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "Characters/Abilities/Tasks/AsyncTaskAttributeChange.h"
#include "Player/PaperPlayerState.h"

UPaperPlayerHUD::UPaperPlayerHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UPaperPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
	APaperPlayerState* PS = GetOwningPlayerState<APaperPlayerState>();
	if (PS) 
	{
		TArray<FGameplayAttribute> AttributesToListenFor;
		AttributesToListenFor.Add(UAttributeSetBase::GetHealthAttribute());
		AttributesToListenFor.Add(UAttributeSetBase::GetManaAttribute());
		AttributeChangeTask = UAsyncTaskAttributeChange::ListenForAttributesChange(PS->GetAbilitySystemComponent(), AttributesToListenFor);
		if(AttributeChangeTask)
		{
			AttributeChangeTask->OnAttributeChanged.AddDynamic(this, &UPaperPlayerHUD::UpdateHealth);
			AttributeChangeTask->OnAttributeChanged.AddDynamic(this, &UPaperPlayerHUD::UpdateMana);
		}
		
	}
}

void UPaperPlayerHUD::NativeDestruct()
{
	if (IsValid(AttributeChangeTask)) 
	{
		AttributeChangeTask->EndTask();
	}
	Super::NativeDestruct();	
}

void UPaperPlayerHUD::InitializeHUDWidget(const UAttributeSetBase* Attributes)
{
	float Health = Attributes->GetHealth();
	float MaxHealth = Attributes->GetMaxHealth();

	HealthBar->SetMaxValue(MaxHealth);
	HealthBar->UpdateBar(Health);

	ManaBar->SetMaxValue(Attributes->GetMaxMana());
	ManaBar->UpdateBar(Attributes->GetMana());

	// TODO: Initialize Mana Bar similarly
}

void UPaperPlayerHUD::UpdateHealth(FGameplayAttribute Attribute, float NewValue, float MaxValue)
{
	if (Attribute != UAttributeSetBase::GetHealthAttribute()) 
	{
		return;
	}
	HealthBar->UpdateBar(NewValue);
}

void UPaperPlayerHUD::UpdateMana(FGameplayAttribute Attribute, float NewValue, float MaxValue)
{
	if (Attribute != UAttributeSetBase::GetManaAttribute())
	{
		return;
	}
	ManaBar->UpdateBar(NewValue);
}
