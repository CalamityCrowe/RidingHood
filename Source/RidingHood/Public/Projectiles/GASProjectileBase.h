// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "GASProjectileBase.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS(abstract)
class RIDINGHOOD_API AGASProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGASProjectileBase();

	UStaticMeshComponent* GetMesh() const { return Mesh; }
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	USphereComponent* GetCollider() const { return Collider; }

	void InitProjectile(const float Speed, const float Range, const FVector& Direction);


	UPROPERTY(BlueprintReadOnly, Category = "GAS", meta = (ExposeOnSpawn = true, AllowPrivateAccess = true))
	FGameplayEffectSpecHandle DamageEffect;


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<USphereComponent> Collider;


	float Speed;
	float Range;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
