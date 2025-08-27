// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Abilities/GASDamageExecCalculation.h"
#include "Characters/Abilities/GASAbilitySystemComponent.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"

struct GASDamageStatics 
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armour)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage)

	GASDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armour, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Damage, Source, true);
	}
};

static const GASDamageStatics& DamageStatics()
{
	static GASDamageStatics DmgStatics;
	return DmgStatics;
}

UGASDamageExecCalculation::UGASDamageExecCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmourDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UGASDamageExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetOwnerActor() : nullptr;
	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetOwnerActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Armour = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmourDef, EvaluationParameters, Armour);
	Armour = FMath::Max<float>(Armour, 0);

	float Damage = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage);
	Damage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")),false,-1.0f),0.0f);

	float UnmitigatedDamage = Damage;

	float MitigatedDamage = Damage * (100 / (100 + Armour));

	if (MitigatedDamage > 0)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageDef.AttributeToCapture, EGameplayModOp::Additive, MitigatedDamage));
	}

	UGASAbilitySystemComponent* TargetASC = Cast<UGASAbilitySystemComponent>(TargetAbilitySystemComponent);
	if (TargetASC)
	{
		UGASAbilitySystemComponent* SourceASC = Cast<UGASAbilitySystemComponent>(SourceAbilitySystemComponent);
		TargetASC->RecieveDamage(SourceASC,UnmitigatedDamage,MitigatedDamage);
	}
}
