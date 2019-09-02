// Fill out your copyright notice in the Description page of Project Settings.


#include "SFCombatGameModeBase.h"
#include "CombatManager.h"
#include "SFAccountInfo.h"
#include "Common.h"
#include "SFCombatLevelScriptActor.h"
#include "SFGameInstanceSubsystem.h"
#include "GameFramework/Actor.h"


ASFCombatGameModeBase::ASFCombatGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CombatManager = CreateDefaultSubobject<UCombatManager>(TEXT("CmbMgr"));

}


void ASFCombatGameModeBase::StartPlay()
{
	Super::StartPlay();

	MyLevelScript = Cast<ASFCombatLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	ensure(MyLevelScript != nullptr);

	MyGameInstance = GetGameInstance()->GetSubsystem<USFGameInstanceSubsystem>();
	MyStageData = *(GDATA->GetStageData(GDATA->AccountInfo->SelectedStageID));
	ensure(MyGameInstance != nullptr);

	InitPlayerCharacter();

	MaxEnemyCounter = MyStageData.NPCSet.Num();
	CurrentEnemyCounter = 0;
	InitEnemyCharacter();

	// test
	OnEncounterEnemy();
}


void ASFCombatGameModeBase::InitPlayerCharacter()
{
	// �÷��̾� ĳ���� ���� �ʱ�ȭ
	MyCharacterData = GDATA->AccountInfo->GetSelectedCharacterData();

	auto* CharStaticData = GDATA->GetCharacterData(MyCharacterData.ID);
	auto LVData = CharStaticData->LevelData[MyCharacterData.Level];

	MyCharacterCombatData.ID = MyCharacterData.ID;
	MyCharacterCombatData.HP = MyCharacterCombatData.MaxHP = LVData.HP;
	MyCharacterCombatData.ATK = LVData.Attack;
	MyCharacterCombatData.DEF = LVData.Defense;

	MyCharacter = MyLevelScript->SpawnCharacter(MyCharacterData.ID);
	MyCharacterCombatData.Character = MyCharacter;
}


void ASFCombatGameModeBase::OnEncounterEnemy()
{
	// �Ĺ� �Ŵ��� �ʱ�ȭ, ���� ���� ���� 
	CombatManager->ActivateCombat(&MyCharacterCombatData, &EnemyCombatData);
}


void ASFCombatGameModeBase::OnPlayerDead()
{
	// �������� ���� ó�� 

}


void ASFCombatGameModeBase::OnEnemyDead()
{
	// ���� ���� ����


	if (CurrentEnemyCounter == MaxEnemyCounter)
	{
		// �������� Ŭ���� 

		return;
	}

	InitEnemyCharacter();
}


void ASFCombatGameModeBase::InitEnemyCharacter()
{
	ensure(CurrentEnemyCounter < MaxEnemyCounter);
	FName EnemyID = MyStageData.NPCSet[CurrentEnemyCounter];

	FNPCDataRow* EnemyData = GDATA->GetNPCData(EnemyID);
	ensure(EnemyData != nullptr);

	EnemyCombatData.ID = EnemyID;
	EnemyCombatData.HP = EnemyCombatData.MaxHP = EnemyData->HP;
	EnemyCombatData.ATK = EnemyData->ATK;
	EnemyCombatData.DEF = EnemyData->DEF;

	EnemyCharacter = MyLevelScript->SpawnEnemyCharacter(EnemyID);
	EnemyCombatData.Character = EnemyCharacter; 

	++CurrentEnemyCounter;
}


void ASFCombatGameModeBase::SetPlayerSkillQueue(int32 Index, FName SkillID)
{
	MyCharacterCombatData.SkillQueue.FindOrAdd(Index);
	MyCharacterCombatData.SkillQueue[Index] = SkillID;
}


void ASFCombatGameModeBase::SetEnemySkillQueue(int32 Index, FName SkillID)
{
	EnemyCombatData.SkillQueue.FindOrAdd(Index);
	EnemyCombatData.SkillQueue[Index] = SkillID;
}