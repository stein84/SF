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
전투중인 캐릭터의 상태관리 및 제어 모든것을 담당


 */


// 캐릭터 인스턴스 / NPC 정보를 통해 초기화한다
// 스킬 정보는 들고있을 필요 없고, 벨트에 실제 등록된 애들의 스태틱 데이터만을 가져온다


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

	// 현재 버프 관련 데이터도 추가 

	// 현재 스킬 관련 , 시퀀스 카운터

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
