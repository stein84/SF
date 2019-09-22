// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "SocketFightersGameModeBase.h"
#include "CombatManager.h"
#include "Platform.h"
#include "SFCombatGameModeBase.generated.h"


/**
 * 

인스턴스로부터 캐릭터 데이터 / 스테이지 데이터 (적들 정보) 얻어야 함

플레이어 캐릭터 스폰 / 초기화 

첫 번째 적 스폰

시작 연출 

스테이지로 이동 -> 적 조우 연출 

전투 매니져 전투 시작 처리 

승리 - 이동 / 더 이상 적 없으면 클리어 처리
패배 - 종료 

 */

class ASFCharacter;


UCLASS(Blueprintable)
class SOCKETFIGHTERS_API ASFCombatGameModeBase : public ASocketFightersGameModeBase
{
	GENERATED_BODY()

public:
	ASFCombatGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetPlayerSkillQueue(int32 Index, FName SkillID);

	UFUNCTION(BlueprintCallable)
	void SetEnemySkillQueue(int32 Index, FName SkillID);

	UFUNCTION(BlueprintImplementableEvent)
	void EnterCombat();



private:
	
	void OnEncounterEnemy();

	UFUNCTION()
	void OnPlayerDead();
	UFUNCTION()
	void OnEnemyDead();

	void InitPlayerCharacter();

	void InitEnemyData();
	void SpawnNextEnemy();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCombatManager* CombatManager;

	UPROPERTY(BlueprintReadWrite)
	class ASFCombatLevelScriptActor* MyLevelScript;

	UPROPERTY(BlueprintReadWrite)
	class USFGameInstanceSubsystem* MyGameInstance;

	UPROPERTY(BlueprintReadWrite)
	FStageDataRow MyStageData;

	UPROPERTY(BlueprintReadWrite)
	FCharacterInstanceData MyCharacterData;


// combat

	UPROPERTY(BlueprintReadWrite)
	FCombatCharacterData MyCombatData;

	UPROPERTY(BlueprintReadWrite)
	FCombatCharacterData EnemyCombatData;

	UPROPERTY()
	int32 MaxEnemyCounter;

	UPROPERTY()
	int32 CurrentEnemyCounter;
};
