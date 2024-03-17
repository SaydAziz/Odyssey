// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ButtonInteractable.generated.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ButtonOffset;

private:
	FVector RelativeLoc;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
