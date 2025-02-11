// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class NEWCPP_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	
	//에디터에서 TSubclassOf 해당 자료형 클래스만 드래그 가능하게
	//우리가 에디터에 넣어줄 UI클래스 원본
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG|UI")
	TSubclassOf<class UHUDWidget> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "RPG|UI")
	class UHUDWidget* UIHUDWidget; // 원본 기준으로 생성된 UI

public:
	class UHUDWidget* GetHUD();
	void CreateHUD();

	void SpawnPlayerStateSetting(class ANewCPPCharacter* Player);


};
