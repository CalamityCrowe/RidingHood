// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GASPaperCharacter.h"
#include "Characters/Abilities/GASAbilitySystemComponent.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"
#include "Characters/Abilities/GASGameplayAbility.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperZDAnimationComponent.h"


AGASPaperCharacter::AGASPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);

	bAlwaysRelevant = true;

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));

	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;
	GetSprite()->CastShadow = true;
}

UAbilitySystemComponent* AGASPaperCharacter::GetAbilitySystemComponent() const
{
	return ASC.Get();
}

bool AGASPaperCharacter::IsAlive() const
{
	return GetHealth() > 0;
}

int32 AGASPaperCharacter::GetAbilityLevel(EGASAbilityInputID AbilityInputID) const
{
	return 1;
}

void AGASPaperCharacter::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !ASC.IsValid())
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterConfig->DefaultAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}
	for (int32 i = 0; i < AbilitiesToRemove.Num(); ++i)
	{
		ASC->ClearAbility(AbilitiesToRemove[i]);
	}
}

float AGASPaperCharacter::GetHealth() const
{
	if (AttributeSetBase.Get())
	{
		return AttributeSetBase->GetHealth();
	}
	return 0.0f;
}

float AGASPaperCharacter::GetMaxHealth() const
{
	if (AttributeSetBase.Get())
	{
		return AttributeSetBase->GetMaxHealth();
	}
	return 0.0f;
}

float AGASPaperCharacter::GetMana() const
{
	if (AttributeSetBase.Get())
	{
		return AttributeSetBase->GetMana();
	}
	return 0.0f;
}

float AGASPaperCharacter::GetMaxMana() const
{
	if (AttributeSetBase.Get())
	{
		return AttributeSetBase->GetMaxMana();
	}
	return 0.0f;
}

void AGASPaperCharacter::Die()
{
	RemoveCharacterAbilities();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector::ZeroVector;

	if (ASC.IsValid())
	{
		ASC->CancelAbilities();
	}
}

void AGASPaperCharacter::FinishDying()
{
	Destroy();
}

void AGASPaperCharacter::StartHitStop(float Time)
{
	CustomTimeDilation = 0.3;
	// we say what one has been hit in the debug

	GetWorld()->GetTimerManager().SetTimer(HitStopTimerHandle, this, &AGASPaperCharacter::StopHitStop, Time, false);

}
void AGASPaperCharacter::StopHitStop()
{
	CustomTimeDilation = 1.0f;
	GetWorld()->GetTimerManager().ClearTimer(HitStopTimerHandle);
}

void AGASPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AGASPaperCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	if (bIsHurt == false)
	{


		if (GetVelocity().X > 0)
		{
			GetSprite()->SetRelativeRotation(CharacterConfig->FaceRightRotation);
			GetSprite()->SetRelativeLocation(CharacterConfig->FaceRightOffset);
		}
		if (GetVelocity().X < 0)
		{
			GetSprite()->SetRelativeRotation(CharacterConfig->FaceLeftRotation);
			GetSprite()->SetRelativeLocation(CharacterConfig->FaceLeftOffset);
		}
	}
}

void AGASPaperCharacter::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !ASC.IsValid())
	{
		return;
	}

	// loops through all the abilities in the character config and gives them to the ASC if they are valid
	for (TSubclassOf<UGASGameplayAbility> Ability : CharacterConfig->DefaultAbilities)
	{
		if (Ability)
		{
			FGameplayAbilitySpec AbilitySpec(Ability, GetAbilityLevel(Ability.GetDefaultObject()->AbilityID), static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this);
			ASC->GiveAbility(AbilitySpec);
		}
	}

	ASC->bCharacterAbilitiesGiven = true; // tells the ASC that it has recieved the abilities
}

void AGASPaperCharacter::IntializeAttributes()
{
	if (!ASC.IsValid())
	{
		return;
	}

	if (CharacterConfig->DefaultAttributes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultAttributes is not set for %s"), *GetName());
		return;
	}

	// we make an effect contect and tell it what actor to affect, in this case itself
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	// we loop through all the default attributes in the character config and apply them to the ASC based on the effect context handle
	for (TSubclassOf<UGameplayEffect>& DefaultAttribute : CharacterConfig->DefaultAttributes)
	{
		if (DefaultAttribute)
		{
			FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(DefaultAttribute, 1, EffectContext);
			if (EffectSpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}

void AGASPaperCharacter::SetHealth(float NewHealth)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetHealth(NewHealth);
	}
}

void AGASPaperCharacter::SetMana(float NewMana)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->SetMana(NewMana);
	}
}

