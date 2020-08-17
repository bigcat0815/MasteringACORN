// Fill out your copyright notice in the Description page of Project Settings.

#include "MasteringInventoryTEST.h"
#include "MasterringAcornCharacter.h"
#include "MasteringWeaponTEST.h"

#define UNLIMITED_AMMO  -1

// Sets default values for this component's properties
UMasteringInventoryTEST::UMasteringInventoryTEST()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MyOwner = Cast<AMasterringAcornCharacter>(GetOwner());
	check(GetOwner() == nullptr || MyOwner != nullptr);
}

// Called when the game starts
void UMasteringInventoryTEST::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (DefaultWeapon != nullptr)
	{
		AddWeapon(DefaultWeapon, UNLIMITED_AMMO, 0);
	}
}

void UMasteringInventoryTEST::SelectBestWeapon()
{
	int bestWeaponPower = CurrentWeaponPower;
	TSubclassOf<class AMasteringWeaponTEST> bestWeapon = nullptr;

	//데이터순회 하면서 총알이 없으면 해당 데이터는 건너뛰고
	//배열의 무기가 더 높다면 교체한다.
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponPropertiesTEST& currentProps = *WeaponIt;

		if (currentProps.Ammo == 0) continue;
		if (currentProps.WeaponPower > bestWeaponPower)
		{
			bestWeaponPower = currentProps.WeaponPower;
			bestWeapon = currentProps.WeaponClass;
			CurrentWeaponPower = bestWeaponPower;
		}		
	}
	//자동으로 무기 교체
	if (bestWeapon != nullptr)
	{
		SelectWeapon(bestWeapon);
	}
}

void UMasteringInventoryTEST::SelectWeapon(TSubclassOf<class AMasteringWeaponTEST> Weapon)
{
	MyOwner->EquipWeaponTEST(Weapon);
	CurrentWeapon = Weapon;
}

void UMasteringInventoryTEST::AddWeapon(TSubclassOf<class AMasteringWeaponTEST> weapon, int AmmoCount, uint8 WeaponPower)
{
	//만약 같은 무기라면 총알만 업데이트시키고 나간다.
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponPropertiesTEST& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == weapon)
		{
			checkSlow(AmmoCount >= 0);
			currentProps.Ammo += AmmoCount;
			return;
		}
	}

	//데이터를 업데이트하고 등록한다.
	FWeaponPropertiesTEST WeaponProps;
	WeaponProps.WeaponClass = weapon;
	WeaponProps.WeaponPower = WeaponPower;
	WeaponProps.Ammo = AmmoCount;

	WeaponsArray.Add(WeaponProps);

}

void UMasteringInventoryTEST::AddDefaultWeapon()
{
}

//const라서 해당 속성도 const로 설정함
int UMasteringInventoryTEST::FindCurrentWeaponIndex() const
{
	int iCurrentIndex = 0;
	for (auto WeaponIt = WeaponsArray.CreateConstIterator();
		WeaponIt; ++WeaponIt, ++iCurrentIndex)
	{
		const FWeaponPropertiesTEST& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == CurrentWeapon)
			break;
	}
	checkSlow(iCurrentIndex < WeaponsArray.Num());
	return iCurrentIndex;
}

void UMasteringInventoryTEST::SelectNextWeapon()
{
	int iCurrentIndex = FindCurrentWeaponIndex();
	if (iCurrentIndex == 0) return;
	
	//마지막 인덱스 == 마지막 무기 일경우 처음무기로 변경
	if (iCurrentIndex == WeaponsArray.Num() - 1)
	{
		SelectWeapon(WeaponsArray[0].WeaponClass);
	}
	else
	{
		SelectWeapon(WeaponsArray[iCurrentIndex +1].WeaponClass);
	}
}

void UMasteringInventoryTEST::SelectPreviousWeapon()
{
	int iCurrentIndex = FindCurrentWeaponIndex();
	if (iCurrentIndex == 0) return;

	//인덱스0보다 크다면 현재 인덱스보다 앞쪽무기를 선택
	if (iCurrentIndex > 0)
	{
		SelectWeapon(WeaponsArray[iCurrentIndex -1].WeaponClass);
	}
	else
	{
		//아니면 현재무기의 젤 마지막 무기 선택
		SelectWeapon(WeaponsArray[WeaponsArray.Num()-1].WeaponClass);
	}
}

void UMasteringInventoryTEST::ChangeAmmo(TSubclassOf<class AMasteringWeaponTEST> Weapon, const int ChangeAmount)
{
	//현재무기가 총알이 0이면 탄약을 가진 무기중에 가장좋은 무기 선택한다.
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponPropertiesTEST& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == Weapon)
		{
			if (currentProps.Ammo == UNLIMITED_AMMO) //탄환 무제한
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



