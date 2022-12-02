// Copyright Epic Games, Inc. All Rights Reserved.

#include "BrainDamageGameMode.h"
#include "BrainDamageCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABrainDamageGameMode::ABrainDamageGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
