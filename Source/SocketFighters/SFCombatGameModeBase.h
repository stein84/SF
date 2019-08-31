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

UCLASS(Blueprintable)
class SOCKETFIGHTERS_API ASFCombatGameModeBase : public ASocketFightersGameModeBase
{
	GENERATED_BODY()

public:
	ASFCombatGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;


private:
	void InitCharacter();

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
};
