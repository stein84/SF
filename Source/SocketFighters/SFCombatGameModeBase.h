// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "SocketFightersGameModeBase.h"
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

	// ���� ���� ���� �����͵� �߰� 


	// ���� ��ų ���� , ������ ī����

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
