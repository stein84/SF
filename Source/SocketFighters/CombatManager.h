// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "Common.h"
#include "CombatManager.generated.h"

class ASFCharacter;


/**
 * 
�������� ĳ������ ���°��� �� ���� ������ ���


 */


// ĳ���� �ν��Ͻ� / NPC ������ ���� �ʱ�ȭ�Ѵ�
// ��ų ������ ������� �ʿ� ����, ��Ʈ�� ���� ��ϵ� �ֵ��� ����ƽ �����͸��� �����´�


USTRUCT(BlueprintType)
struct FCharacterCombatData
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite)
	ASFCharacter* Character;

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



UCLASS(BlueprintType)
class SOCKETFIGHTERS_API UCombatManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void InitMyCharacter(int64 CharacterUID);

	UFUNCTION(BlueprintCallable)
	void InitEnemyCharacter(FName NPCID);

	UFUNCTION(BlueprintCallable)
	void ActivateSkill(ASFCharacter* InCharacter);


	UFUNCTION(BlueprintCallable)
	void TriggerSkillSequence(ASFCharacter* InCharacter);
	
	FCharacterCombatData& GetCombatData(ASFCharacter* InCharacter);


	// Begin FTickableGameObject implementation
	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }
	virtual bool IsTickableWhenPaused() const override { return false; }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const;
	// End FTickableGameObject implementation


public:

	UPROPERTY(BlueprintReadWrite)
	FCharacterCombatData MyCharacter;

	UPROPERTY(BlueprintReadOnly)
	FCharacterCombatData EnemyCharacter;
	
	
};
