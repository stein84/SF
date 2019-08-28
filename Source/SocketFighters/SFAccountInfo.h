// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/SaveGame.h"
#include "SFAccountInfo.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FAccountInfo
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 SelectedCharacterUID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap <int64, FCharacterInstanceData> Characters;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap <int64, FSkillInstanceData> MainSkills;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap <int64, FSocketSkillInstanceData> SocketSkills;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap <int64, FBeltInstanceData> Belts;
};


UCLASS(Blueprintable, BlueprintType)
class SOCKETFIGHTERS_API USFAccountInfo : public USaveGame
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void AddCharacter(FName CharacterID);

	UFUNCTION(BlueprintCallable)
	void AddSkillToCharacter(FName SkillID, int64 CharacterUID);

	UFUNCTION(BlueprintPure)
	int64 GetFirstCharacterID();

	UFUNCTION(BlueprintPure)
	FCharacterInstanceData GetSelectedCharacterData();

	UFUNCTION(BlueprintPure)
	FCharacterInstanceData GetCharacterInstanceData(int64 InUID);

	UFUNCTION(BlueprintPure)
	FSkillInstanceData GetSkillInstanceData(int64 InUID);

	UFUNCTION(BlueprintPure)
	FSocketSkillInstanceData GetSocketSkillInstanceData(int64 InUID);

	UFUNCTION(BlueprintPure)
	FBeltInstanceData GetBeltInstanceData(int64 InUID);


private:
	int64 CreateUID() { return ++UIDCounter; }

public:

	UPROPERTY(BlueprintReadWrite)
	FAccountInfo MyAccountInfo;

	UPROPERTY()
	int64 UIDCounter;

};
