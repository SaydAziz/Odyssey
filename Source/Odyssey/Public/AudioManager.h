// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissionListener.h"
#include "AudioManager.generated.h"


USTRUCT(BlueprintType)
struct FAudioAmbienceVolume {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AAudioVolume* VolumeBounds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* AmbienceFile;
};

UENUM()
enum class EAmbienceState : uint8 {
	active UMETA(DIsplayName = "active"), fading UMETA(DIsplayName = "fading"), waitingforfade UMETA(DIsplayName = "waitingforfade")
};

UCLASS()
class ODYSSEY_API AAudioManager : public AActor, public IMissionListener
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//UFUNCTION(BlueprintImplementableEvent)
	//void NotifyMissionChanged(struct FMissionBeat);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EAmbienceState currentAmbienceState;

	UFUNCTION()
	virtual void OnMissionChanged(struct FMissionBeat mission) override;

	UFUNCTION(BlueprintImplementableEvent)
	void NotifyMissionChanged(struct FMissionBeat mission);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AVrPlayerPawn* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAudioAmbienceVolume> AmbienceVolumeList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AmbienceFadeTime;

	FAudioAmbienceVolume ActiveAmbience;

	bool ExitedActiveAmbienceVolume();

	void SetNewActiveAmbience();
	//cache current box, if no longer inside current box then loop through the others and find which one the player is in
	//adjust the volumes of the ambiences accordingly

	//allows for fading
	UAudioComponent* audioAmb1;
	UAudioComponent* audioAmb2;

	bool ambience1Active;
	void fadeAmbience();
	void AdjustAmbienceSourceVolumes(UAudioComponent* fadeInComp, UAudioComponent* fadeOutComp);

	FTimerHandle ambienceFadeTimer;
	void fadeComplete();

};
