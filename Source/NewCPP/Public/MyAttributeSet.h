// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MyAbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


// ��������Ʈ �Ķ���� �ΰ�¥��, �Ӽ� ����� ������ �� ��Ƽĳ��Ʈ�� ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeChangeDelegate, float, Attr, int32, StackCount);

UCLASS()
class NEWCPP_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);


	// Health���� ���� ���� �� ReplicationUsing�� �־��� �Լ��� ȣ��
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health); // ü�� �����Լ� ��ũ��
	
	//���� ü�� ����� ȣ���� ��������Ʈ
	FAttributeChangeDelegate HealthChangeDelegate;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;
};
