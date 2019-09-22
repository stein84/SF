// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common.h"
#include "GameFramework/Character.h"
#include "SFCharacter.generated.h"


/*
���� / ����� ���� 
�⺻ ���� ������ ����
ü�� ���� -> ���� ó��

�ִϸ��̼� ���� ���� ����
*/

USTRUCT(BlueprintType)
struct FCombatStat
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	float MaxHP;
	
	UPROPERTY(BlueprintReadOnly)
	float HP;

	UPROPERTY(BlueprintReadOnly)
	float Max_Shield;

	UPROPERTY(BlueprintReadOnly)
	float Shield;

	UPROPERTY(BlueprintReadOnly)
	float ATK;

	UPROPERTY(BlueprintReadOnly)
	float DEF;
};


DECLARE_DYNAMIC_DELEGATE(FOnCharacterDead);
DECLARE_DYNAMIC_DELEGATE(FOnSkillEnded);


UCLASS()
class SOCKETFIGHTERS_API ASFCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASFCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	// �÷��̾� ���� / npc ���� �������� �����ε�
	void SetupCombatData(const FCharacterLevelDataRow& CharLVData);
	void SetupCombatData(const FNPCDataRow* NPCData);
	void SetEnemy(ASFCharacter* InEnemy);


	void PlaySkill(FName SkillID);

	void PlayTestAnim(FName SkillID);

	UFUNCTION(BlueprintCallable)
	void TriggerSkillSequence();

	virtual void ApplyDamage(FDamageData InDamageData);
	
	bool IsPlayingSkill() const;
	bool IsDead() const;
	
	void StopAction();

protected:

	void ProcessSkillEffect(FSkillEffectData& EffectData);
	
	virtual bool CanApplyDamage(const FDamageData& InDamageData);
	virtual bool IsBuffDamage(const FDamageData& InDamageData);
	virtual float CalcActualDamage(const FDamageData& InDamageData);
	void PlayHit(const FDamageData& InDamageData);
	void PlayDeath(const FDamageData& InDamageData);
	void PlayBuff(const FDamageData& InDamageData);

	

	UFUNCTION()
	void SkillMontageEndedDelegate(class UAnimMontage* Anim, bool bInterrupted);

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FName, class UAnimMontage*> SkillAnims;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FName, class UAnimMontage*> TestAnims;


	UPROPERTY(BlueprintReadOnly)
	ASFCharacter* Enemy;

	UPROPERTY(BlueprintReadOnly)
	FCombatStat Stat;

	UPROPERTY()
	FOnCharacterDead OnCharacterDead;

	UPROPERTY()
	FOnSkillEnded OnSkillEnded;


private:

	FName CurrentSkillID;
	int32 SkillSequenceCounter = 0;

	FOnMontageBlendingOutStarted OnSkillMontageEnded;
};
