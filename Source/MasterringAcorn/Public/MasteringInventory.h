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

	//보유무기중 가장좋은무기 자동 선택
	void SelectBestWeapon();

	//인벤토리에서 무기선택
	void SelectWeapon(TSubclassOf<class AMasterringWeapon> Weapon);

	//인벤토리에 무기추가
	void AddWeapon(TSubclassOf<class AMasterringWeapon> Weapon, int AmmoCount, uint8 WeaponPower);

	//설정할 수 있는 기본 무기 추가
	void AddDefaultWeapon();

	//현재 선택된 무기 가져오기
	FORCEINLINE TSubclassOf<class AMasterringWeapon> GetCurrentWeapon() const
	{
		return CurrentWeapon;
	}

	//무기교체
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
