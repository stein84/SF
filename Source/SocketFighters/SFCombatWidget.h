// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Common.h"
#include "SFCombatWidget.generated.h"


class UCombatManager;

UCLASS(BlueprintType)
class SOCKETFIGHTERS_API USFCombatWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	void InitData(UCombatManager* InMgr, FCharacterInstanceData& InCharData);

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitData();


public:

	UPROPERTY(BlueprintReadWrite)
	UCombatManager* CombatManager;

	UPROPERTY(BlueprintReadWrite)
	FCharacterInstanceData CharacterData;
};
