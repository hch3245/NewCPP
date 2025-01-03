// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{

}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}
