// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "CombatManager.generated.h"

class ASFCharacter;


/**
 * 
전투중인 캐릭터의 상태관리 및 제어 모든것을 담당


 */


USTRUCT(BlueprintType)
struct FCharacterCombatData
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite)
	ASFCharacter* Character;

	UPROPERTY(BlueprintReadWrite)
	FCharacterInstanceData InstanceData;

	UPROPERTY(BlueprintReadWrite)
	float CurrentHP;

	// 현재 버프 관련 데이터도 추가 
};



UCLASS(BlueprintType)
class SOCKETFIGHTERS_API UCombatManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void InitCombat(FCharacterInstanceData MyInfo);

	UFUNCTION(BlueprintCallable)
	void ActivateSkill(AActor* InCharacter);

	UFUNCTION(BlueprintCallable)
	void TriggerSkillSequence(AActor* InCharacter);


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
