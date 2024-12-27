// Copyright Epic Games, Inc. All Rights Reserved.

#include "NewCPPGameMode.h"
#include "NewCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANewCPPGameMode::ANewCPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
