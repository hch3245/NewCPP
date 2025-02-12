// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "MyAbilitySystemComponent.h"
#include "AsyncTaskAttributeChanged.generated.h"

/**
 * 
 */


// 델리게이트 파라미터 3개짜리 생성
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged,FGameplayAttribute,Attribute,float,NewValue,float,OldValue);

// 블루프린트 로드에서 자동으로 리스너를 등록하여
// Attribute가 변경됐을 때 호출해줄 수 있도록 함
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class NEWCPP_API UAsyncTaskAttributeChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged; // 함수 포인터

	// 변경 됐을 때 블루프린트 확인 가능하도록 static이라 아무곳에서나 호출 가능
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = true))
	static UAsyncTaskAttributeChanged* ListenForAttributeChange(
		UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = true))
	static UAsyncTaskAttributeChanged* ListenForAttributesChange(
		UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayAttribute AttributeToListenFor; // 값 들어있는애 하나 기다려서 체크
	TArray<FGameplayAttribute> AttributesToListenFor; // 여러 개

	// 값 변경될 때 이거 호출
	void AttributeChanged(const FOnAttributeChangeData& Data);
};
