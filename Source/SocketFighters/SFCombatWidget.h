// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common.h"
#include "SFCombatWidget.generated.h"


class UCombatManager;

USTRUCT(BlueprintType)
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	스킬 데이터 모아놓기


}


UCLASS(BlueprintType)
class SOCKETFIGHTERS_API USFCombatWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void InitData(UCombatManager* InMgr, FCharacterInstanceData& InCharData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitData();

	UPROPERTY(BlueprintReadWrite)
	bool IsInputEnabled() { return bInputEnabled; }

	void EnableInput();

	UFUNCTION(BlueprintCallable)
	void DisableInput();


	UFUNCTION(BlueprintCallable)
	void SkillSelected(int64 InUID);


public:

	UPROPERTY(BlueprintReadWrite)
	UCombatManager* CombatManager;

	UPROPERTY(BlueprintReadWrite)
	FCharacterInstanceData CharacterData;


	UPROPERTY(BlueprintReadWrite)
	bool bInputEnabled = false;

	UPROPERTY(BlueprintReadWrite)
	int64 SelectedSkillUID;

private:
	
};
