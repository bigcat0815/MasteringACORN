// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MasterringAcorn.h"
#include "Components/ActorComponent.h"
#include "MasteringInventoryTEST.generated.h"

//�κ��丮�� ���� ���ⱸ��ü
USTRUCT()
struct FWeaponPropertiesTEST
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		TSubclassOf<class AMasteringWeaponTEST> WeaponClass;

	//������
	UPROPERTY()
		int WeaponPower;

	UPROPERTY()
		int Ammo;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MASTERRINGACORN_API UMasteringInventoryTEST : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMasteringInventoryTEST();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//�⺻����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMasteringWeaponTEST> DefaultWeapon;

	//���������߿� �������� ���� �ڵ�����
	void SelectBestWeapon();

	//�κ��丮���� ���⼱��
	void SelectWeapon(TSubclassOf<class AMasteringWeaponTEST> Weapon);

	//�κ��丮�� �����߰�
	void AddWeapon(TSubclassOf<class AMasteringWeaponTEST> weapon, int AmmoCount, uint8 WeaponPower);

	//������ �� �ִ� �⺻����
	void AddDefaultWeapon();

	//���� ���õ� ���� ��������
	FORCEINLINE TSubclassOf<class AMasteringWeaponTEST> GetCurrentWeapon() const
	{
		return CurrentWeapon;
	}

protected:
	TArray<FWeaponPropertiesTEST> WeaponsArray;
	TSubclassOf<class AMasteringWeaponTEST> CurrentWeapon;
	int CurrentWeaponPower = -1; //����� ���ٴ� ��
	class AMasterringAcornCharacter* MyOwner;

	//�Ʒ��� ���� ������ �ƴϳ� ������ �帧�� �̸� �����ߴ�.
public:
	
	int FindCurrentWeaponIndex() const;
	void SelectNextWeapon();
	void SelectPreviousWeapon();

	//�Ѿ˱�ü
	void ChangeAmmo(TSubclassOf<class AMasteringWeaponTEST> Weapon,
		const int ChangeAmount);

};
