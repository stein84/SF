// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Common.h"
#include "SFCombatLevelScriptActor.generated.h"

class ASFCharacter;

UCLASS()
class SOCKETFIGHTERS_API ASFCombatLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	ASFCharacter* SpawnCharacter(FName CharacterID);

	UFUNCTION(BlueprintImplementableEvent)
	ASFCharacter* TestSpawnBIE(FName CharacterID);

	UFUNCTION(BlueprintCallable)
	ASFCharacter* SpawnEnemyCharacter(FName CharacterID);

	UFUNCTION(BlueprintImplementableEvent)
	ASFCharacter* SpawnEnemyCharacterBIE(FName CharacterID);


public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class APlayerStart* TestPlayerStart;
};
