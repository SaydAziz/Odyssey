// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ButtonInteractable.h"
#include "MissionManager.generated.h"

USTRUCT(BlueprintType)
struct FMissionBeat
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MissionObjective;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredInteractableID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCompleted;
	
};



/**
 * 
 */
UCLASS()
class ODYSSEY_API UMissionManager : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:

	UMissionManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMissionBeat> MissionList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AButtonInteractable*> WatchedButtons;
	
	UFUNCTION()
	void BindToEvent(AButtonInteractable* button);
private:

	UPROPERTY(EditAnywhere)
	FMissionBeat CurrentMission;

	UFUNCTION()
	void CreateMission(FString Objective, int32 InteractableID);

	UFUNCTION()
	void CheckInteracted(int32 ID);

};
