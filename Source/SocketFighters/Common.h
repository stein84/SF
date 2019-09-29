// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "AssertionMacros.h"
#include "Classes/Engine/DataTable.h"
#include "Common.generated.h"

/**
 * 
 */


static const int32 MAX_TURN = 5;


UENUM(BlueprintType)
enum class ESkillEffect : uint8
{
	Attack_Type0,
	Attack_Type1,
	Attack_Type2,
};


USTRUCT(BlueprintType)
struct FSkillEffectData
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	ESkillEffect EffectID;

	UPROPERTY(EditDefaultsOnly)
	float Param1;

	UPROPERTY(EditDefaultsOnly)
	float Param2;

	UPROPERTY(EditDefaultsOnly)
	float Param3;
};


USTRUCT(BlueprintType)
struct FCharacterDataRow : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> SkillID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> BeltID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> PromotionID;
};


USTRUCT(BlueprintType)
struct FCharacterLevelDataRow : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName CharacterID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Defense;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 HP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 EXP;
};



USTRUCT(BlueprintType)
struct FCharacterStaticData
{
	GENERATED_BODY()
public:

	FCharacterStaticData() {}
	FCharacterStaticData(FCharacterDataRow& InData)
	: Data(InData) {}
	
	UPROPERTY(BlueprintReadOnly)
	FCharacterDataRow Data;

	UPROPERTY(BlueprintReadOnly)
	TMap<int32, FCharacterLevelDataRow> LevelData;

	UPROPERTY(BlueprintReadOnly)
	FName ParentID;
};




USTRUCT(BlueprintType)
struct FMainSkillSocketData
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Index;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Class;
};



USTRUCT(BlueprintType)
struct FSkillEffectDataRow : public FTableRowBase
{
public:
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Param1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Param2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Param3;
};


USTRUCT(BlueprintType)
struct FMainSkillDataRow : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText SkillName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Length;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Cost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMainSkillSocketData> Sockets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSkillEffectData> SkillSequence;
};



USTRUCT(BlueprintType)
struct FSocketSkillDataRow : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText SkillName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSkillEffectData> SkillSequence;
};


USTRUCT(BlueprintType)
struct FBeltDataRow : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText BeltName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Class;
};


USTRUCT(BlueprintType)
struct FNPCSkillData
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName SkillID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SkillLevel;
};


USTRUCT(BlueprintType)
struct FNPCSkillComboData
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int32, FNPCSkillData> SkillCombo;
};


USTRUCT(BlueprintType)
struct FNPCDataRow : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 HP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ATK;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 DEF;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FNPCSkillComboData> SkillSets;
};



USTRUCT(BlueprintType)
struct FStageDataRow : public FTableRowBase
{
public:
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FName> NPCSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName MapName;
};



USTRUCT(BlueprintType)
struct FCharacterInstanceData
{
public:
	GENERATED_BODY()

	FCharacterInstanceData() : UID(0), Level(1) {}
	FCharacterInstanceData(int64 InUID, FName InID)
	: UID(InUID), ID(InID), Level(1) {}
	FCharacterInstanceData(int64 InUID, FName InID, 
	TArray<int64>& InSkillUIDs, TArray<int64>& InBeltUIDs)
	: UID(InUID), ID(InID), Level(1), SkillUIDs(InSkillUIDs), BeltUIDs(InBeltUIDs){}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 UID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 Exp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<int64> SkillUIDs;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<int64> BeltUIDs;
};



USTRUCT(BlueprintType)
struct FSkillInstanceData
{
public:
	GENERATED_BODY()

	FSkillInstanceData() : UID(0), Level(1) {}
	FSkillInstanceData(int64 InUID, FName InID)
	: UID(InUID), ID(InID), Level(1) {}
	FSkillInstanceData(int64 InUID, FName InID, int64 InOwnerUID)
		: UID(InUID), ID(InID), Level(1), OwnerUID(InOwnerUID){}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 UID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<int32, int64> SocketSkills;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 OwnerUID;
};


USTRUCT(BlueprintType)
struct FSocketSkillInstanceData
{
public:
	GENERATED_BODY()

	FSocketSkillInstanceData() : UID(0) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 UID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 OwnerSkillUID;
};


USTRUCT(BlueprintType)
struct FBeltInstanceData
{
public:
	GENERATED_BODY()

	FBeltInstanceData() : UID(0) {}
	FBeltInstanceData(int64 InUID, FName InID, int64 InOwnerID)
	: UID(InUID), ID(InID), OwnerUID(InOwnerID) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 UID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int64 OwnerUID;
};




USTRUCT(BlueprintType)
struct FDamageData
{
	GENERATED_BODY()
public:

	FDamageData() 
	: ArmorPenetration(0.f), BuffType(NAME_None) {}

	// FName들은 나중에 enum화 

	UPROPERTY(BlueprintReadWrite)
	FName DamageType;

	UPROPERTY(BlueprintReadWrite)
	float DefaultDamage;

	UPROPERTY(BlueprintReadWrite)
	float ArmorPenetration;

	UPROPERTY(BlueprintReadWrite)
	FName BuffType;

	UPROPERTY(BlueprintReadWrite)
	float BuffWeight;

};


USTRUCT(BlueprintType)
struct FIconData : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* IconTex;
};


UCLASS(BlueprintType)
class SOCKETFIGHTERS_API UStaticDataAccessor : public UObject
{
	GENERATED_BODY()

public:
	UStaticDataAccessor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintPure)
	static UStaticDataAccessor* GetStaticData()
	{
		if (Instance == nullptr)
		{
			Instance = NewObject<UStaticDataAccessor>();
			Instance->InitStaticData();
			Instance->AddToRoot();
			Instance->bAccountInfoValid = false;
		}
		
		return Instance;
	}

	static void Reset()
	{
		if (Instance != nullptr)
		{
			Instance->RemoveFromRoot();
			Instance = nullptr;
		}
	}


	UFUNCTION(BlueprintPure)
	FCharacterStaticData GetCharacterData_BP(FName InID);

	UFUNCTION(BlueprintPure)
	FMainSkillDataRow GetMainSkillData_BP(FName InID);

	UFUNCTION(BlueprintPure)
	FSocketSkillDataRow GetSocketSkillData_BP(FName InID);

	UFUNCTION(BlueprintPure)
	FBeltDataRow GetBeltData_BP(FName InID);

	UFUNCTION(BlueprintPure)
	class UTexture2D* GetIcon(FName InID);

	FCharacterStaticData* GetCharacterData(FName InID);
	FMainSkillDataRow* GetMainSkillData(FName InID);
	FSocketSkillDataRow* GetSocketSkillData(FName InID);
	FBeltDataRow* GetBeltData(FName InID);
	FNPCDataRow* GetNPCData(FName InID);
	FStageDataRow* GetStageData(FName InID);
	
	FSkillEffectDataRow* GetSkillEffectData(FName InID);
	
private:
	void InitStaticData();


public:
	UPROPERTY(BlueprintReadOnly)
	UDataTable* MainSkillTable;
	UPROPERTY(BlueprintReadOnly)
	UDataTable* SocketSkillTable;
	UPROPERTY(BlueprintReadOnly)
	UDataTable* BeltTable;
	UPROPERTY(BlueprintReadOnly)
	TMap<FName, FCharacterStaticData> CharStaticDataMap;
	
	UPROPERTY(BlueprintReadOnly)
	UDataTable* NPCTable;
	UPROPERTY(BlueprintReadOnly)
	UDataTable* StageTable;
	UPROPERTY(BlueprintReadOnly)
	UDataTable* SkillEffectTable;
	UPROPERTY(BlueprintReadOnly)
	UDataTable* IconTable;

	UPROPERTY(BlueprintReadOnly)
	class USFAccountInfo* AccountInfo;
	UPROPERTY(BlueprintReadOnly)
	bool bAccountInfoValid;


private:
	static UStaticDataAccessor* Instance;

	
};


#define GDATA		UStaticDataAccessor::GetStaticData()
#define GACCOUNT	GDATA->AccountInfo


class SOCKETFIGHTERS_API Common
{
public:
	Common();
	~Common();
};



USTRUCT(BlueprintType)
struct FCombatCharacterData
{
	GENERATED_BODY()

public:

	void RegisterSkill(int32 Turn, FName SkillID);
	void SwapToNextQueue();

public:

	UPROPERTY(BlueprintReadWrite)
	class ASFCharacter* Character;

	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FName> SkillQueue;

	UPROPERTY(BlueprintReadWrite)
	TMap<int32, FName> NextQueue;
};
