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


	UPROPERTY(BlueprintReadWrite)
	int32 SkillSequenceCounter;

	// 스킬 큐
	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FName> SkillQueue;

	UPROPERTY(BlueprintReadWrite)
	FName LastSkillID;

};



UCLASS(BlueprintType)
class SOCKETFIGHTERS_API UCombatManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:

	void ActivateCombat(FCombatCharacterData* InMyData, FCombatCharacterData* InEnemyData);
	void DeactivateCombat();

	UFUNCTION(BlueprintCallable)
	void TriggerSkillSequence(ASFCharacter* InCharacter);
	
	


	// Begin FTickableGameObject implementation
	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Conditional; }
	virtual bool IsTickableWhenPaused() const override { return false; }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual bool IsTickable() const override { return bTickEnabled; }
	virtual TStatId GetStatId() const { return TStatId(); }
	virtual void Tick(float DeltaTime) override;
	// End FTickableGameObject implementation

private:

	FCombatCharacterData* GetCombatData(ASFCharacter* InCharacter);
	void ProcessNextTurn();
	void CheckTriggerSkill(FCombatCharacterData* InData, int32 TurnIndex);

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnDelay = 3.f;
	

private:

	FCombatCharacterData* MyData = nullptr;
	FCombatCharacterData* EnemyData = nullptr;

	UPROPERTY()
	bool bTickEnabled = false;

	float CurrentTickTime = 0.f;
	int32 CurrentTurnIndex = 0;
};
