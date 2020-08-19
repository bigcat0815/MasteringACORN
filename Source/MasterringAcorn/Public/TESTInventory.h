// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MasterringAcorn.h"
#include "Components/ActorComponent.h"
#include "TESTWeaponBase.h"
#include "TESTInventory.generated.h"


USTRUCT()
struct FWeaponPropertiesTEST2
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	TSubclassOf<class ATESTWeaponBase> WeaponClass;

	UPROPERTY()
	int Ammo;

	UPROPERTY()
	int WeaponPower;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTERRINGACORN_API UTESTInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTESTInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATESTWeaponBase> DefaultWeapon;

	//���������� ������������ �ڵ� ����
	void SelectBestWeapon();

	//�κ��丮���� ���⼱��
	//void SelectWeapon(FWeaponPropertiesTEST2 Weapon);
	void SelectWeapon(TSubclassOf<class ATESTWeaponBase> Weapon);

	//�κ��丮�� �����߰�
	void AddWeapon(TSubclassOf<class ATESTWeaponBase> Weapon, int AmmoCount, uint8 WeaponPower);
	//void AddWeapon(const FWeaponPropertiesTEST2 &Properties);

	//������ �� �ִ� �⺻ ���� �߰�
	void AddDefaultWeapon();
	
	FORCEINLINE TSubclassOf<class ATESTWeaponBase> GetCurrentWeapon() const
	{
		return CurrentWeapon;
	}

	FORCEINLINE TArray<FWeaponPropertiesTEST2>& GetWeaponsArray() { return WeaponArray; }

	FORCEINLINE int GetCurrentWeaponPower() const { return CurrentWeaponPower; }



	void ChangeAmmo(TSubclassOf<class ATESTWeaponBase> Weapon,
		const int ChangeAmount);


	//DECLARE_EVENT_OneParam(UTESTInventory, FSelectedWeaponChanged, FWeaponPropertiesTEST2);
	//FSelectedWeaponChanged OnSelectedWeaponChanged;

	//DECLARE_EVENT_OneParam(UTESTInventory, FWeaponAdded, FWeaponPropertiesTEST2);
	//FSelectedWeaponChanged OnWeaponAdded;

	//DECLARE_EVENT_OneParam(UTESTInventory, FWeaponRemoved, FWeaponPropertiesTEST2);
	//FSelectedWeaponChanged OnWeaponRemoved;

protected:
	TArray<FWeaponPropertiesTEST2> WeaponArray;
	TSubclassOf<class ATESTWeaponBase> CurrentWeapon;
	int CurrentWeaponPower = -1;
	class ATESTCharacter* MyOwner;

public:
	int FindCurrentWeaponIndex() const;
	void SelectNextWeapon();
	void SelectPreviousWeapon();
};
