// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionManager.h"


void UMissionManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

UMissionManager::UMissionManager()
{
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Collect the lab specimens and escape in the emergency pod.", 2);
	CreateMission("Investigate power outtage in engine room", 3);
	CreateMission("Get a replacement battery from storage", 4);
	CreateMission("Divert power to lab door at breaker room", 5);
	CreateMission("Retrieve samples in lab", 6);
	CreateMission("Take samples to emergency pod and escape", 7);
	CreateMission("Input coordinates at navigation", 8);
	CreateMission("Input coordinates at navigation", 8);
	CreateMission("Input coordinates at navigation", 8);
	CreateMission("Input coordinates at navigation", 8);
	CreateMission("Input coordinates at navigation", 8);
	CreateMission("Take Battery from engine and put in pod", 9);
	CreateMission("ESCAPE USING THE LAUNCH BUTTON", 10);
	 

	CurrentMissionIndex = 0;
	MissionChanged.Broadcast(MissionList[CurrentMissionIndex]);
}


void UMissionManager::BindToEvent(AInteractableObject* Interaction)
{
	Interaction->HasInteracted.AddDynamic(this, &UMissionManager::CheckInteracted);
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
	if (MissionList[CurrentMissionIndex].RequiredInteractableID == ID)
	{
		MissionList[CurrentMissionIndex].bIsCompleted = true;
		if (CurrentMissionIndex < MissionList.Num() - 1)
		{
			CurrentMissionIndex++;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mission Complete"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("All Missions Have been Complete"));
		}
		MissionChanged.Broadcast(MissionList[CurrentMissionIndex]);
	}
}
