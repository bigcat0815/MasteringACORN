// Fill out your copyright notice in the Description page of Project Settings.


#include "MasteringIconCamera.h"
#include "TESTInventory.h"
#include "TESTWeaponPickUp.h"
#include "Engine/AssetManager.h"
#include "Engine/ObjectLibrary.h"
#include "Engine/Blueprint.h"
#include "Components/MeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HighResScreenshot.h"
#include "DrawDebugHelpers.h"

void AMasteringIconCamera::BeginPlay()
{
	Super::BeginPlay();
	
	if (bInitialied)
	{
		return;
	}

	bInitialied = true;
	CameraComp = GetCameraComponent();

	UWorld* World = GetWorld();
	check(World != nullptr);
	APlayerController* Player = World->GetFirstPlayerController();

	Player->SetCinematicMode(true, true, true, true, true);
	Player->SetViewTarget(this);
	
	FString contentPath = FString("/Game/") + WeaponsPath;

	static UObjectLibrary* objectLibray = nullptr;
	objectLibray = UObjectLibrary::CreateLibrary(ATESTWeaponPickUp::StaticClass(),
		false, GIsEditor);
	objectLibray->AddToRoot();
	objectLibray->bHasBlueprintClasses = true;

	objectLibray->LoadBlueprintAssetDataFromPath(contentPath);

	TArray<FAssetData> AssetDatas;
	objectLibray->GetAssetDataList(AssetDatas);

	for (auto itr : AssetDatas)
	{
		FSoftObjectPath assetPath(itr.ObjectPath.ToString());
		WeaponBlueprintSoftRefs.Add(assetPath);
	}

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	Streamable.RequestAsyncLoad(WeaponBlueprintSoftRefs,
		FStreamableDelegate::CreateUObject(this, &AMasteringIconCamera::OnFinishedLoadingAssets));

}

void AMasteringIconCamera::TakeShot()
{
	UWorld* World = GetWorld();

	check(CurrentWeaponPickup != nullptr);

	UMeshComponent* Mesh = Cast<UMeshComponent>(CurrentWeaponPickup->GetComponentByClass(UMeshComponent::StaticClass()));
	check(Mesh != nullptr);


	Mesh->bForceMipStreaming = true;

	Mesh->SetRenderCustomDepth(true);

	GScreenshotResolutionX = ScreenshotResolutionX;
	GScreenshotResolutionY = ScreenshotResolutionY;

	GetHighResScreenshotConfig().SetHDRCapture(true);
	GetHighResScreenshotConfig().bMaskEnabled = true;
	World->GetGameViewport()->Viewport->TakeHighResScreenShot();

	FTimerHandle SpawnNextTimer;
	World->GetTimerManager().SetTimer(SpawnNextTimer, [this] {
		if (CurrentWeaponIndex >= WeaponBlueprints.Num())
		{
			CurrentWeaponIndex = 0;
		}
		else
		{
			SpawnAndPlaceNextActor();
		}
	},0.001f,false);
}

void AMasteringIconCamera::SpawnAndPlaceNextActor()
{
	if (CurrentWeaponPickup != nullptr)
		CurrentWeaponPickup->Destroy();

	CurrentWeaponBlueprint = WeaponBlueprints[CurrentWeaponIndex];
	check(CurrentWeaponBlueprint != nullptr); // anything not a blueprint should never find its way into our list

	UWorld* World = GetWorld();

	FRotator Rot(0.0f);
	FVector Trans(0.0f);

	FTransform Transform(Rot, Trans);
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	CurrentWeaponPickup = World->SpawnActor<ATESTWeaponPickUp>(CurrentWeaponBlueprint->GeneratedClass, Transform, ActorSpawnParams);
	CurrentWeaponPickup->RotatorSpeed = 0.0f; // the ones we use for screenshots we don't want spinning!
	check(CurrentWeaponPickup != nullptr);

	FVector Pos = ComputeActorLocation();
	CurrentWeaponPickup->SetActorLocation(Pos);

	CurrentWeaponIndex++;
}

FVector AMasteringIconCamera::ComputeActorLocation()
{
	check(CurrentWeaponPickup != nullptr);
	UMeshComponent* Mesh = Cast<UMeshComponent>(CurrentWeaponPickup->GetComponentByClass(UMeshComponent::StaticClass()));

	FVector InPos;
	FVector BoxExtent;
	CurrentWeaponPickup->GetActorBounds(false, InPos, BoxExtent);
	
	const float fX = BoxExtent.X;
	const float fY = BoxExtent.Y;
	const float fZ = BoxExtent.Z;

	if (fX > fY)
	{
		FRotator YawRot(0.0f, 90.0f, 0.0f);
		CurrentWeaponPickup->SetActorRotation(YawRot);
	}

	const float fLongestBoxSide = FMath::Max(fX, FMath::Max(fY, fZ));

	const float FOVhalf = 0.5f * CameraComp->FieldOfView;
	const float FOVradians = FOVhalf * PI / 180.0f;

	const float FOVtan = FMath::Tan(FOVradians);

	float XDistance = fLongestBoxSide / FOVtan;

	FVector Positioning(XDistance, 0.0f, 0.0f);

	return CurrentWeaponPickup->GetActorLocation() + Positioning - InPos;

}

void AMasteringIconCamera::OnFinishedLoadingAssets()
{
	UWorld* World = GetWorld();

	for (auto itr = WeaponBlueprintSoftRefs.CreateIterator(); itr; ++itr)
	{
		UBlueprint* BPObj = CastChecked<UBlueprint>((*itr).ResolveObject());
		WeaponBlueprints.Add(BPObj);
	}

	SpawnAndPlaceNextActor();

	static FTimerHandle ScreenShotTimer;
	World->GetTimerManager().SetTimer(ScreenShotTimer, [=] {
		if (CurrentWeaponIndex == 0)
		{
			World->GetTimerManager().ClearTimer(ScreenShotTimer);
			if (APlayerController* Player = UGameplayStatics::GetPlayerController(World, 0))
			{
				Player->ConsoleCommand(TEXT("Exit"), true);
				return;
			}
		}
		TakeShot();
	},
		ShotDelay,true,ShotDelay);
}
