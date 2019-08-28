// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SkillSequence.generated.h"

/**
 * 
 */
UCLASS()
class SOCKETFIGHTERS_API UAN_SkillSequence : public UAnimNotify
{
	GENERATED_BODY()
	

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


};
