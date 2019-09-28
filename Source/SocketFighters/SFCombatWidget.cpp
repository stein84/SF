// Fill out your copyright notice in the Description page of Project Settings.


#include "SFCombatWidget.h"
#include "CombatManager.h"


void USFCombatWidget::InitData(UCombatManager* InMgr, FCharacterInstanceData& InCharData)
{
	CombatManager = InMgr;
	CharacterData = InCharData;

	OnInitData();
}