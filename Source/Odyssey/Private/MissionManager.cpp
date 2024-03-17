// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionManager.h"


void UMissionManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

UMissionManager::UMissionManager()
{
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Get to the escape pod and get out!", 2);
	 

	CurrentMission = MissionList[0];
}


void UMissionManager::BindToEvent(AButtonInteractable* button)
{
	button->ButtonPressed.AddDynamic(this, &UMissionManager::CheckInteracted);
}

void UMissionManager::CreateMission(FString Objective, int32 InteractableID)
{
	FMissionBeat MissionBeat;
	MissionBeat.MissionObjective = Objective;
	MissionBeat.RequiredInteractableID = InteractableID;

	MissionList.Add(MissionBeat);
}

UFUNCTION()
void UMissionManager::CheckInteracted(int32 ID)
{
	if (CurrentMission.RequiredInteractableID == ID)
	{
		CurrentMission.bIsCompleted = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mission Complete"));
	}
}
