// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Cartridge.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "LeverInteraction.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API ALeverInteraction : public AInteractableObject
{
	GENERATED_BODY()

public: 
	ALeverInteraction();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LeverBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPhysicsConstraintComponent* PhysConstraint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* LowerTrigger;

    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult ) override;

	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex) override;

};
