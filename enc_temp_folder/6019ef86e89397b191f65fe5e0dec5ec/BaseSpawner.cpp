// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/BaseSpawner.h"
#include "Components/SphereComponent.h"
#include "Characters/Enemies/GASEnemyCharacter.h"
#include "Gamefiles/RidingHoodGameMode.h"

// Sets default values
ABaseSpawner::ABaseSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Collider->SetSphereRadius(50.f);
}

// Called when the game starts or when spawned
void ABaseSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ABaseSpawner::AttemptToSpawn, 2.f, true, 2.f);
}

// Called every frame
void ABaseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
bool ABaseSpawner::SpawnEnemy()
{
	if (EnemyQueue.IsValidIndex(0))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		if (AGASEnemyCharacter* Enemy = GetWorld()->SpawnActor<AGASEnemyCharacter>(EnemyQueue[0], GetActorTransform(), SpawnParams))
		{

			Enemy->OnDeathDelegate.AddDynamic(this, &ABaseSpawner::OnEnemyDefeated);
			EnemyQueue.RemoveAt(0);
			return true;
		}
		return false;
	}
	else
	{
		return false; 
	}


}

void ABaseSpawner::AddEnemyToQueue(TSubclassOf<AGASEnemyCharacter> EnemyClass)
{
	EnemyQueue.Add(EnemyClass);

	TArray<AActor*> OverlappingActors;
	Collider->GetOverlappingActors(OverlappingActors,EnemyClass->StaticClass());
	if (OverlappingActors.IsValidIndex(0)) 
	{
	
	}
	else
	{
		SpawnEnemy();
	}
}

void ABaseSpawner::AttemptToSpawn()
{
	SpawnEnemy(); 
}

void ABaseSpawner::OnEnemyDefeated()
{
	if (ARidingHoodGameMode* GM = Cast<ARidingHoodGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnEnemyDefeated();
	}
}

