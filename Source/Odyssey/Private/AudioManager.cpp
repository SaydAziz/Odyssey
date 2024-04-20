// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "MissionManager.h"

// Sets default values
AAudioManager::AAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	UMissionManager* missions = GetWorld()->GetSubsystem<UMissionManager>();
	missions->MissionChanged.AddDynamic(this, &AAudioManager::OnMissionChanged);
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioManager::OnMissionChanged(FMissionBeat mission)
{
	NotifyMissionChanged(mission);
}

