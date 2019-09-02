// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "Common.h"
#include "SFAccountInfo.h"
#include "Animation/AnimMontage.h"
#include "SFCharacter.h"




void UCombatManager::ActivateCombat(FCombatCharacterData* InMyData, FCombatCharacterData* InEnemyData)
{
	MyData = InMyData;
	EnemyData = InEnemyData;

	bTickEnabled = true;
	ProcessNextTurn();
}


void UCombatManager::DeactivateCombat()
{
	MyData = nullptr;
	EnemyData = nullptr;

	bTickEnabled = false;
}



void UCombatManager::Tick(float DeltaTime)
{
	CurrentTickTime += DeltaTime;
	if (CurrentTickTime >= TurnDelay)
	{
		CurrentTickTime -= TurnDelay;
		ProcessNextTurn();
	}
}


void UCombatManager::CheckTriggerSkill(FCombatCharacterData* InData, int32 TurnIndex)
{
	FName* SkillID = InData->SkillQueue.Find(TurnIndex);
	if (SkillID != nullptr)
	{
		InData->SkillSequenceCounter = 0;
		InData->LastSkillID = *SkillID;
		UAnimMontage** Anim = InData->Character->SkillAnims.Find(*SkillID);
		if (Anim != nullptr)
		{
			InData->Character->PlayAnimMontage(*Anim);
		}
	}
}


void UCombatManager::ProcessNextTurn()
{
	CheckTriggerSkill(MyData, CurrentTurnIndex);
	CheckTriggerSkill(EnemyData, CurrentTurnIndex);

	++CurrentTurnIndex;
}


void UCombatManager::TriggerSkillSequence(ASFCharacter* InCharacter)
{
	FCombatCharacterData* CombatData = GetCombatData(InCharacter);
	ensure(CombatData != nullptr);

	auto SkillDataPtr = GDATA->GetMainSkillData(CombatData->LastSkillID);
	FName SequenceID = SkillDataPtr->SkillSequenceIDs[CombatData->SkillSequenceCounter];

	auto EffectData = GDATA->GetSkillEffectData(SequenceID);
	   
	// trigger sequence
	if (EffectData != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.0f, FColor::White,
			FString::Printf(TEXT("%s : %f, %f, %f"), *SequenceID.ToString(), EffectData->Param1, EffectData->Param2, EffectData->Param3), false);
	}

	
	++(CombatData->SkillSequenceCounter);
}


FCombatCharacterData* UCombatManager::GetCombatData(ASFCharacter* InCharacter)
{
	if (InCharacter == MyData->Character)
		return MyData;

	return EnemyData;
}