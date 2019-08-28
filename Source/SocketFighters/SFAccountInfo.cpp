// Fill out your copyright notice in the Description page of Project Settings.


#include "SFAccountInfo.h"


void USFAccountInfo::AddCharacter(FName CharacterID)
{
	FCharacterStaticData* CharData = GDATA->GetCharacterData(CharacterID);
	if(CharData == nullptr)
		return;

	bool bHasAlready = false;
	for (auto& it : MyAccountInfo.Characters)
	{
		if (it.Value.ID == CharacterID)
		{
			bHasAlready = true;
			break;
		}
	}

	int64 NewCharUID = CreateUID();
	FCharacterInstanceData& NewCharData = MyAccountInfo.Characters.Emplace(NewCharUID, FCharacterInstanceData(NewCharUID, CharacterID));
	while (CharData != nullptr)
	{
		for (auto& SkillID : CharData->Data.SkillID)
		{
			uint64 SkillUID = CreateUID();
			MyAccountInfo.MainSkills.Add(SkillUID, FSkillInstanceData(SkillUID, SkillID, NewCharUID));
			NewCharData.SkillUIDs.Emplace(SkillUID);
		}

		for (auto& BeltID : CharData->Data.BeltID)
		{
			uint64 BeltUID = CreateUID();
			MyAccountInfo.Belts.Add(BeltUID, FBeltInstanceData(BeltUID, BeltID, NewCharUID));
			NewCharData.BeltUIDs.Emplace(BeltUID);
		}
		
		CharData = GDATA->GetCharacterData(CharData->ParentID);
	}
}


void USFAccountInfo::AddSkillToCharacter(FName SkillID, int64 CharacterUID)
{	
	auto CharInst = MyAccountInfo.Characters.Find(CharacterUID);
	if (CharInst == nullptr)
	{
		return;
	}

	uint64 SkillUID = CreateUID();
	MyAccountInfo.MainSkills.Add(SkillUID, FSkillInstanceData(SkillUID, SkillID, CharacterUID));
	CharInst->SkillUIDs.Emplace(SkillUID);
}


int64 USFAccountInfo::GetFirstCharacterID()
{
	TArray<int64> IDs;
	MyAccountInfo.Characters.GetKeys(IDs);
	return IDs[0];
}


FCharacterInstanceData USFAccountInfo::GetSelectedCharacterData()
{
	return GetCharacterInstanceData(MyAccountInfo.SelectedCharacterUID);
}


FCharacterInstanceData USFAccountInfo::GetCharacterInstanceData(int64 InUID)
{
	auto Data = MyAccountInfo.Characters.Find(InUID);
	return Data == nullptr ? FCharacterInstanceData() : *Data;
}


FSkillInstanceData USFAccountInfo::GetSkillInstanceData(int64 InUID)
{
	auto Data = MyAccountInfo.MainSkills.Find(InUID);
	return Data == nullptr ? FSkillInstanceData() : *Data;
}


FSocketSkillInstanceData USFAccountInfo::GetSocketSkillInstanceData(int64 InUID)
{
	auto Data = MyAccountInfo.SocketSkills.Find(InUID);
	return Data == nullptr ? FSocketSkillInstanceData() : *Data;
}


FBeltInstanceData USFAccountInfo::GetBeltInstanceData(int64 InUID)
{
	auto Data = MyAccountInfo.Belts.Find(InUID);
	return Data == nullptr ? FBeltInstanceData() : *Data;
}