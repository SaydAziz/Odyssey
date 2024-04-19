// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "CartridgeDock.h"
#include "CartridgeInteraction.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API ACartridgeInteraction : public AInteractableObject
{
	GENERATED_BODY()
	
public:
	ACartridgeInteraction();

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBoxComponent*> SlotTriggerCollection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UBoxComponent*, bool> SlotTriggerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Casing; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* SlotTrigger; 

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
