// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTWeaponBase.h"
#include "TESTCharacter.h"
#include "MasterringAcornProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATESTWeaponBase::ATESTWeaponBase()
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
void ATESTWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATESTWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

