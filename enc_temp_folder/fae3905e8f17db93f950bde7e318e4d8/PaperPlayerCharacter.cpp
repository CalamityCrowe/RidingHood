// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PaperPlayerCharacter.h"
#include "AbilityIDDefine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/Abilities/GASAbilitySystemComponent.h"
#include "Characters/Abilities/Attributes/AttributeSetBase.h"

#include "Player/PaperPlayerController.h"
#include "Player/PaperPlayerState.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APaperPlayerCharacter::APaperPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f,0.f));
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 5.0f;

	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false; 

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->FieldOfView = 80.0f;

	
}

void APaperPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (PlayerInputData->InputMappingContext == nullptr)
			{
				return;
			}
			InputSystem->AddMappingContext(PlayerInputData->InputMappingContext, 0);
		}
	}
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(PlayerInputData->MoveAction, ETriggerEvent::Triggered, this, &APaperPlayerCharacter::Move);
		EIC->BindAction(PlayerInputData->JumpAction, ETriggerEvent::Started, this, &APaperPlayerCharacter::Jump);
		EIC->BindAction(PlayerInputData->AttackAction, ETriggerEvent::Started, this, &APaperPlayerCharacter::Attack);
	}
}

void APaperPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	APaperPlayerState* PS = GetPlayerState<APaperPlayerState>(); 
	if (PS) 
	{
		ASC = Cast<UGASAbilitySystemComponent>(PS->GetAbilitySystemComponent()); 
		AttributeSetBase = PS->GetAttributeSetBase();
		IntializeAttributes();

		ASC->SetTagMapCount(DeadTag, 0); 
		SetHealth(GetMaxHealth()); 
		SetMana(GetMaxMana());

		AddCharacterAbilities();

		if (APaperPlayerController* PC = Cast<APaperPlayerController>(GetController()))
		{
			PC->CreateHUD();
		}
	}
}

void APaperPlayerCharacter::BeginPlay()
{
	Super::BeginPlay(); 
}

void APaperPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APaperPlayerCharacter::SendAbilityLocalInput(const FInputActionValue& Value, int32 InputID)
{
	if (!ASC.Get())
	{
		return;
	}
	if (Value.Get<bool>())
	{
		ASC->AbilityLocalInputPressed(InputID);
	}
	else
	{
		ASC->AbilityLocalInputReleased(InputID);
	}
}

void APaperPlayerCharacter::Move(const FInputActionValue& Value)
{
	MoveAxis = Value.Get<FVector2D>();
	SendAbilityLocalInput(Value, static_cast<int32>(EGASAbilityInputID::Move));
}

void APaperPlayerCharacter::Magic(const FInputActionValue& Value)
{
	SendAbilityLocalInput(Value, static_cast<int32>(EGASAbilityInputID::Ability2));
}

void APaperPlayerCharacter::Attack(const FInputActionValue& Value)
{
	SendAbilityLocalInput(Value, static_cast<int32>(EGASAbilityInputID::Ability1));
}
