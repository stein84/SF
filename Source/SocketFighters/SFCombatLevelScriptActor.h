// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Common.h"
#include "SFCombatLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETFIGHTERS_API ASFCombatLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void SpawnCharacter(FCharacterInstanceData InData);



public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerStart* TestPlayerStart;
};
