// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MasterringAcornGameMode.h"
#include "MasterringAcornHUD.h"
#include "MasterringAcornCharacter.h"
#include "TESTCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMasterringAcornGameMode::AMasterringAcornGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	static ConstructorHelpers::FClassFinder<APawn> TESTPlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/BP_TESTFirstCharacter"));
	DefaultPawnClass = TESTPlayerPawnClassFinder.Class;
	// use our custom HUD class
	HUDClass = AMasterringAcornHUD::StaticClass();
}
