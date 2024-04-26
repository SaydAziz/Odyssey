// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MissionListener.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightManager.generated.h"

UCLASS()
class ODYSSEY_API ALightManager : public AActor, public IMissionListener
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnMissionChanged(struct FMissionBeat mission) override;

	UFUNCTION(BlueprintImplementableEvent)
	void NotifyMissionChanged(struct FMissionBeat mission);

};
