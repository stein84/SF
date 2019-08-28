// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
