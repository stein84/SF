// Fill out your copyright notice in the Description page of Project Settings.


#include "SFGameInstanceSubsystem.h"
#include "Common.h"
#include "Kismet/GameplayStatics.h"

const FString USFGameInstanceSubsystem::SaveSlotName(TEXT("SaveSlot"));

void USFGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// initiallize static data 
	UStaticDataAccessor::GetStaticData();

	LoadAccountInfo();
}


void USFGameInstanceSubsystem::Deinitialize()
{
	SaveAccountInfo();

	UStaticDataAccessor::Reset();
}


void USFGameInstanceSubsystem::SaveAccountInfo()
{
	ensure(AccountInfo != nullptr);
	UGameplayStatics::SaveGameToSlot(AccountInfo, SaveSlotName, 0);
}


void USFGameInstanceSubsystem::LoadAccountInfo()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		AccountInfo = Cast<USFAccountInfo>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	}
	else
	{
		AccountInfo = NewObject<USFAccountInfo>(this);
	}

	GDATA->AccountInfo = AccountInfo;
	GDATA->bAccountInfoValid = true;
}