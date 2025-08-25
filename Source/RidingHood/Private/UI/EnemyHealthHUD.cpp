// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyHealthHUD.h"
#include "UI/PaperProgressBar.h"
#include "Components/TextBlock.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "Characters/Abilities/Tasks/AsyncTaskAttributeChange.h"
#include "Characters/GASPaperCharacter.h"

UEnemyHealthHUD::UEnemyHealthHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UEnemyHealthHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEnemyHealthHUD::NativeDestruct()
{
	if (IsValid(AttributeChangeTask)) 
	{
		AttributeChangeTask->EndTask();
	}
	Super::NativeDestruct();
}

void UEnemyHealthHUD::InitializeHUDWidget(const UAttributeSetBase* Attributes, UAbilitySystemComponent* ASC, AActor* OwningActor)
{
	if (Attributes)
	{
		

		HealthBar->SetMaxValue(Attributes->GetMaxHealth());
		HealthBar->UpdateBar(Attributes->GetHealth());

		if (const AGASPaperCharacter* EnemyCharacter = Cast<AGASPaperCharacter>(OwningActor)) 
		{
			TArray<FGameplayAttribute> AttributesToListenFor;
			AttributesToListenFor.Add(UAttributeSetBase::GetHealthAttribute());
			AttributeChangeTask = UAsyncTaskAttributeChange::ListenForAttributesChange(ASC, AttributesToListenFor);
			if (AttributeChangeTask)
			{
				AttributeChangeTask->OnAttributeChanged.AddDynamic(this, &UEnemyHealthHUD::UpdateHealth);
			}
		}
	}
}

void UEnemyHealthHUD::UpdateHealth(FGameplayAttribute Attribute, float CurrentHealth, float MaxHealth)
{
	if (Attribute != UAttributeSetBase::GetHealthAttribute())
	{
		return;
	}
	HealthBar->UpdateBar(CurrentHealth);
}
