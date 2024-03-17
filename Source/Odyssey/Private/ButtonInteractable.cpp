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
	PressCheck = CreateDefaultSubobject<UBoxComponent>(TEXT("Press Check"));

	RootComponent = ButtonBase;
	PressCheck->SetupAttachment(ButtonBase);
	ButtonPush->SetupAttachment(ButtonBase);
	Trigger->SetupAttachment(ButtonPush);

	ButtonID = 0;

	PressCheck->SetGenerateOverlapEvents(true);

	ButtonOffset = 110.f;

	RelativeLoc = FVector(0, 0, ButtonOffset);

	ButtonPush->SetRelativeLocation(RelativeLoc);
}

// Called when the game starts or when spawned
void AButtonInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	PressCheck->OnComponentBeginOverlap.AddDynamic(this, &AButtonInteractable::BeginOverlap);
	PressCheck->OnComponentEndOverlap.AddDynamic(this, &AButtonInteractable::OnOverlapEnd);
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

void AButtonInteractable::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp == ButtonPush)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PRESSED>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"));
		ButtonPressed.Broadcast(ButtonID);
	}
}

void AButtonInteractable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

