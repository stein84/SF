// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "Common.h"
#include "SFAccountInfo.h"
#include "Animation/AnimMontage.h"
#include "SFCharacter.h"
#include "SFCombatGameModeBase.h"
#include "UserWidget.h"
#include "SFCombatWidget.h"



UCombatManager::UCombatManager(const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
	: Super(ObjectInitializer)
{
	bAutoActivate = false;
	PrimaryComponentTick.bTickEvenWhenPaused = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = true;

}

void UCombatManager::ActivateCombat(FCombatCharacterData* InMyData, FCombatCharacterData* InEnemyData)
{
	MyData = InMyData;
	EnemyData = InEnemyData;

	MyData->Character->SetEnemy(EnemyData->Character);
	EnemyData->Character->SetEnemy(MyData->Character);

	PlayActivateSequence();
}


void UCombatManager::DeactivateCombat()
{
	MyData = nullptr;
	EnemyData = nullptr;

	Deactivate();
	CurrentTickTime = 0.f;
	CurrentTurnIndex = 0;
	
	PlayDeactivateSequence();
}
	


void UCombatManager::PlayActivateSequence()
{
	InitUI();

	// 나중에 delegate 처리
	OnActivateSequenceEnded();
}


void UCombatManager::PlayDeactivateSequence()
{
	// 나중에 delegate 처리 
	OnDeactivateSequenceEnded();
}


void UCombatManager::OnActivateSequenceEnded()
{
	Activate();
	ProcessNextTurn();
}


void UCombatManager::OnDeactivateSequenceEnded()
{
	MyGameMode->OnCombatDeactivated();
	RemoveUI();
}


void UCombatManager::InitUI()
{
	CombatUI = Cast<USFCombatWidget>(CreateWidget<UUserWidget, UWorld>(GetWorld(), CombatUIClass));
	CombatUI->InitData(this, MyGameMode->MyCharacterData);
	CombatUI->AddToViewport();
}


void UCombatManager::RemoveUI()
{
	CombatUI->RemoveFromViewport();
	CombatUI = nullptr;
}


ASFCharacter* UCombatManager::GetPlayerCharacter()
{
	return MyData == nullptr ? nullptr : MyData->Character;
}


ASFCharacter* UCombatManager::GetEnemyCharacter()
{
	return EnemyData == nullptr ? nullptr : EnemyData->Character;
}


TMap<int32, FName> UCombatManager::GetPlayerSkillQueue()
{
	return MyData == nullptr ? TMap<int32, FName>() : MyData->SkillQueue;
}


TMap<int32, FName> UCombatManager::GetEnemySkillQueue()
{
	return EnemyData == nullptr ? TMap<int32, FName>() : EnemyData->SkillQueue;
}


void UCombatManager::CheckTriggerSkill(FCombatCharacterData* InData, int32 TurnIndex)
{
	FName* SkillID = InData->SkillQueue.Find(TurnIndex);
	if (SkillID != nullptr)
	{
		InData->Character->PlaySkill(*SkillID);
	}
}


void UCombatManager::ProcessNextTurn()
{
	if (CurrentTurnIndex == MAX_TURN)
	{
		NextCycle();
	}

	CheckTriggerSkill(MyData, CurrentTurnIndex);
	CheckTriggerSkill(EnemyData, CurrentTurnIndex);

	++CurrentTurnIndex;
}


bool UCombatManager::IsSkillPlaying()
{
	return MyData->Character->IsPlayingSkill() || EnemyData->Character->IsPlayingSkill();
}


void UCombatManager::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickInputQueue(DeltaTime);

	CurrentTickTime += DeltaTime;
	if (CurrentTickTime >= TurnDelay)
	{
		if (!IsSkillPlaying())
		{
			CurrentTickTime = 0.f;
			ProcessNextTurn();
		}
	}
}


void UCombatManager::NextCycle()
{
	// 다음 사이클 
	CurrentTurnIndex = 0;

	MyData->SwapToNextQueue();
	EnemyData->SwapToNextQueue();
	EnableInput(true);
}


void UCombatManager::EnableInput(bool bEnable)
{
	if (bEnable)
	{
		RemainInputTime = InputDuration;
		CombatUI->EnableInput();
	}
	else
	{
		RemainInputTime = 0.f;
		CombatUI->DisableInput();
	}
}


void UCombatManager::TickInputQueue(float DeltaTime)
{
	if (!CombatUI->IsInputEnabled())
		return;

	RemainInputTime -= DeltaTime;
	if (RemainInputTime <= 0.f)
	{
		EnableInput(false);
	}
}