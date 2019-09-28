// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "Common.h"
#include "Components/ActorComponent.h"
#include "CombatManager.generated.h"

class ASFCharacter;
class USFCombatWidget;

/**
 * 
전투중인 캐릭터의 상태관리 및 제어 모든것을 담당


 */



UCLASS(BlueprintType)
class SOCKETFIGHTERS_API UCombatManager : public UActorComponent
{
	GENERATED_BODY()
public:
	UCombatManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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

	UFUNCTION(BlueprintCallable)
	void OnActivateSequenceEnded();
	
	UFUNCTION(BlueprintCallable)
	void OnDeactivateSequenceEnded();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:

	void PlayActivateSequence();
	void PlayDeactivateSequence();

	void InitUI();
	void RemoveUI();


	void ProcessNextTurn();
	void CheckTriggerSkill(FCombatCharacterData* InData, int32 TurnIndex);
	bool IsSkillPlaying();


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurnDelay = 1.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CombatUIClass;
	
	UPROPERTY(BlueprintReadOnly)
	int32 CurrentTurnIndex = 0;

	UPROPERTY(BlueprintReadOnly)
	USFCombatWidget* CombatUI;

	UPROPERTY(BlueprintReadOnly)
	class ASFCombatGameModeBase* MyGameMode;

private:

	FCombatCharacterData* MyData = nullptr;
	FCombatCharacterData* EnemyData = nullptr;

	UPROPERTY()
	bool bTickEnabled = false;

	float CurrentTickTime = 0.f;
	
};
