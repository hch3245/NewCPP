// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyHUD.h"
#include "NewCPP/NewCPPCharacter.h"

void AMyPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// 컨트롤러의 주인이 내가 아니면 생성 안하도록
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
