// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SFAccountInfo.h"
#include "SFGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETFIGHTERS_API USFGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintCallable)
	void EnterStage(FName InStageID);

	UFUNCTION(BlueprintPure)
	FName GetCurrentStageID() { return StageID;  }


private:
	void InitializeStaticData();
	void LoadAccountInfo();
	void SaveAccountInfo();


public:
	
	UPROPERTY(BlueprintReadOnly)
	USFAccountInfo* AccountInfo;



private:

	static const FString SaveSlotName;

	FName StageID;
};
