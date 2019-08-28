// Fill out your copyright notice in the Description page of Project Settings.


#include "AN_SkillSequence.h"
#include "SFCombatGameModeBase.h"


void UAN_SkillSequence::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ASFCombatGameModeBase* CombatGameMode = Cast<ASFCombatGameModeBase>(GetWorld()->GetAuthGameMode());
	if(CombatGameMode == nullptr)
		return;

	//MeshComp->GetOwner()
}