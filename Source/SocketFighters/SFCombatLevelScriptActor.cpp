// Fill out your copyright notice in the Description page of Project Settings.


#include "SFCombatLevelScriptActor.h"


ASFCharacter* ASFCombatLevelScriptActor::SpawnCharacter(FName CharacterID)
{
	return TestSpawnBIE(CharacterID);
}

ASFCharacter* ASFCombatLevelScriptActor::SpawnEnemyCharacter(FName CharacterID)
{
	return SpawnEnemyCharacterBIE(CharacterID);
}