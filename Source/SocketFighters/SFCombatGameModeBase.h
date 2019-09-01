// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "SocketFightersGameModeBase.h"
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


USTRUCT(BlueprintType)
struct FCombatCharacterData
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite)
	ASFCharacter* Character;

	UPROPERTY(BlueprintReadWrite)
	FName ID;

	UPROPERTY(BlueprintReadWrite)
	int32 MaxHP;

	UPROPERTY(BlueprintReadWrite)
	int32 HP;

	UPROPERTY(BlueprintReadWrite)
	int32 ATK;

	UPROPERTY(BlueprintReadWrite)
	int32 DEF;

	// 현재 버프 관련 데이터도 추가 


	// 현재 스킬 관련 , 시퀀스 카운터

};


class ASFCharacter;

UCLASS(Blueprintable)
class SOCKETFIGHTERS_API ASFCombatGameModeBase : public ASocketFightersGameModeBase
{
	GENERATED_BODY()

public:
	ASFCombatGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;


	void OnEncounterEnemy();
	void OnPlayerDead();

	UFUNCTION(BlueprintCallable)
	void OnEnemyDead();


private:
	void InitPlayerCharacter();

	void InitEnemyCharacter();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UCombatManager* CombatManager;

	UPROPERTY(BlueprintReadWrite)
	FStageDataRow MyStageData;

	UPROPERTY(BlueprintReadWrite)
	FCharacterInstanceData MyCharacterData;

	UPROPERTY(BlueprintReadWrite)
	class ASFCombatLevelScriptActor* MyLevelScript;

	UPROPERTY(BlueprintReadWrite)
	class USFGameInstanceSubsystem* MyGameInstance;

	UPROPERTY(BlueprintReadWrite)
	ASFCharacter* MyCharacter;

	UPROPERTY(BlueprintReadWrite)
	ASFCharacter* EnemyCharacter;

	UPROPERTY(BlueprintReadWrite)
	FCombatCharacterData MyCharacterCombatData;

	UPROPERTY(BlueprintReadWrite)
	FCombatCharacterData EnemyCombatData;


	UPROPERTY()
	int32 MaxEnemyCounter;

	UPROPERTY()
	int32 CurrentEnemyCounter;
};
