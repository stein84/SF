// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatManager.h"
#include "Common.h"
#include "SFAccountInfo.h"


void UCombatManager::Tick(float DeltaTime)
{
	
}


TStatId UCombatManager::GetStatId() const
{
	return TStatId();

}


void UCombatManager::InitMyCharacter(int64 CharacterUID)
{
	auto CharData = GDATA->AccountInfo->GetCharacterInstanceData(CharacterUID);
	auto* CharStaticData = GDATA->GetCharacterData(CharData.ID);

	auto LVData = CharStaticData->LevelData[CharData.Level];

	MyCharacter.HP = MyCharacter.MaxHP = LVData.HP;
	MyCharacter.ATK = LVData.Attack;
	MyCharacter.DEF = LVData.Defense;


	

}


void UCombatManager::InitEnemyCharacter(FName NPCID)
{

}


void UCombatManager::ActivateSkill(ASFCharacter* InCharacter)
{
	//FCharacterCombatData& CombatData = GetCombatData(InCharacter);
}


void UCombatManager::TriggerSkillSequence(ASFCharacter* InCharacter)
{
	FCharacterCombatData& CombatData = GetCombatData(InCharacter);
	
	//GDATA->AccountInfo->GetSkillInstanceData(CombatData.CurrentSkillUID);

}


FCharacterCombatData& UCombatManager::GetCombatData(ASFCharacter* InCharacter)
{
	if (InCharacter == MyCharacter.Character)
		return MyCharacter;

	return EnemyCharacter;
}