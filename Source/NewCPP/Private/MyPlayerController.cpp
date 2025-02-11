// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyHUD.h"
#include "NewCPP/NewCPPCharacter.h"

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// ��Ʈ�ѷ��� ������ ���� �ƴϸ� ���� ���ϵ���
	if (!IsLocalPlayerController())
		return;

	AHUD* hud = GetHUD();
	if (IsValid(hud)) 
	{
		AMyHUD* myhud = Cast<AMyHUD>(hud);
		if (IsValid(myhud)) 
		{
			myhud->CreateHUD();
			myhud->SpawnPlayerStateSetting(Cast<ANewCPPCharacter>(aPawn));
		}
	}
}

void AMyPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsLocalPlayerController())
		return;

	AHUD* hud = GetHUD();
	if (IsValid(hud))
	{
		AMyHUD* myhud = Cast<AMyHUD>(hud);
		if (IsValid(myhud))
		{
			myhud->CreateHUD();
			myhud->SpawnPlayerStateSetting(Cast<ANewCPPCharacter>(GetCharacter()));
		}
	}
}
