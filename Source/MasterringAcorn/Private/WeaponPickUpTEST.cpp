// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickUpTEST.h"
#include "MasteringInventoryTEST.h"
#include "MasterringAcornCharacter.h"

// Sets default values
AWeaponPickUpTEST::AWeaponPickUpTEST()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponPickUpTEST::BeginPlay()
{
	Super::BeginPlay();	
}

void AWeaponPickUpTEST::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AMasterringAcornCharacter* Player = Cast<AMasterringAcornCharacter>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}

	//pickup���� ������ ���� ĳ������ ���� �κ��丮�� �־��ش�.
	UMasteringInventoryTEST* Inventroy = Player->GetInventory();
	Inventroy->AddWeapon(WeaponClass, Ammunition, WeaponPower);

	//���� ���� ���� �� pickup�ı�
	Inventroy->SelectBestWeapon();
	Destroy();
}

// Called every frame
void AWeaponPickUpTEST::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotationAmount(0.0f, DeltaTime * RotatorSpeed, 0.0f);
	AddActorLocalRotation(rotationAmount);
}

