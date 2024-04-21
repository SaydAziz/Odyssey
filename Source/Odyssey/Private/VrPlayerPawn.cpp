// Fill out your copyright notice in the Description page of Project Settings.

#include "VrPlayerPawn.h"


// Sets default values
AVrPlayerPawn::AVrPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Physics Root"));
	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	HeadCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Head Collision"));

	RootComponent = PhysicsRoot;
	VROrigin->SetupAttachment(PhysicsRoot);
	Camera->SetupAttachment(VROrigin);
	HeadCollision->SetupAttachment(Camera);



}

// Called when the game starts or when spawned
void AVrPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVrPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVrPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

