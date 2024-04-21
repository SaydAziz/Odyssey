// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "VrPlayerPawn.h"
#include "MissionManager.h"
#include <Kismet/GameplayStatics.h>
#include "Components/AudioComponent.h"

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
	ActiveAmbience = AmbienceVolumeList[0];

	audioAmb1 = NewObject<UAudioComponent>(this);
	audioAmb1->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	audioAmb1->bIsUISound = true;
	audioAmb1->VolumeMultiplier = 1;

	audioAmb2 = NewObject<UAudioComponent>(this);
	audioAmb2->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	audioAmb2->bIsUISound = true;
	audioAmb2->VolumeMultiplier = 0;

	audioAmb1->SetSound(ActiveAmbience.AmbienceFile);
	audioAmb1->Play();
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (currentAmbienceState) {
		case EAmbienceState::active:
			if (ExitedActiveAmbienceVolume()) {
				SetNewActiveAmbience();
			}
			break;
		case EAmbienceState::fading:
			fadeAmbience();
			break;
	}
}

void AAudioManager::OnMissionChanged(FMissionBeat mission)
{
	NotifyMissionChanged(mission);
}

bool AAudioManager::ExitedActiveAmbienceVolume()
{
	if (!ActiveAmbience.VolumeBounds->IsOverlappingActor(PlayerRef)) {
		return true;
	}
	return false;
}

void AAudioManager::SetNewActiveAmbience()
{
	for (FAudioAmbienceVolume av : AmbienceVolumeList) {
		if (av.VolumeBounds->IsOverlappingActor(PlayerRef)) {
			
			ActiveAmbience = av;
			currentAmbienceState = EAmbienceState::fading;
		}
	}
}

void AAudioManager::fadeAmbience()
{
	float amb1vol = 0, amb2vol = 0;
	if (ambience1Active) {
		audioAmb1->SetSound(ActiveAmbience.AmbienceFile);
		audioAmb1->Play();
		amb1vol = 1;
		ambience1Active = false;
	}
	else {
		audioAmb2->SetSound(ActiveAmbience.AmbienceFile);
		if (!audioAmb2->IsPlaying()) {
			audioAmb2->Play();
		}
		amb2vol = 1;
		ambience1Active = true;
	}
	audioAmb1->AdjustVolume(1.0f, 0, EAudioFaderCurve::Logarithmic);
	audioAmb2->AdjustVolume(1.0, 1, EAudioFaderCurve::Logarithmic);
	currentAmbienceState = EAmbienceState::active;
}

