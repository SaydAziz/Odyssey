// Fill out your copyright notice in the Description page of Project Settings.


#include "CartridgeDock.h"

// Sets default values
ACartridgeDock::ACartridgeDock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RailPoint= CreateDefaultSubobject<USceneComponent>(TEXT("RailTrigger"));
	RailTrigger= CreateDefaultSubobject<UBoxComponent>(TEXT("RailPoint"));

	RailTrigger->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ACartridgeDock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACartridgeDock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



