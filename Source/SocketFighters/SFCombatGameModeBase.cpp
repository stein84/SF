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
	MyStageData = *(GDATA->GetStageData(MyGameInstance->GetCurrentStageID()));
	ensure(MyGameInstance != nullptr);

	InitCharacter();
}


void ASFCombatGameModeBase::InitCharacter()
{
	// �÷��̾� ĳ���� ���� �ʱ�ȭ
	MyCharacterData = GDATA->AccountInfo->GetSelectedCharacterData();


	MyCharacter = MyLevelScript->SpawnCharacter(MyCharacterData);
}
