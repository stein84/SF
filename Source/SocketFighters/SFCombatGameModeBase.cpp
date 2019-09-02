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
	// 플레이어 캐릭터 정보 초기화
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
	// 컴뱃 매니져 초기화, 전투 시작 로직 
	CombatManager->ActivateCombat(&MyCharacterCombatData, &EnemyCombatData);
}


void ASFCombatGameModeBase::OnPlayerDead()
{
	// 스테이지 실패 처리 

}


void ASFCombatGameModeBase::OnEnemyDead()
{
	// 전투 종료 로직


	if (CurrentEnemyCounter == MaxEnemyCounter)
	{
		// 스테이지 클리어 

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