// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "HUDWidget.h"
#include "NewCPP/NewCPPCharacter.h"

UHUDWidget* AMyHUD::GetHUD()
{
	return UIHUDWidget;
}

void AMyHUD::CreateHUD()
{
	if (UIHUDWidget != nullptr) // 이미 생성된 UI가 있는 경우
		return;

	// 에디터에서 위젯 클래스가 있는 경우에만 작업
	if (UIHUDWidgetClass == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s()Missing UIHUDWidgetClass"), *FString(__FUNCTION__));
		return;
	}


	// UIHUDWidgetClass 기준으로 위젯 생성
	UIHUDWidget = CreateWidget<UHUDWidget>(GetWorld(), UIHUDWidgetClass);
	if(UIHUDWidget != nullptr)
	UIHUDWidget->AddToViewport(); // 뷰포트에 추가해줌.
}

void AMyHUD::SpawnPlayerStateSetting(ANewCPPCharacter* Player)
{
	// 둘 다 생성 잘 됐으면
	if (Player && UIHUDWidget) {
		UIHUDWidget->SetPlayer(Player);
		UIHUDWidget->SetCurrentHealth(Player->GetHealth());
		UIHUDWidget->SetMaxHealth(Player->GetMaxHealth());
	}
}
