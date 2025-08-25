// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PaperPlayerState.h"
#include "Characters/Abilities/GASAbilitySystemComponent.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"

APaperPlayerState::APaperPlayerState()
{
	ASC = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ASC->SetIsReplicated(true);

	AttributeSetBase = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSetBase"));

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* APaperPlayerState::GetAbilitySystemComponent() const
{
	if (ASC)
	{
		return ASC;
	}
	return nullptr;
}

UAttributeSetBase* APaperPlayerState::GetAttributeSetBase() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase;
	}
	return nullptr;
}

void APaperPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(ASC)
	{
		HealthChangeDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &APaperPlayerState::HealthChanged);
		MaxHealthChangeDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &APaperPlayerState::MaxHealthChanged);
		ManaChangeDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetManaAttribute()).AddUObject(this, &APaperPlayerState::ManaChanged);
		MaxManaChangeDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxManaAttribute()).AddUObject(this, &APaperPlayerState::MaxManaChanged);
	}
}

void APaperPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float NewHealth = Data.NewValue;
	if (!IsAlive() && !ASC->HasMatchingGameplayTag(DeadTag)) 
	{
	
	}
}
void APaperPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float NewMaxHealth = Data.NewValue;

}

void APaperPlayerState::ManaChanged(const FOnAttributeChangeData& Data)
{
	float NewMana = Data.NewValue;
}

void APaperPlayerState::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	float NewMaxMana = Data.NewValue;
}


bool APaperPlayerState::IsAlive() const
{
	return GetHealth() > 0.f;
}

float APaperPlayerState::GetHealth() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetHealth();
	}
	return 0.0f;
}

float APaperPlayerState::GetMaxHealth() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMaxHealth();
	}
	return 0.0f;
}

float APaperPlayerState::GetMana() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMana();
	}
	return 0.0f;
}

float APaperPlayerState::GetMaxMana() const
{
	if (AttributeSetBase)
	{
		return AttributeSetBase->GetMaxMana();
	}
	return 0.0f;
}
