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
	int iBestWeaponPower = CurrentWeaponPower;
	TSubclassOf<class ATESTWeaponBase> bestWeapon = nullptr;

	for (auto WeaponIt = WeaponArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponPropertiesTEST2& currentProps = *WeaponIt;
		if (currentProps.Ammo == 0) continue;
		if (currentProps.WeaponPower > iBestWeaponPower)
		{
			iBestWeaponPower = currentProps.WeaponPower;
			bestWeapon = currentProps.WeaponClass;
			CurrentWeaponPower = iBestWeaponPower;
		}
	}

	if (bestWeapon != nullptr)
	{
		SelectWeapon(bestWeapon);
	}
}

void UTESTInventory::SelectWeapon(TSubclassOf<class ATESTWeaponBase> Weapon)
{
	MyOwner->EquipWeaponTEST(Weapon);
	CurrentWeapon = Weapon;
}

void UTESTInventory::AddWeapon(TSubclassOf<class ATESTWeaponBase> Weapon, int AmmoCount, uint8 WeaponPower)
{
	for (auto WeaponIt = WeaponArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponPropertiesTEST2& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == CurrentWeapon)
		{
			checkSlow(AmmoCount >= 0);
			currentProps.Ammo += AmmoCount;
			return;
		}
	}

	FWeaponPropertiesTEST2 WeaponProps;
	WeaponProps.WeaponClass = Weapon;
	WeaponProps.Ammo = AmmoCount;
	WeaponProps.WeaponPower = WeaponPower;

	WeaponArray.Add(WeaponProps);
}


void UTESTInventory::AddDefaultWeapon()
{
}

void UTESTInventory::ChangeAmmo(TSubclassOf<class ATESTWeaponBase> Weapon, const int ChangeAmount)
{
	for (auto WeaponIt = WeaponArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponPropertiesTEST2& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == Weapon)
		{
			if (currentProps.Ammo == UNLIMITED_AMMO) return;

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

int UTESTInventory::FindCurrentWeaponIndex() const
{
	int iCurrentIndex = 0;
	for (auto WeaponIt = WeaponArray.CreateConstIterator(); WeaponIt; ++WeaponIt)
	{
		const FWeaponPropertiesTEST2& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == CurrentWeapon) break;
	}
	checkSlow(iCurrentIndex < WeaponArray.Num());
	
	return iCurrentIndex;
}

void UTESTInventory::SelectNextWeapon()
{
	int iCurrentIndex = FindCurrentWeaponIndex();
	if (iCurrentIndex == 0) return;

	if (iCurrentIndex == WeaponArray.Num() - 1)
	{
		SelectWeapon(WeaponArray[0].WeaponClass);
	}
	else
	{
		SelectWeapon(WeaponArray[iCurrentIndex + 1].WeaponClass);
	}
}

void UTESTInventory::SelectPreviousWeapon()
{
	int iCurrentIndex = FindCurrentWeaponIndex();
	if (iCurrentIndex == 0) return;
	if (iCurrentIndex > 0)
	{
		SelectWeapon(WeaponArray[iCurrentIndex - 1].WeaponClass);
	}
	else
	{
		SelectWeapon(WeaponArray[WeaponArray.Num() - 1].WeaponClass);
	}
}

