// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MasterringAcorn.h"
#include "Components/ActorComponent.h"
#include "MasteringInventoryTEST.generated.h"

//인벤토리에 담을 무기구조체
USTRUCT()
struct FWeaponPropertiesTEST
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
		TSubclassOf<class AMasteringWeaponTEST> WeaponClass;

	//무기등급
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
	
	//기본무기
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMasteringWeaponTEST> DefaultWeapon;

	//보유무기중에 가장좋은 무기 자동선택
	void SelectBestWeapon();

	//인벤토리에서 무기선택
	void SelectWeapon(TSubclassOf<class AMasteringWeaponTEST> Weapon);

	//인벤토리에 무기추가
	void AddWeapon(TSubclassOf<class AMasteringWeaponTEST> weapon, int AmmoCount, uint8 WeaponPower);

	//설정할 수 있는 기본무기
	void AddDefaultWeapon();

	//현재 선택된 무기 가져오기
	FORCEINLINE TSubclassOf<class AMasteringWeaponTEST> GetCurrentWeapon() const
	{
		return CurrentWeapon;
	}

protected:
	TArray<FWeaponPropertiesTEST> WeaponsArray;
	TSubclassOf<class AMasteringWeaponTEST> CurrentWeapon;
	int CurrentWeaponPower = -1; //현재는 없다는 뜻
	class AMasterringAcornCharacter* MyOwner;

	//아래는 지금 구성은 아니나 교재의 흐름상 미리 기입했다.
public:
	
	int FindCurrentWeaponIndex() const;
	void SelectNextWeapon();
	void SelectPreviousWeapon();

	//총알교체
	void ChangeAmmo(TSubclassOf<class AMasteringWeaponTEST> Weapon,
		const int ChangeAmount);

};
