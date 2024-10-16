// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionManager.h"


void UMissionManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

UMissionManager::UMissionManager()
{
	CreateMission("Retrieve samples in lab", 1);
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Get to communications and fix comms.", 1);
	CreateMission("Collect the lab specimens and escape in the emergency pod.", 2);
	CreateMission("Investigate power outage in engine room", 3);
	CreateMission("Get a replacement battery from storage", 4);
	CreateMission("Divert power to lab door at breaker room", 5);
	CreateMission("Retrieve samples in lab", 6);
	CreateMission("You should see a recorder.", 7);
	CreateMission("Take samples to emergency pod and escape", 8);
	CreateMission("Input coordinates at navigation", 9);
	CreateMission("Input coordinates at navigation", 9);
	CreateMission("Input coordinates at navigation", 9);
	CreateMission("Input coordinates at navigation", 9);
	CreateMission("Input coordinates at navigation", 9);
	CreateMission("Take Battery from engine and put in pod", 10);
	CreateMission("ESCAPE USING THE LAUNCH BUTTON", 11);

	//creature spawn in on lab sample completion, trigger to make it hide back in engine

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
