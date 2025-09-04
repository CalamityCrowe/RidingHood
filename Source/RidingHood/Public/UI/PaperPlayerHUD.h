#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaperPlayerHUD.generated.h"


class UTextBlock;
class UPaperProgressBar;
class UAttributeSetBase;
class UAsyncTaskAttributeChange;
class UAsyncTaskCooldownChanged;
class UActionDisplayWidget;
class UItemDisplayWidget; 



UCLASS()
class RIDINGHOOD_API UPaperPlayerHUD : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public: 

	UPaperPlayerHUD();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void InitializeHUDWidget(const UAttributeSetBase* Attributes);

	void SetItemWidget(class UTexture2D* ItemIcon, int32 Quantity);

	UFUNCTION()
	void UpdateHealth(FGameplayAttribute Attribute, float NewValue, float MaxValue);
	UFUNCTION()
	void UpdateMana(FGameplayAttribute Attribute, float NewValue, float MaxValue);

	UFUNCTION()
	void DisplayCooldown(FGameplayTag CooldownTag, float TimeRemaining, float Duration);
	UFUNCTION()
	void HideCooldown(FGameplayTag CooldownTag, float TimeRemaining, float Duration);

protected: 

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPaperProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UPaperProgressBar* ManaBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UActionDisplayWidget* AttackDisplay;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UActionDisplayWidget* MagicDisplay;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UActionDisplayWidget* ItemDisplay;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UActionDisplayWidget* JumpDisplay;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UItemDisplayWidget* ItemWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CooldownText;
private: 
	UPROPERTY()
	TObjectPtr<UAsyncTaskAttributeChange> AttributeChangeTask;
	UPROPERTY()
	TObjectPtr<UAsyncTaskCooldownChanged> CooldownChangeTask;

	FTimerHandle CooldownTimerHandle;
	float CooldownTimeRemaining;
	void UpdateCooldownTimer();
};