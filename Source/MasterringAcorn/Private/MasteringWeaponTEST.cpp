// Fill out your copyright notice in the Description page of Project Settings.


#include "MasteringWeaponTEST.h"
#include "MasterringAcornCharacter.h"
#include "MasterringAcornProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "MasteringInventoryTEST.h"

// Sets default values
AMasteringWeaponTEST::AMasteringWeaponTEST()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Mesh
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetOnlyOwnerSee(true);
	WeaponMesh->bCastDynamicShadow = false;
	WeaponMesh->CastShadow = false;
	WeaponMesh->SetupAttachment(RootComponent);

	//Muzzle
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AMasteringWeaponTEST::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasteringWeaponTEST::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasteringWeaponTEST::Fire(FRotator ControlRotation, UAnimInstance* AnimInst, UMasteringInventoryTEST* Inventory)
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FVector SpawnLocation = ((MuzzleLocation != nullptr) ?
				MuzzleLocation->GetComponentLocation() : GetActorLocation()) +
				ControlRotation.RotateVector(GunOffset);

			//스폰콜리전 방식
			FActorSpawnParameters ActorSpawnParms;
			ActorSpawnParms.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AMasterringAcornProjectile>(ProjectileClass,
				SpawnLocation, ControlRotation, ActorSpawnParms);
		}
	}

	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation != nullptr)
	{
		AnimInst->Montage_Play(FireAnimation, 1.f);
	}
	Inventory->ChangeAmmo(GetClass(), -1);
}

