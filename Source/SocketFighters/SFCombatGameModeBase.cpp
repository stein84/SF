// Fill out your copyright notice in the Description page of Project Settings.


#include "SFCombatGameModeBase.h"
#include "CombatManager.h"
#include "SFAccountInfo.h"
#include "Common.h"
#include "SFCombatLevelScriptActor.h"
#include "SFGameInstanceSubsystem.h"
#include "GameFramework/Actor.h"
#include "SFCharacter.h"


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
	InitEnemyData();
	SpawnNextEnemy();

	// test
	OnEncounterEnemy();
}


void ASFCombatGameModeBase::InitPlayerCharacter()
{
	// �÷��̾� ĳ���� ���� �ʱ�ȭ
	MyCharacterData = GDATA->AccountInfo->GetSelectedCharacterData();

	auto* CharStaticData = GDATA->GetCharacterData(MyCharacterData.ID);
	auto LVData = CharStaticData->LevelData[MyCharacterData.Level];

	MyCombatData.Character = MyLevelScript->SpawnCharacter(MyCharacterData.ID);
	MyCombatData.Character->SetupCombatData(LVData);
	MyCombatData.Character->OnCharacterDead.BindDynamic(this, &ASFCombatGameModeBase::OnPlayerDead);
}


void ASFCombatGameModeBase::OnEncounterEnemy()
{
	// �Ĺ� �Ŵ��� �ʱ�ȭ, ���� ���� ���� 
	CombatManager->ActivateCombat(&MyCombatData, &EnemyCombatData);

	EnterCombat();
}


void ASFCombatGameModeBase::OnPlayerDead()
{
	// �������� ���� ó�� 
	CombatManager->DeactivateCombat();
}


void ASFCombatGameModeBase::OnEnemyDead()
{
	// ���� ���� ����
	CombatManager->DeactivateCombat();

	EnemyCombatData.Character = nullptr;
	EnemyCombatData.SkillQueue.Reset();

	MyCombatData.Character->StopAction();

	if (CurrentEnemyCounter == MaxEnemyCounter)
	{
		// �������� Ŭ���� 

		return;
	}
	
	SpawnNextEnemy();

	// �ӽ�
	OnEncounterEnemy();
}


void ASFCombatGameModeBase::InitEnemyData()
{
	MaxEnemyCounter = MyStageData.NPCSet.Num();
	CurrentEnemyCounter = 0;	
}


void ASFCombatGameModeBase::SpawnNextEnemy()
{
	ensure(CurrentEnemyCounter < MaxEnemyCounter);
	FName EnemyID = MyStageData.NPCSet[CurrentEnemyCounter];
	FNPCDataRow* EnemyData = GDATA->GetNPCData(EnemyID);
	ensure(EnemyData != nullptr);

	EnemyCombatData.Character = MyLevelScript->SpawnEnemyCharacter(EnemyID);
	EnemyCombatData.Character->SetupCombatData(EnemyData);
	EnemyCombatData.Character->OnCharacterDead.BindDynamic(this, &ASFCombatGameModeBase::OnEnemyDead);

	++CurrentEnemyCounter;
}


void ASFCombatGameModeBase::SetPlayerSkillQueue(int32 Index, FName SkillID)
{
	MyCombatData.SkillQueue.FindOrAdd(Index);
	MyCombatData.SkillQueue[Index] = SkillID;
}


void ASFCombatGameModeBase::SetEnemySkillQueue(int32 Index, FName SkillID)
{
	EnemyCombatData.SkillQueue.FindOrAdd(Index);
	EnemyCombatData.SkillQueue[Index] = SkillID;
}