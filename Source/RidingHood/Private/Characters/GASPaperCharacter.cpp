// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GASPaperCharacter.h"

AGASPaperCharacter::AGASPaperCharacter()
{

}

UAbilitySystemComponent* AGASPaperCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

bool AGASPaperCharacter::IsAlive() const
{
	return false;
}

int32 AGASPaperCharacter::GetAbilityLevel(EGASAbilityInputID AbilityInputID) const
{
	return int32();
}

void AGASPaperCharacter::RemoveCharacterAbilities()
{
}

float AGASPaperCharacter::GetHealth() const
{
	return 0.0f;
}

float AGASPaperCharacter::GetMaxHealth() const
{
	return 0.0f;
}

void AGASPaperCharacter::Die()
{
}

void AGASPaperCharacter::FinishDying()
{
}

void AGASPaperCharacter::BeginPlay()
{
}

void AGASPaperCharacter::AddCharacterAbilities()
{
}

void AGASPaperCharacter::IntializeAttributes()
{
}

void AGASPaperCharacter::SetHealth(float NewHealth)
{
}

