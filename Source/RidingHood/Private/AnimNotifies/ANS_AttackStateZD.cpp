// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_AttackStateZD.h"
#include "PaperZDAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/GASPaperCharacter.h"
#include "AbilitySystemComponent.h"
#include "PaperFlipbookComponent.h"


UANS_AttackStateZD::UANS_AttackStateZD()
{
#if WITH_EDITORONLY_DATA
	Color = FColor(255, 0, 0, 255); // Red color for attack state
#endif
}


void UANS_AttackStateZD::OnNotifyTick_Implementation(float DeltaTime, UPaperZDAnimInstance* OwningInstance) const
{
	if (OwningInstance == nullptr)
	{
		return;
	}
	AActor* OwnerActor = OwningInstance->GetOwningActor();
	if (OwnerActor == nullptr)
	{
		return;
	}
	AGASPaperCharacter* OwnerCharacter = Cast<AGASPaperCharacter>(OwnerActor);
	FVector Start = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetSprite()->GetForwardVector() * Offset;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(OwnerCharacter);
	TArray<FHitResult> Hits;

	UKismetSystemLibrary::SphereTraceMultiForObjects(this, Start, Start, CurrentRadius, ObjectTypes, false, IgnoreActors, EDrawDebugTrace::None, Hits, true);
	//DrawDebugSphere(GetWorld(), Start, CurrentRadius, 12, FColor::Red, false, -1.0f, 0, 1.0f);
	if (Hits.Num() > 0)
	{
		for (FHitResult Hit : Hits)
		{
			if (Hit.GetActor() && Hit.GetActor() != OwnerCharacter)
			{
				if (AGASPaperCharacter* HitCharacter = Cast<AGASPaperCharacter>(Hit.GetActor())) 
				{
					UAbilitySystemComponent* TargetASC = HitCharacter->GetAbilitySystemComponent();
					UAbilitySystemComponent* SourceASC = OwnerCharacter->GetAbilitySystemComponent();
					if (TargetASC && SourceASC &&  !TargetASC->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag("State.Stun")))
					{
						// generate a message to show what actor hit what 
						FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
						EffectContext.AddSourceObject(OwnerCharacter);
						EffectContext.AddHitResult(Hit);

						FGameplayEffectSpecHandle DamageSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffect, 1, EffectContext);
						if (DamageSpecHandle.IsValid()) 
						{
							DamageSpecHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), CurrentDamage);
							TargetASC->ApplyGameplayEffectSpecToSelf(*DamageSpecHandle.Data.Get());
						}
					}

				}
			}
		}
	}
	// we do the hit logic stuff in here
}

FName UANS_AttackStateZD::GetDisplayName_Implementation() const
{
	return Super::GetDisplayName_Implementation();
}
