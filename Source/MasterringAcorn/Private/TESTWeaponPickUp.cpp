// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTWeaponPickUp.h"
#include "TESTCharacter.h"
#include "TESTInventory.h"

// Sets default values
ATESTWeaponPickUp::ATESTWeaponPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATESTWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATESTWeaponPickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ATESTCharacter* Player = Cast<ATESTCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}

	UTESTInventory* Inventory = Player->GetInventory();
	Inventory->AddWeapon(WeaponClass, Ammunition, WeaponPower);

	Inventory->SelectBestWeapon();
	Destroy();
}

// Called every frame
void ATESTWeaponPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, DeltaTime * RotatorSpeed, 0.0f));
}

