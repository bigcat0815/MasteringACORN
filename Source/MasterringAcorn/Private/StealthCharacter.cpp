// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthCharacter.h"

void AStealthCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("Stealth"), EInputEvent::IE_Pressed, this, &AStealthCharacter::Stealth);
	PlayerInputComponent->BindAction(TEXT("Stealth"), EInputEvent::IE_Released, this, &AStealthCharacter::UnStealth);

}

void AStealthCharacter::AddControllerPitchInput(float Val)
{
	const float fScale = bIsStealthed ? fStealthPitchYawScale : 1.0f;
	Super::AddControllerPitchInput(Val*fScale);
}

void AStealthCharacter::AddControllerYawInput(float Val)
{
	const float fScale = bIsStealthed ? fStealthPitchYawScale : 1.0f;
	Super::AddControllerYawInput(Val * fScale);
}

void AStealthCharacter::Stealth()
{
	bIsStealthed = true;
	Super::Crouch();

	ABLOG(Warning, TEXT("Stealth Mode"));
}

void AStealthCharacter::UnStealth()
{

	bIsStealthed = false;
	Super::UnCrouch();
}
