#include "UI/PaperPlayerHUD.h"
#include "Components/TextBlock.h"
#include "UI/PaperProgressBar.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "Characters/Abilities/Tasks/AsyncTaskAttributeChange.h"
#include "Characters/Abilities/Tasks/AsyncTaskCooldownChanged.h"
#include "Player/PaperPlayerState.h"
#include "Kismet/KismetMathLibrary.h"


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

		FGameplayTagContainer CooldownTags;
		CooldownTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Item")));

		CooldownChangeTask = UAsyncTaskCooldownChanged::ListenForCooldownChange(PS->GetAbilitySystemComponent(),CooldownTags, false);
		if (CooldownChangeTask)
		{
			// You can bind to cooldown start/end events here if needed
			CooldownChangeTask->OnCooldownBegin.AddDynamic(this, &UPaperPlayerHUD::DisplayCooldown);
			CooldownChangeTask->OnCooldownEnd.AddDynamic(this, &UPaperPlayerHUD::HideCooldown);
		}
	}
}

void UPaperPlayerHUD::NativeDestruct()
{
	if (IsValid(AttributeChangeTask)) 
	{
		AttributeChangeTask->EndTask();
	}
	if (IsValid(CooldownChangeTask))
	{
		CooldownChangeTask->EndTask();
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

void UPaperPlayerHUD::DisplayCooldown(FGameplayTag CooldownTag, float TimeRemaining, float Duration)
{

	CooldownTimeRemaining = TimeRemaining;
	int32 Seconds = UKismetMathLibrary::Round(TimeRemaining);
	FText CooldownTextValue = FText::FromString(FString::Printf(TEXT("%d"),Seconds ));
	CooldownText->SetText(CooldownTextValue);
	CooldownText->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UPaperPlayerHUD::UpdateCooldownTimer, 0.1f, true);
}

void UPaperPlayerHUD::HideCooldown(FGameplayTag CooldownTag, float TimeRemaining, float Duration)
{
	if (CooldownTag != FGameplayTag::RequestGameplayTag(FName("Ability.Cooldown")))
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
	CooldownText->SetVisibility(ESlateVisibility::Hidden);
}

void UPaperPlayerHUD::UpdateCooldownTimer()
{
	int32 Seconds = UKismetMathLibrary::Round(CooldownTimeRemaining);
	FText CooldownTextValue = FText::FromString(FString::Printf(TEXT("%d"), Seconds));	CooldownText->SetText(CooldownTextValue);
	CooldownTimeRemaining -= 0.1f;
	if (CooldownTimeRemaining <= 0.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandle);
		CooldownText->SetVisibility(ESlateVisibility::Hidden);
	}
}
