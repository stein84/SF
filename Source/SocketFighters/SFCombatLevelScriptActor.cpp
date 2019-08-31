// Fill out your copyright notice in the Description page of Project Settings.


#include "SFCombatLevelScriptActor.h"


ASFCharacter* ASFCombatLevelScriptActor::SpawnCharacter(FCharacterInstanceData InData)
{
	return TestSpawnBIE(InData);
}