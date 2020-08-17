// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MasterringAcorn.h"
#include "GameFramework/Actor.h"
#include "WeaponPickUpTEST.generated.h"

UCLASS()
class MASTERRINGACORN_API AWeaponPickUpTEST : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickUpTEST();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//액터와 접촉했을때 이벤트
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMasteringWeaponTEST> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float RotatorSpeed = 30.f;

	//획득시 탄약수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 Ammunition = 10;

	//다른무기와 비교한 이 무기의 상대적 파워 랭크 기본이 1로 되어있다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 WeaponPower = 1;
};
