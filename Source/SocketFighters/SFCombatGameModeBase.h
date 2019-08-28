// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

UCLASS(Blueprintable)
class SOCKETFIGHTERS_API ASFCombatGameModeBase : public ASocketFightersGameModeBase
{
	GENERATED_BODY()

public:
	ASFCombatGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;


private:
	void InitCharacter();

	void SpawnCharacter();

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UCombatManager* CombatManager;

	UPROPERTY(BlueprintReadWrite)
	FCharacterInstanceData MyCharacterData;

	UPROPERTY(BlueprintReadWrite)
	class ASFCombatLevelScriptActor* MyLevelScript;

};
