// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAIStates : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Spawning	UMETA(DisplayName = "Spawning"),
	Attacking	UMETA(DisplayName = "Attacking"),
	Dying		UMETA(DisplayName = "Dead"),
};



UCLASS()
class RIDINGHOOD_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseEnemyController(const FObjectInitializer& ObjectInitializer);
protected: 
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Blackboard|Keys", meta = (AllowPrivateAccess = true))
	FName TargetKeyName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Blackboard|Keys", meta = (AllowPrivateAccess = true))
	FName POIKeyName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Blackboard|Keys", meta = (AllowPrivateAccess = true))
	FName AIStateKeyName;

public: 
	UFUNCTION(BlueprintPure)
	EAIStates GetAIState() const;

	UFUNCTION(BlueprintCallable)
	void SetStateAsAttacking(UObject* AttackTarget);
	UFUNCTION(BlueprintCallable)
	void SetStateAsDying();

	FName GetTargetKeyName() const { return TargetKeyName; }

	UFUNCTION(BlueprintPure)
	AActor* GetTargetActor() const;

};
