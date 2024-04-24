// Fill out your copyright notice in the Description page of Project Settings.


#include "LightManager.h"
#include "MissionManager.h"

// Sets default values
ALightManager::ALightManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightManager::BeginPlay()
{
	Super::BeginPlay();
	UMissionManager* missions = GetWorld()->GetSubsystem<UMissionManager>();
	missions->MissionChanged.AddDynamic(this, &ALightManager::OnMissionChanged);
}

// Called every frame
void ALightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightManager::OnMissionChanged(FMissionBeat mission)
{
	NotifyMissionChanged(mission);
}

