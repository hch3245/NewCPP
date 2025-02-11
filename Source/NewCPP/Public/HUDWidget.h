// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEWCPP_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// BlueprintImplementableEvent �������� �ڵ� ������ �ϵ���
	// BlueprintCallable �������� C++ �Լ��� ȣ�� �����ϵ���
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetPlayer(class ANewCPPCharacter* player);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float CurrentHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

};
