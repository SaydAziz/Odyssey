// Fill out your copyright notice in the Description page of Project Settings.

#include "MissionManager.h"
#include "InteractableObject.h"

// Sets default values
AInteractableObject::AInteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();

	UMissionManager* missions = GetWorld()->GetSubsystem<UMissionManager>();
	missions->BindToEvent(static_cast<AInteractableObject*>(this));
	
}

// Called every frame
void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
