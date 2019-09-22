// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "Common.h"
#include "SFAccountInfo.h"
#include "Animation/AnimMontage.h"
#include "SFCharacter.h"
#include "SFCombatGameModeBase.h"




void UCombatManager::ActivateCombat(FCombatCharacterData* InMyData, FCombatCharacterData* InEnemyData)
{
	MyData = InMyData;
	EnemyData = InEnemyData;

	MyData->Character->SetEnemy(EnemyData->Character);
	EnemyData->Character->SetEnemy(MyData->Character);

	bTickEnabled = true;
	ProcessNextTurn();
}


void UCombatManager::DeactivateCombat()
{
	MyData = nullptr;
	EnemyData = nullptr;

	bTickEnabled = false;
	CurrentTickTime = 0.f;
	CurrentTurnIndex = 0;
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


void UCombatManager::Tick(float DeltaTime)
{
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
	CheckTriggerSkill(MyData, CurrentTurnIndex);
	CheckTriggerSkill(EnemyData, CurrentTurnIndex);

	++CurrentTurnIndex;
	if (CurrentTurnIndex == MAX_TURN)
	{
		// 다음 사이클 
		CurrentTurnIndex = 0;
	}
}


bool UCombatManager::IsSkillPlaying()
{
	return MyData->Character->IsPlayingSkill() || EnemyData->Character->IsPlayingSkill();
}