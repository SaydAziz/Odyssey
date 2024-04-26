// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Components/BoxComponent.h"
#include "ButtonInteraction.generated.h"

/**
 * 
 */
UCLASS()
class ODYSSEY_API AButtonInteraction : public AInteractableObject
{
	GENERATED_BODY()
	
public: 
	AButtonInteraction();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ButtonPush;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ButtonBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* PressCheck;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ButtonOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* ButtonClick;

private:
	FVector RelativeLoc;

public:	
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
