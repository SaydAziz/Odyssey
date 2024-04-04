// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ButtonInteractable.generated.h"

UDELEGATE(BlueprintCallable)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonPressed, int, ButtonID);

UCLASS()
class ODYSSEY_API AButtonInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ButtonID;

private:
	FVector RelativeLoc;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintCallable, BlueprintAssignable)
	FOnButtonPressed ButtonPressed;

    UFUNCTION( )
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
