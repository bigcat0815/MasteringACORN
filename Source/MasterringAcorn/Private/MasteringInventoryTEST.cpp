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

	//�����ͼ�ȸ �ϸ鼭 �Ѿ��� ������ �ش� �����ʹ� �ǳʶٰ�
	//�迭�� ���Ⱑ �� ���ٸ� ��ü�Ѵ�.
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
	//�ڵ����� ���� ��ü
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
	//���� ���� ������ �Ѿ˸� ������Ʈ��Ű�� ������.
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

	//�����͸� ������Ʈ�ϰ� ����Ѵ�.
	FWeaponPropertiesTEST WeaponProps;
	WeaponProps.WeaponClass = weapon;
	WeaponProps.WeaponPower = WeaponPower;
	WeaponProps.Ammo = AmmoCount;

	WeaponsArray.Add(WeaponProps);

}

void UMasteringInventoryTEST::AddDefaultWeapon()
{
}

//const�� �ش� �Ӽ��� const�� ������
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
	
	//������ �ε��� == ������ ���� �ϰ�� ó������� ����
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

	//�ε���0���� ũ�ٸ� ���� �ε������� ���ʹ��⸦ ����
	if (iCurrentIndex > 0)
	{
		SelectWeapon(WeaponsArray[iCurrentIndex -1].WeaponClass);
	}
	else
	{
		//�ƴϸ� ���繫���� �� ������ ���� ����
		SelectWeapon(WeaponsArray[WeaponsArray.Num()-1].WeaponClass);
	}
}

void UMasteringInventoryTEST::ChangeAmmo(TSubclassOf<class AMasteringWeaponTEST> Weapon, const int ChangeAmount)
{
	//���繫�Ⱑ �Ѿ��� 0�̸� ź���� ���� �����߿� �������� ���� �����Ѵ�.
	for (auto WeaponIt = WeaponsArray.CreateIterator(); WeaponIt; ++WeaponIt)
	{
		FWeaponPropertiesTEST& currentProps = *WeaponIt;
		if (currentProps.WeaponClass == Weapon)
		{
			if (currentProps.Ammo == UNLIMITED_AMMO) //źȯ ������
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



