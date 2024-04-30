// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "InteractableObject.h"
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

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionChanged, FMissionBeat, Mission);

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

	UPROPERTY(BlueprintAssignable)
	FOnMissionChanged MissionChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMissionBeat> MissionList;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<AInteractableObject*> WatchedInteractions;
	
	UFUNCTION()
	void BindToEvent(AInteractableObject* Interaction);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentMissionIndex;

private:



	UFUNCTION()
	void CreateMission(FString Objective, int32 InteractableID);

	UFUNCTION()
	void CheckInteracted(int32 ID);

};
