// Fill out your copyright notice in the Description page of Project Settings.


#include "CartridgeDock.h"

// Sets default values
ACartridgeDock::ACartridgeDock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RailPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RailPoint"));
	RailTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("RailTrigger"));

	RootComponent = RailTrigger;
	RailPoint->SetupAttachment(RailTrigger);

	RailTrigger->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ACartridgeDock::BeginPlay()
{
	RailTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACartridgeDock::BeginOverlap);
	RailTrigger->OnComponentEndOverlap.AddDynamic(this, &ACartridgeDock::OnOverlapEnd);
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

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherComp->GetName());

		OtherActor->SetActorRotation(FQuat::Identity);
		OtherActor->SetActorLocation(RailPoint->GetComponentLocation());

		OtherComp->GetBodyInstance()->bLockXRotation = true;
		OtherComp->GetBodyInstance()->bLockYRotation = true;
		OtherComp->GetBodyInstance()->bLockZRotation = true;

		OtherComp->GetBodyInstance()->bLockXTranslation = true;
		OtherComp->GetBodyInstance()->bLockZTranslation = true;

		OtherComp->BodyInstance.SetDOFLock(EDOFMode::SixDOF);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, BodyInstance->GetBodyDebugName());
	//Define the parameters of the custom plane
	//FVector CustomPlaneNormal = CustomPlane->GetForwardVector(); // Normal vector of the custom plane

	//Set the DOF mode to CustomPlane
	//BodyInstance->DOFMode = EDOFMode::CustomPlane;

	// Set the parameters of the custom plane
	//BodyInstance->CustomDOFPlaneNormal = CustomPlaneNormal;
}

void ACartridgeDock::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT"));

		OtherComp->GetBodyInstance()->bLockXRotation = false;
		OtherComp->GetBodyInstance()->bLockYRotation = false;
		OtherComp->GetBodyInstance()->bLockZRotation = false;

		OtherComp->GetBodyInstance()->bLockXTranslation = false;
		OtherComp->GetBodyInstance()->bLockZTranslation = false;

		OtherComp->BodyInstance.SetDOFLock(EDOFMode::None);
}



