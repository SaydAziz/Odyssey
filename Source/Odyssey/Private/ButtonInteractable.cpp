// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetSystemLibrary.h"
#include "ButtonInteractable.h"

// Sets default values
AButtonInteractable::AButtonInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ButtonBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Base"));
	ButtonPush = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Push"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Button Trigger"));

	RootComponent = ButtonBase;
	ButtonPush->SetupAttachment(ButtonBase);
	Trigger->SetupAttachment(ButtonPush);

	ButtonOffset = 110.f;

	RelativeLoc = FVector(0, 0, ButtonOffset);

	ButtonPush->SetRelativeLocation(RelativeLoc);
}

// Called when the game starts or when spawned
void AButtonInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButtonInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	TArray<AActor*> Overlaps;
	Trigger->GetOverlappingActors(Overlaps);
	float newOffset;

	if (Overlaps.Num() > 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ENTERRRRRRRRRRRRRRRRRRRRRRRRRRRED"));
		newOffset = RelativeLoc.Z - 20;
	}
	else
	{
		newOffset = RelativeLoc.Z + 10;
	}
	newOffset = FMath::Clamp(newOffset, -100, ButtonOffset);
	RelativeLoc.Z = newOffset;

	FLatentActionInfo latentInfo;
	latentInfo.CallbackTarget = ButtonPush;
	UKismetSystemLibrary::MoveComponentTo(ButtonPush, RelativeLoc, FRotator::ZeroRotator, false, false, 0.0001f, false, EMoveComponentAction::Type::Move, latentInfo);
}

