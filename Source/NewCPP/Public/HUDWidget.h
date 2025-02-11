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
	// BlueprintImplementableEvent 블프에서 코드 구현을 하도록
	// BlueprintCallable 블프에서 C++ 함수를 호출 가능하도록
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetPlayer(class ANewCPPCharacter* player);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCurrentHealth(float CurrentHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetMaxHealth(float MaxHealth);

};
