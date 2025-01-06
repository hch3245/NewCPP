// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"

#include "Net/UnrealNetwork.h" // 언리얼 통신 과련, 멀티캐스트 사용하기 위해
#include "GameplayEffect.h" // 능력치 전달용 이펙트, 버프, 디버프
#include "GameplayEffectExtension.h"


void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	// 이벤트 받기 위해 RepNOtify 선언 GetLifetimeReplicatedProps도 있어야 함
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
	// 이펙트 변경시 해당 하는 이펙트가 뭔지 확인후 처리 
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) {	// 변경된 데이터 타입 확인
		
		SetHealth(FMath::Clamp(GetHealth(), 0.f, 1000.f));

		// HealthChangeDelegate에 넣은 함수에 전부 전달
		HealthChangeDelegate.Broadcast(GetHealth(), Data.EffectSpec.StackCount);
	}
}
