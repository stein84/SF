// Fill out your copyright notice in the Description page of Project Settings.


#include "SFCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

// Sets default values
ASFCharacter::ASFCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASFCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	OnSkillMontageEnded.BindUObject(this, &ASFCharacter::SkillMontageEndedDelegate);
}

// Called every frame
void ASFCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASFCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}


void ASFCharacter::SetEnemy(ASFCharacter* InEnemy)
{
	Enemy = InEnemy;
}


void ASFCharacter::PlaySkill(FName SkillID)
{
	CurrentSkillID = SkillID;
	SkillSequenceCounter = 0;
	UAnimMontage** Anim = SkillAnims.Find(SkillID);
	ensure(Anim != nullptr);

	if (Anim != nullptr)
	{
		PlayAnimMontage(*Anim);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(OnSkillMontageEnded, *Anim);
	}
}


bool ASFCharacter::IsPlayingSkill() const
{
	return CurrentSkillID != NAME_None;
}


bool ASFCharacter::IsDead() const
{
	return Stat.HP <= 0.f;
}


void ASFCharacter::TriggerSkillSequence()
{
	auto SkillDataPtr = GDATA->GetMainSkillData(CurrentSkillID);
	ensure(SkillSequenceCounter < SkillDataPtr->SkillSequence.Num());

	ProcessSkillEffect(SkillDataPtr->SkillSequence[SkillSequenceCounter]);
	++SkillSequenceCounter;
}


void ASFCharacter::ProcessSkillEffect(FSkillEffectData& EffectData)
{
	ESkillEffect ID = EffectData.EffectID;

	FDamageData DamageData;
	switch (ID)
	{
	case ESkillEffect::Attack_Type0:
		DamageData.DamageType = TEXT("Default");
		DamageData.DefaultDamage = Stat.ATK * EffectData.Param1;
		break;
	case ESkillEffect::Attack_Type1:
		DamageData.DamageType = TEXT("ArmorIgnore");
		DamageData.DefaultDamage = Stat.ATK * EffectData.Param1;
		DamageData.ArmorPenetration = EffectData.Param2;
		break;
	case ESkillEffect::Attack_Type2:
		DamageData.DamageType = TEXT("Debuff");
		DamageData.DefaultDamage = Stat.ATK * EffectData.Param1;
		DamageData.BuffType = TEXT("Fire");
		DamageData.BuffWeight = EffectData.Param2;
		break;
	}

	Enemy->ApplyDamage(DamageData);
}


void ASFCharacter::SetupCombatData(const FCharacterLevelDataRow& CharLVData)
{
	Stat.HP = Stat.MaxHP = CharLVData.HP;
	Stat.ATK = CharLVData.Attack;
	Stat.DEF = CharLVData.Defense;
}


void ASFCharacter::SetupCombatData(const FNPCDataRow* NPCData)
{
	ensure(NPCData != nullptr);
	Stat.HP = Stat.MaxHP = NPCData->HP;
	Stat.ATK = NPCData->ATK;
	Stat.DEF = NPCData->DEF;
}


void ASFCharacter::ApplyDamage(FDamageData InDamageData)
{
	if (!CanApplyDamage(InDamageData))
		return;

	if (IsBuffDamage(InDamageData))
	{
		PlayBuff(InDamageData);
	}

	float ActualDamage = CalcActualDamage(InDamageData);
	if (ActualDamage == 0.f)
		return;

	Stat.HP -= ActualDamage;
	if (Stat.HP <= 0.f)
	{
		OnCharacterDead.ExecuteIfBound();

		PlayDeath(InDamageData);
	}
	else
	{
		PlayHit(InDamageData);
	}
}


bool ASFCharacter::CanApplyDamage(const FDamageData& InDamageData)
{
	return !IsDead();
}


bool ASFCharacter::IsBuffDamage(const FDamageData& InDamageData)
{
	return InDamageData.BuffType != NAME_None;
}


float ASFCharacter::CalcActualDamage(const FDamageData& InDamageData)
{
	static const float MIN_DAMAGE = 1.f;

	float BlockDamage = InDamageData.DefaultDamage - FMath::Clamp(1.f - InDamageData.ArmorPenetration, 0.f, 1.f) * Stat.DEF;
	return FMath::Max(MIN_DAMAGE, BlockDamage);
}


void ASFCharacter::PlayHit(const FDamageData& InDamageData)
{
	// 자기 타입과 데미지 타입 따라 처리

	// 현재 스킬과 데미지 타입에 따라 스킬 캔슬 처리 필요 

	if(!IsPlayingSkill())
		PlayTestAnim(TEXT("Hit"));
}


void ASFCharacter::PlayDeath(const FDamageData& InDamageData)
{
	PlayTestAnim(TEXT("Death"));
}


void ASFCharacter::PlayBuff(const FDamageData& InDamageData)
{

}


void ASFCharacter::SkillMontageEndedDelegate(class UAnimMontage* Anim, bool bInterrupted)
{
	CurrentSkillID = NAME_None;
	
	OnSkillEnded.ExecuteIfBound();
}


void ASFCharacter::PlayTestAnim(FName SkillID)
{
	UAnimMontage** Anim = TestAnims.Find(SkillID);
	if (Anim == nullptr)
		return;

	PlayAnimMontage(*Anim);
}


void ASFCharacter::StopAction()
{
	GetMesh()->GetAnimInstance()->StopAllMontages(0.2f);
}