// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"

#include "Net/UnrealNetwork.h" // �𸮾� ��� ����, ��Ƽĳ��Ʈ ����ϱ� ����
#include "GameplayEffect.h" // �ɷ�ġ ���޿� ����Ʈ, ����, �����
#include "GameplayEffectExtension.h"


void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	// �̺�Ʈ �ޱ� ���� RepNOtify ���� GetLifetimeReplicatedProps�� �־�� ��
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Health, OldHealth);
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMyAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	// ����Ʈ ����� �ش� �ϴ� ����Ʈ�� ���� Ȯ���� ó�� 
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {	// ����� ������ Ÿ�� Ȯ��
		
		SetHealth(FMath::Clamp(GetHealth(), 0.f, 1000.f));

		// HealthChangeDelegate�� ���� �Լ��� ���� ����
		HealthChangeDelegate.Broadcast(GetHealth(), Data.EffectSpec.StackCount);
	}
}
