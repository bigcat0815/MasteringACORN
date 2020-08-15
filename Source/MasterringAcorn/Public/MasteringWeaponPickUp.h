// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MasterringAcorn.h"
#include "GameFramework/Actor.h"
#include "MasteringWeaponPickUp.generated.h"

UCLASS()
class MASTERRINGACORN_API AMasteringWeaponPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasteringWeaponPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMasterringWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RotatorSpeed = 30.f;

	//ȹ��� ź���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 Ammunition = 10;

	//�ٸ������ ���� �� ������ ����� �Ŀ� ��ũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 WeaponPower = -1;

};
