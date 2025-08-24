#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PaperPlayerHUD.generated.h"


class UTextBlock;
class UPaperProgressBar;
class UAttributeSetBase;
class UAsyncTaskAttributeChange;
class UActionDisplayWidget;


UCLASS()
class RIDINGHOOD_API UPaperPlayerHUD : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public: 

	UPaperPlayerHUD();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void InitializeHUDWidget(const UAttributeSetBase* Attributes);

	UFUNCTION()
	void UpdateHealth(FGameplayAttribute Attribute, float NewValue, float MaxValue);
	UFUNCTION()
	void UpdateMana(FGameplayAttribute Attribute, float NewValue, float MaxValue);

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

private: 
	UPROPERTY()
	TObjectPtr<UAsyncTaskAttributeChange> AttributeChangeTask;
};