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

�ν��Ͻ��κ��� ĳ���� ������ / �������� ������ (���� ����) ���� ��

�÷��̾� ĳ���� ���� / �ʱ�ȭ 

ù ��° �� ����

���� ���� 

���������� �̵� -> �� ���� ���� 

���� �Ŵ��� ���� ���� ó�� 

�¸� - �̵� / �� �̻� �� ������ Ŭ���� ó��
�й� - ���� 

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
