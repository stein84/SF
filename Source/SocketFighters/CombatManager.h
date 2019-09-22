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
	TMap<int32, FName> SkillQueue;
};


UCLASS(BlueprintType)
class SOCKETFIGHTERS_API UCombatManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:

	void ActivateCombat(FCombatCharacterData* InMyData, FCombatCharacterData* InEnemyData);
	void DeactivateCombat();

	UFUNCTION(BlueprintPure)
	ASFCharacter* GetPlayerCharacter();

	UFUNCTION(BlueprintPure)
	ASFCharacter* GetEnemyCharacter();
	
	UFUNCTION(BlueprintPure)
	TMap<int32, FName> GetPlayerSkillQueue();

	UFUNCTION(BlueprintPure)
	TMap<int32, FName> GetEnemySkillQueue();


	// Begin FTickableGameObject implementation
	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Conditional; }
	virtual bool IsTickableWhenPaused() const override { return false; }
	virtual bool IsTickableInEditor() const override { return true; }
	virtual bool IsTickable() const override { return bTickEnabled; }
	virtual TStatId GetStatId() const { return TStatId(); }
	virtual void Tick(float DeltaTime) override;
	// End FTickableGameObject implementation


private:

	void ProcessNextTurn();
	void CheckTriggerSkill(FCombatCharacterData* InData, int32 TurnIndex);
	bool IsSkillPlaying();


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnDelay = 1.f;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentTurnIndex = 0;

private:

	FCombatCharacterData* MyData = nullptr;
	FCombatCharacterData* EnemyData = nullptr;

	UPROPERTY()
	bool bTickEnabled = false;

	float CurrentTickTime = 0.f;
	
};
