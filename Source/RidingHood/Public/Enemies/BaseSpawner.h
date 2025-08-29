// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"

class USphereComponent;
class AGASEnemyCharacter;




UCLASS()
class RIDINGHOOD_API ABaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
	bool SpawnEnemy();

	void AddEnemyToQueue(TSubclassOf<AGASEnemyCharacter> EnemyRef); 



private: 

	UPROPERTY(EditDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> Collider;

	UPROPERTY(EditAnywhere, Category = "Enemy Queue", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AGASEnemyCharacter>> EnemyQueue;


	FTimerHandle SpawnTimerHandle;

	void AttemptToSpawn(); 
	UFUNCTION()
	void OnEnemyDefeated();
};
