// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/GASEnemyCharacter.h"
#include "Characters/Abilities/GASAbilitySystemComponent.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemyHealthHUD.h"

AGASEnemyCharacter::AGASEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HardASCRef = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("ASC"));
	HardASCRef->SetIsReplicated(true);
	ASC = HardASCRef;

	HardRefAttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));
	AttributeSetBase = HardRefAttributeSet;

	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(RootComponent);
	HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarComponent->SetCastShadow(false);
}

void AGASEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (ASC.IsValid()) 
	{
		ASC->InitAbilityActorInfo(this, this);
		IntializeAttributes();
		SetHealth(GetMaxHealth()); // Set initial health, can be modified as needed

		// TODO : Add Enemy specific UI setup here if needed


		if (UEnemyHealthHUD* HUD = Cast<UEnemyHealthHUD>(HealthBarComponent->GetWidget()))
		{
			HUD->InitializeHUDWidget(HardRefAttributeSet,HardASCRef, this);
		}

		OnHealthChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &AGASEnemyCharacter::OnHealthChanged);

	}
}

void AGASEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


void AGASEnemyCharacter::Die()
{
	Super::Die();

	// Additional logic for enemy death can be added here

}

void AGASEnemyCharacter::FinishDying()
{
	Super::FinishDying();

	// Additional logic for finishing death can be added here, like dropping loot or notifying a spawner
}

void AGASEnemyCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	float NewHealth = Data.NewValue;

	if(!IsAlive() && !ASC->HasMatchingGameplayTag(DeadTag))
	{
		Die();
	}
}
