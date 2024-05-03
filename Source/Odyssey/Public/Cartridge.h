// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cartridge.generated.h"


UCLASS()
class ODYSSEY_API ACartridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACartridge();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInserted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInPlace;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInsertedNotify();
	
	void OnInserted(bool InsertState);
};
