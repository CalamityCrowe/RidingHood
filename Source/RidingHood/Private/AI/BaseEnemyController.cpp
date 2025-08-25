// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BaseEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemies/GASEnemyCharacter.h"
#include "Player/PaperPlayerState.h"

ABaseEnemyController::ABaseEnemyController(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	TargetKeyName = "TargetActor";
	POIKeyName = "POI";
	AIStateKeyName = "State";
}

void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AGASEnemyCharacter* EnemyCharacter = Cast<AGASEnemyCharacter>(InPawn))
	{
		if (EnemyCharacter->GetBehaviorTree())
		{
			RunBehaviorTree(EnemyCharacter->GetBehaviorTree());
			AGASPaperCharacter* PlayerCharacter = Cast<AGASPaperCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
			if (PlayerCharacter)
			{
				SetStateAsAttacking(PlayerCharacter);
			}
		}
	}
}

EAIStates ABaseEnemyController::GetAIState() const
{
	return static_cast<EAIStates>(Blackboard->GetValueAsEnum(AIStateKeyName));
}


void ABaseEnemyController::SetStateAsAttacking(UObject* AttackTarget)
{
	if (AttackTarget) 
	{
		Blackboard->SetValueAsObject(TargetKeyName, AttackTarget);
	}
	Blackboard->SetValueAsEnum(AIStateKeyName, (uint8)EAIStates::Attacking);
}

void ABaseEnemyController::SetStateAsDying()
{
	Blackboard->SetValueAsEnum(AIStateKeyName, static_cast<uint8>(EAIStates::Dying));
	Blackboard->ClearValue(TargetKeyName);
	Blackboard->ClearValue(POIKeyName);
	ClearFocus(EAIFocusPriority::Gameplay);
}

AActor* ABaseEnemyController::GetTargetActor() const
{
	if (Blackboard)
	{
		return Cast<AActor>(Blackboard->GetValueAsObject(TargetKeyName));
	}
	return nullptr;
}
