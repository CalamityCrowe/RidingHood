// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/GASProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Characters/GASPaperCharacter.h"
#include "Characters/Abilities/GASAbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AGASProjectileBase::AGASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	Collider->SetSphereRadius(15.0f);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AGASProjectileBase::OnOverlapBegin);
	Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AGASProjectileBase::InitProjectile(const float NewSpeed, const float NewRange, const FVector& Direction)
{
	Speed = NewSpeed;
	Range = NewRange;
	float LifeTIme = Range / Speed;
	
	ProjectileMovement->Velocity = Direction * Speed;
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); 
}

void AGASProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AGASProjectileBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetInstigator()) 
	{
		if (AGASPaperCharacter* Character = Cast<AGASPaperCharacter>(OtherActor)) 
		{
			if (UGASAbilitySystemComponent* ASC = Cast<UGASAbilitySystemComponent>(Character->GetAbilitySystemComponent()))
			{
				FGameplayEffectContextHandle EffectContext = DamageEffect.Data.Get()->GetContext();
				EffectContext.AddSourceObject(this);

				ASC->ApplyGameplayEffectSpecToSelf(*DamageEffect.Data.Get());

				Destroy(); 
			}
		}
	}
}

