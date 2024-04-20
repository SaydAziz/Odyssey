// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cartridge.h"
#include "Components/BoxComponent.h"
#include "CartridgeDock.generated.h"

UCLASS()
class ODYSSEY_API ACartridgeDock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACartridgeDock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RailPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* RailTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LockX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LockY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LockZ;

    UFUNCTION()
    void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
                      AActor* OtherActor, 
                      UPrimitiveComponent* OtherComp, 
                      int32 OtherBodyIndex, 
                      bool bFromSweep, 
                      const FHitResult &SweepResult );

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
};
