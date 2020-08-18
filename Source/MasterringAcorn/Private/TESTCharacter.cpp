// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTCharacter.h"
#include "MasterringAcornProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

#include "TESTInventory.h"
#include "TESTWeaponBase.h"


// Sets default values
ATESTCharacter::ATESTCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	//inventory
	Inventory = CreateDefaultSubobject<UTESTInventory>(TEXT("TESTINVENTORY"));

}

// Called when the game starts or when spawned
void ATESTCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATESTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATESTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATESTCharacter::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATESTCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATESTCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATESTCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATESTCharacter::LookUpAtRate);


	PlayerInputComponent->BindAction("InventoryUp", IE_Pressed, this, &ATESTCharacter::SelectPreviousWeaponTEST);
	PlayerInputComponent->BindAction("InventoryDown", IE_Pressed, this, &ATESTCharacter::SelectNextWeaponTEST);

}

void ATESTCharacter::OnFire()
{
	if (GetEquippedWeapon() != nullptr)
	{
		UAnimInstance* Anim = Mesh1P->GetAnimInstance();

		GetEquippedWeapon()->Fire(GetControlRotation(),Anim,Inventory);
	}
	
}

void ATESTCharacter::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ATESTCharacter::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void ATESTCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATESTCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATESTCharacter::EquipWeaponTEST(TSubclassOf<class ATESTWeaponBase> Weapon)
{
	UWorld* World = GetWorld();

	if (World == nullptr) return;
	if (EquippedWeaponActor != nullptr)
	{
		World->DestroyActor(EquippedWeaponActor);
	}

	//ºÎÂø
	const FRotator SpawnRotation = GetActorRotation();
	const FVector SpawnLocation = GetActorLocation();

	FActorSpawnParameters Parmas;
	Parmas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Parmas.Owner = this;

	EquippedWeaponActor = Cast<ATESTWeaponBase>(World->SpawnActor(Weapon, &SpawnLocation,
		&SpawnRotation, Parmas));

	if (EquippedWeaponActor != nullptr)
	{
		EquippedWeaponActor->AttachToComponent(Mesh1P,
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
			TEXT("GripPoint"));
	}
}

void ATESTCharacter::SelectNextWeaponTEST()
{
	Inventory->SelectNextWeapon();
}

void ATESTCharacter::SelectPreviousWeaponTEST()
{

	Inventory->SelectPreviousWeapon();
}

