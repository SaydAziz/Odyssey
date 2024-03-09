// Fill out your copyright notice in the Description page of Project Settings.


#include "CartridgeDock.h"

// Sets default values
ACartridgeDock::ACartridgeDock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RailPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RailPoint"));
	RailTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RailTrigger"));
	CustomPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomPlane"));

	RootComponent = RailPoint;
	RailTrigger->SetupAttachment(RailPoint);

	RailTrigger->SetGenerateOverlapEvents(true);
	RailTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACartridgeDock::BeginOverlap);
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

void ACartridgeDock::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FBodyInstance* BodyInstance = OtherComp->GetBodyInstance();
	if (BodyInstance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, BodyInstance->GetBodyDebugName());

		// Define the parameters of the custom plane
		FVector CustomPlaneNormal = CustomPlane->GetForwardVector(); // Normal vector of the custom plane

		// Set the DOF mode to CustomPlane
		BodyInstance->DOFMode = EDOFMode::CustomPlane;

		// Set the parameters of the custom plane
		BodyInstance->CustomDOFPlaneNormal = CustomPlaneNormal;

		OtherComp->BodyInstance.CreateDOFLock();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherComp->GetName());

	//OtherComp->GetBodyInstance()->bLockRotation = true;

	//OtherComp->GetBodyInstance()->bLockXTranslation = true;
	//OtherComp->GetBodyInstance()->bLockZTranslation = true;
}

void ACartridgeDock::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



