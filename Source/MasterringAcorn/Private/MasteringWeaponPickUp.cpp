// Fill out your copyright notice in the Description page of Project Settings.


#include "MasteringWeaponPickUp.h"
#include "MasteringInventory.h"
#include "MasterringAcornCharacter.h"

// Sets default values
AMasteringWeaponPickUp::AMasteringWeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMasteringWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMasteringWeaponPickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AMasterringAcornCharacter* Player = Cast<AMasterringAcornCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}

	UMasteringInventory* Inventory = Player->GetInventory();
	Inventory->AddWeapon(WeaponClass, Ammunition, WeaponPower);
	
	//좋은 무기자동선택
	Inventory->SelectBestWeapon();
	Destroy();
}



// Called every frame
void AMasteringWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotationAmount(0.0f, DeltaTime * RotatorSpeed, 0.0f);
	AddActorLocalRotation(rotationAmount);
}

