#include "LeverInteraction.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverInteraction.h"

ALeverInteraction::ALeverInteraction()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeverBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Base"));
	PhysConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Phys Constraint"));
	LowerTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Lower Trigger"));

	PhysConstraint->SetupAttachment(LeverBase);
	LowerTrigger->SetupAttachment(LeverBase);

	InteractionID = 0;

	LowerTrigger->SetGenerateOverlapEvents(true);
}

void ALeverInteraction::BeginPlay()
{
	Super::BeginPlay();
	LowerTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALeverInteraction::BeginOverlap);
	LowerTrigger->OnComponentEndOverlap.AddDynamic(this, &ALeverInteraction::OnOverlapEnd);
}

void ALeverInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALeverInteraction::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ALeverInteraction::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
