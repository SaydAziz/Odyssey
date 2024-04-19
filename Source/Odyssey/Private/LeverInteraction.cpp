#include "LeverInteraction.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "LeverInteraction.h"

ALeverInteraction::ALeverInteraction()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeverBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Base"));
	PhysConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Phys Constraint"));

	InteractionID = 0;
}

void ALeverInteraction::BeginPlay()
{
}

void ALeverInteraction::Tick(float DeltaTime)
{
}
