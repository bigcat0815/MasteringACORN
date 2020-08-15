// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MasterringAcorn.h"
#include "Components/ActorComponent.h"
#include "MasteringInventory.generated.h"

USTRUCT()
struct FWeaponProperties
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	TSubclassOf<class AMasterringWeapon> WeaponClass;

	UPROPERTY()
	int WeaponPower;

	UPROPERTY()
	int Ammo;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MASTERRINGACORN_API UMasteringInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UMasteringInventory();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AMasterringWeapon> DefaultWeapon;

	//���������� ������������ �ڵ� ����
	void SelectBestWeapon();

	//�κ��丮���� ���⼱��
	void SelectWeapon(TSubclassOf<class AMasterringWeapon> Weapon);

	//�κ��丮�� �����߰�
	void AddWeapon(TSubclassOf<class AMasterringWeapon> Weapon, int AmmoCount, uint8 WeaponPower);

	//������ �� �ִ� �⺻ ���� �߰�
	void AddDefaultWeapon();

	//���� ���õ� ���� ��������
	FORCEINLINE TSubclassOf<class AMasterringWeapon> GetCurrentWeapon() const
	{
		return CurrentWeapon;
	}

	//���ⱳü
	void ChangeAmmo(TSubclassOf<class AMasterringWeapon> Weapon,
		const int ChangeAmount);

protected:
	TArray<FWeaponProperties> WeaponsArray;
	TSubclassOf<class AMasterringWeapon> CurrentWeapon;
	int CurrentWeaponPower = -1;
	class AMasterringAcornCharacter* MyOwner;

public:
	int FindCurrentWeaponIndex() const;
	void SelectNextWeapon();
	void SelectPreviousWeapon();

	//Test
//public:
//	void SelectWeapon2(class AMasterringAcornCharacter* Player,
//		class AMasterringWeapon Weapon);
};
