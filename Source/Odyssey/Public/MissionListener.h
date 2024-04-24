// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MissionListener.generated.h"



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMissionListener : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ODYSSEY_API IMissionListener
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void OnMissionChanged(struct FMissionBeat mission) = 0;

};
