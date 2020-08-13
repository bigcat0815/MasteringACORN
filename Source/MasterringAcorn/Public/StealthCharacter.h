// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MasterringAcorn.h"
#include "MasterringAcornCharacter.h"
#include "StealthCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MASTERRINGACORN_API AStealthCharacter : public AMasterringAcornCharacter
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float fStealthPitchYawScale = 0.5f;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void AddControllerPitchInput(float Val) override;
	virtual void AddControllerYawInput(float Val) override;

	void Stealth();
	void UnStealth();
protected:
	bool bIsStealthed = false;
	

};
