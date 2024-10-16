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
	audioAmb2->VolumeMultiplier = 1;

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
			//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, TEXT("FADINGGGGGGGGGGGGGGGGGGGGGGG"));
			fadeAmbience();
			break;
		case EAmbienceState::waitingforfade:
			break;
	}
}

void AAudioManager::OnMissionChanged(FMissionBeat mission)
{
	NotifyMissionChanged(mission);
}

bool AAudioManager::ExitedActiveAmbienceVolume()
{
	if (!ActiveAmbience.VolumeBounds->EncompassesPoint(PlayerRef->GetActorLocation())) {
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("EXITED"));
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, FString::Printf(TEXT("LOC: x: %f  y: %f,  z: %f"), PlayerRef->GetActorLocation().X, PlayerRef->GetActorLocation().Y, PlayerRef->GetActorLocation().Z));
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Magenta, FString::Printf(TEXT("LOC: x: %f  y: %f,  z: %f"), ActiveAmbience.VolumeBounds->GetActorLocation().X, ActiveAmbience.VolumeBounds->GetActorLocation().Y, ActiveAmbience.VolumeBounds->GetActorLocation().Z));
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString::Printf(TEXT(" x: %f  y: %f,  z: %f"), ActiveAmbience.VolumeBounds->GetBounds().BoxExtent.X, ActiveAmbience.VolumeBounds->GetBounds().BoxExtent.Y, ActiveAmbience.VolumeBounds->GetBounds().BoxExtent.Z));
		return true;
	}
	return false;
}

void AAudioManager::SetNewActiveAmbience()
{
	FVector playerLoc = PlayerRef->GetActorLocation();
	for (FAudioAmbienceVolume av : AmbienceVolumeList) {
		if (av.VolumeBounds->EncompassesPoint(playerLoc)) {
			ActiveAmbience = av;
			currentAmbienceState = EAmbienceState::fading;
		}
	}
}

void AAudioManager::fadeAmbience()
{
	if (ambience1Active) {
		AdjustAmbienceSourceVolumes(audioAmb1, audioAmb2);
		ambience1Active = false;
	}
	else {
		AdjustAmbienceSourceVolumes(audioAmb2, audioAmb1);
		ambience1Active = true;
	}
	GetWorld()->GetTimerManager().SetTimer(ambienceFadeTimer, this, &AAudioManager::fadeComplete, AmbienceFadeTime, false);
	currentAmbienceState = EAmbienceState::waitingforfade;
}

void AAudioManager::AdjustAmbienceSourceVolumes(UAudioComponent* fadeInComp, UAudioComponent* fadeOutComp)
{
	fadeInComp->SetSound(ActiveAmbience.AmbienceFile);
	if (!fadeInComp->IsPlaying()) {
		fadeInComp->Play();
	}
	fadeInComp->FadeIn(AmbienceFadeTime, 1, 0 ,EAudioFaderCurve::Linear);
	fadeOutComp->FadeOut(AmbienceFadeTime, 0, EAudioFaderCurve::Linear);
}

void AAudioManager::fadeComplete()
{
	currentAmbienceState = EAmbienceState::active;
}

