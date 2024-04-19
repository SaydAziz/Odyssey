// Fill out your copyright notice in the Description page of Project Settings.


#include "CartridgeInteraction.h"

ACartridgeInteraction::ACartridgeInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Casing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Casing"));
	SlotTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Slot Trigger"));

	RootComponent = Casing;
	SlotTrigger->SetupAttachment(RootComponent);

	InteractionID = 0;
}

void ACartridgeInteraction::BeginPlay()
{
	Super::BeginPlay();

	TSet<UActorComponent*> components = GetComponents();

	for (UActorComponent* comp : components)
	{
		UBoxComponent* trigger = Cast<UBoxComponent>(comp);
		if (trigger)
		{
			SlotTriggerInfo.Add(trigger, false);
		}
	}

	for (const auto& Pair : SlotTriggerInfo)
	{
		Pair.Key->OnComponentBeginOverlap.AddDynamic(this, &ACartridgeInteraction::BeginOverlap);
		Pair.Key->OnComponentEndOverlap.AddDynamic(this, &ACartridgeInteraction::OnOverlapEnd);

	}
}

void ACartridgeInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, FString::FromInt(SlotTriggerInfo.Num()));
}

void ACartridgeInteraction::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACartridge::StaticClass()))
	{
		SlotTriggerInfo.Add(Cast<UBoxComponent>(OverlappedComponent), true);
	}

	for (const auto& Pair : SlotTriggerInfo)
	{
		if (Pair.Value == false)
		{
			return;
		}
	}
	HasInteracted.Broadcast(InteractionID);
}

void ACartridgeInteraction::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		SlotTriggerInfo.Add(Cast<UBoxComponent>(OverlappedComp), false);
}
