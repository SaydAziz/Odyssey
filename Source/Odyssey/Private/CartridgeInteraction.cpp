// Fill out your copyright notice in the Description page of Project Settings.


#include "CartridgeInteraction.h"

ACartridgeInteraction::ACartridgeInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Casing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Casing"));
	Dock = CreateDefaultSubobject<ACartridgeDock>(TEXT("Dock"));
	SlotTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Slot Trigger"));

	InteractionID = 0;
}

void ACartridgeInteraction::BeginPlay()
{
	Super::BeginPlay();

	SlotTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACartridgeInteraction::BeginOverlap);
	SlotTrigger->OnComponentEndOverlap.AddDynamic(this, &ACartridgeInteraction::OnOverlapEnd);
}

void ACartridgeInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACartridgeInteraction::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACartridge::StaticClass()))
	{
		HasInteracted.Broadcast(InteractionID);
	}
}

void ACartridgeInteraction::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
