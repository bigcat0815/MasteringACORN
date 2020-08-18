// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTInventory.h"
#include "TESTCharacter.h"
#include "TESTWeaponBase.h"

#define UNLIMITED_AMMO -1


// Sets default values for this component's properties
UTESTInventory::UTESTInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...


	MyOwner = Cast<ATESTCharacter>(GetOwner());
	check(GetOwner() == nullptr || MyOwner != nullptr);
}


// Called when the game starts
void UTESTInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (DefaultWeapon != nullptr)
	{
		AddWeapon(DefaultWeapon, UNLIMITED_AMMO,0);
	}
	
}


// Called every frame
void UTESTInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTESTInventory::SelectBestWeapon()
{
}

void UTESTInventory::SelectWeapon(TSubclassOf<class ATESTWeaponBase> Weapon)
{
}

void UTESTInventory::AddWeapon(TSubclassOf<class ATESTWeaponBase> Weapon, int AmmoCount, uint8 WeaponPower)
{
}

void UTESTInventory::AddDefaultWeapon()
{
}

void UTESTInventory::ChangeAmmo(TSubclassOf<class ATESTWeaponBase> Weapon, const int ChangeAmount)
{
}

int UTESTInventory::FindCurrentWeaponIndex() const
{
	return 0;
}

void UTESTInventory::SelectNextWeapon()
{
}

void UTESTInventory::SelectPreviousWeapon()
{
}

