// Fill out your copyright notice in the Description page of Project Settings.


#include "Cartridge.h"

// Sets default values
ACartridge::ACartridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACartridge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACartridge::Tick(float DeltaTime)
{
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, TEXT("####" + bIsInserted));
	if (bIsInPlace)
	{	
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, TEXT("TickUpdate"));
		Cast<UStaticMeshComponent>(GetRootComponent())->GetBodyInstance()->SetLinearVelocity(FVector::Zero(), false, false);
	}
	Super::Tick(DeltaTime);

}

void ACartridge::OnInserted(bool InsertState)
{
	bIsInPlace = InsertState;
	OnInsertedNotify();
}

