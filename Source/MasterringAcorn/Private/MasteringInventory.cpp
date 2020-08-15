// Fill out your copyright notice in the Description page of Project Settings.


#include "MasteringInventory.h"
#include "MasterringAcornCharacter.h"
#include "MasterringWeapon.h"

#define UNLIMITED_AMMO  -1

// Sets default values for this component's properties
UMasteringInventory::UMasteringInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	MyOwner = Cast<AMasterringAcornCharacter>(GetOwner());
	check(GetOwner() == nullptr || MyOwner != nullptr);
}


// Called when the game starts
void UMasteringInventory::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultWeapon != nullptr)
	{
		AddWeapon(DefaultWeapon,UNLIMITED_AMMO,0);
	}
}

void UMasteringInventory::SelectBestWeapon()
{
	int highestWeaponPower = CurrentWeaponPower;
	TSubclassOf<class AMasterringWeapon> bestWeapon = nullptr;

	for (auto WeaponIt = WeaponsArray.CreateIterator() ; WeaponIt; ++WeaponIt)
	{
		const FWeaponProperties& currentProps = *WeaponIt;
		
		if (currentProps.Ammo == 0)
			continue;
		if (currentProps.WeaponPower > highestWeaponPower)
		{
			highestWeaponPower = currentProps.WeaponPower;
			bestWeapon = currentProps.WeaponClass;
			CurrentWeaponPower = highestWeaponPower;
		}			
	}
	if (bestWeapon != nullptr)
	{
		SelectWeapon(bestWeapon);
	}
}

void UMasteringInventory::SelectWeapon(TSubclassOf<class AMasterringWeapon> Weapon)
{
	MyOwner->EquipWeapon(Weapon);
	CurrentWeapon = Weapon;
}

void UMasteringInventory::AddWeapon(TSubclassOf<class AMasterringWeapon> Weapon,
	int AmmoCount, uint8 WeaponPower)
{
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponProperties& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == Weapon)
		{
			checkSlow(AmmoCount >= 0);
			currentProps.Ammo += AmmoCount;
			return;
		}
	}

	FWeaponProperties WeaponProps;
	WeaponProps.WeaponClass = Weapon;
	WeaponProps.WeaponPower = WeaponPower;
	WeaponProps.Ammo = AmmoCount;

	WeaponsArray.Add(WeaponProps);

}

void UMasteringInventory::AddDefaultWeapon()
{

}

void UMasteringInventory::ChangeAmmo(TSubclassOf<class AMasterringWeapon> Weapon, const int ChangeAmount)
{
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponProperties& currentProps = *WeaponIt;

		if (currentProps.WeaponClass == Weapon)
		{
			if (currentProps.Ammo == UNLIMITED_AMMO)
				return;
			currentProps.Ammo = FMath::Clamp(currentProps.Ammo + ChangeAmount, 0, 999);
			if (currentProps.Ammo == 0)
			{
				CurrentWeaponPower = -1;
				SelectBestWeapon();
			}
			return;
		}
	}
}

int UMasteringInventory::FindCurrentWeaponIndex() const
{
	int iCurrentIndex = 0;
	for (auto WeaponIt = WeaponsArray.CreateConstIterator();
		WeaponIt; ++WeaponIt, ++iCurrentIndex)
	{
		const FWeaponProperties& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == CurrentWeapon)
			break;
	}
	checkSlow(iCurrentIndex < WeaponsArray.Num());
	return iCurrentIndex;
}

void UMasteringInventory::SelectNextWeapon()
{
	int iCurrentIndex = FindCurrentWeaponIndex();

	if (iCurrentIndex == 0)
	{
		return;
	}

	if (iCurrentIndex == WeaponsArray.Num() - 1)
	{
		SelectWeapon(WeaponsArray[0].WeaponClass);
	}
	else
	{
		SelectWeapon(WeaponsArray[iCurrentIndex + 1].WeaponClass);
	}
}

void UMasteringInventory::SelectPreviousWeapon()
{
	

	int iCurrentIndex = FindCurrentWeaponIndex();

	if (iCurrentIndex == 0)
	{
		return;
	}

	if (iCurrentIndex > 0)
	{
		SelectWeapon(WeaponsArray[iCurrentIndex - 1].WeaponClass);
	}
	else
	{
		SelectWeapon(WeaponsArray[WeaponsArray.Num() - 1].WeaponClass);
	}
}



