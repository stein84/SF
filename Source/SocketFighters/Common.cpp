// Fill out your copyright notice in the Description page of Project Settings.


#include "Common.h"

UStaticDataAccessor* UStaticDataAccessor::Instance = nullptr;

UStaticDataAccessor::UStaticDataAccessor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void UStaticDataAccessor::InitStaticData()
{
	CharStaticDataMap.Reset();
	UDataTable* CharTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/CharacterTable.CharacterTable"));
	if (CharTable != nullptr)
	{
		for (auto& it : CharTable->GetRowMap())
		{
			CharStaticDataMap.Add(it.Key, *reinterpret_cast<FCharacterDataRow*>(it.Value));
		}
	}

	UDataTable* LVTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/CharacterLevelTable.CharacterLevelTable"));

	TArray<FCharacterLevelDataRow*> LevelDataArray;
	LVTable->GetAllRows<FCharacterLevelDataRow>(nullptr, LevelDataArray);

	for (auto& it : LVTable->GetRowMap())
	{
		FCharacterLevelDataRow* LVData = reinterpret_cast<FCharacterLevelDataRow*>(it.Value);
		ensure(LVData != nullptr);
		auto* Data = CharStaticDataMap.Find(LVData->CharacterID);
		if (Data != nullptr)
		{
			Data->LevelData.Add(LVData->Level, *LVData);
		}
	}

	// link parent ID chain
	for (auto& it : CharStaticDataMap)
	{
		for (FName& ChildID : it.Value.Data.PromotionID)
		{
			auto* Data = CharStaticDataMap.Find(ChildID);
			ensure(Data != nullptr);
			Data->ParentID = it.Key;
		}
	}
	
	MainSkillTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/MainSkillTable.MainSkillTable"));
	SocketSkillTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/SocketSkillTable.SocketSkillTable"));
	BeltTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/BeltTable.BeltTable"));
	NPCTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/NPCTable.NPCTable"));
	StageTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/StageTable.StageTable"));
	SkillEffectTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/SkillEffectTable.SkillEffectTable"));
	IconTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Game/Data/IconTable.IconTable"));
}


FCharacterStaticData UStaticDataAccessor::GetCharacterData_BP(FName InID)
{
	FCharacterStaticData* Data = GetCharacterData(InID);
	ensure(Data != nullptr);
	return Data != nullptr ? *Data : FCharacterStaticData();
}


FMainSkillDataRow UStaticDataAccessor::GetMainSkillData_BP(FName InID)
{
	FMainSkillDataRow* Data = GetMainSkillData(InID);
	ensure(Data != nullptr);
	return Data != nullptr ? *Data : FMainSkillDataRow();
}


FSocketSkillDataRow UStaticDataAccessor::GetSocketSkillData_BP(FName InID)
{
	FSocketSkillDataRow* Data = GetSocketSkillData(InID);
	ensure(Data != nullptr);
	return Data != nullptr ? *Data : FSocketSkillDataRow();
}


FBeltDataRow UStaticDataAccessor::GetBeltData_BP(FName InID)
{
	FBeltDataRow* Data = GetBeltData(InID);
	ensure(Data != nullptr);
	return Data != nullptr ? *Data : FBeltDataRow();
}


FCharacterStaticData* UStaticDataAccessor::GetCharacterData(FName InID)
{
	return CharStaticDataMap.Find(InID);
}


FMainSkillDataRow* UStaticDataAccessor::GetMainSkillData(FName InID)
{
	return MainSkillTable->FindRow<FMainSkillDataRow>(InID, nullptr);
}


FSocketSkillDataRow* UStaticDataAccessor::GetSocketSkillData(FName InID)
{
	return SocketSkillTable->FindRow<FSocketSkillDataRow>(InID, nullptr);
}


FBeltDataRow* UStaticDataAccessor::GetBeltData(FName InID)
{
	return BeltTable->FindRow<FBeltDataRow>(InID, nullptr);
}


FNPCDataRow* UStaticDataAccessor::GetNPCData(FName InID)
{
	return NPCTable->FindRow<FNPCDataRow>(InID, nullptr);
}


FStageDataRow* UStaticDataAccessor::GetStageData(FName InID)
{
	return StageTable->FindRow<FStageDataRow>(InID, nullptr);
}


FSkillEffectDataRow* UStaticDataAccessor::GetSkillEffectData(FName InID)
{
	return SkillEffectTable->FindRow<FSkillEffectDataRow>(InID, nullptr);
}


UTexture2D* UStaticDataAccessor::GetIcon(FName InID)
{
	FIconData* Data = IconTable->FindRow<FIconData>(InID, nullptr);
	return Data == nullptr ? nullptr : Data->IconTex;
}


Common::Common()
{
}

Common::~Common()
{
}
