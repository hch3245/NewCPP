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
	if (UIHUDWidget != nullptr) // �̹� ������ UI�� �ִ� ���
		return;

	// �����Ϳ��� ���� Ŭ������ �ִ� ��쿡�� �۾�
	if (UIHUDWidgetClass == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s()Missing UIHUDWidgetClass"), *FString(__FUNCTION__));
		return;
	}


	// UIHUDWidgetClass �������� ���� ����
	UIHUDWidget = CreateWidget<UHUDWidget>(GetWorld(), UIHUDWidgetClass);
	if(UIHUDWidget != nullptr)
	UIHUDWidget->AddToViewport(); // ����Ʈ�� �߰�����.
}

void AMyHUD::SpawnPlayerStateSetting(ANewCPPCharacter* Player)
{
	// �� �� ���� �� ������
	if (Player && UIHUDWidget) {
		UIHUDWidget->SetPlayer(Player);
		UIHUDWidget->SetCurrentHealth(Player->GetHealth());
		UIHUDWidget->SetMaxHealth(Player->GetMaxHealth());
	}
}
