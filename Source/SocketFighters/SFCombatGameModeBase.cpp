// Fill out your copyright notice in the Description page of Project Settings.


#include "SFCombatGameModeBase.h"
#include "CombatManager.h"
#include "SFAccountInfo.h"
#include "Common.h"
#include "SFCombatLevelScriptActor.h"


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

	InitCharacter();
}


void ASFCombatGameModeBase::InitCharacter()
{
	// 플레이어 캐릭터 정보 초기화
	MyCharacterData = GDATA->AccountInfo->GetSelectedCharacterData();


}


void ASFCombatGameModeBase::SpawnCharacter()
{
	MyLevelScript->SpawnCharacter(MyCharacterData);
}