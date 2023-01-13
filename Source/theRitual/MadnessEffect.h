// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ManagerOfMadness.h"
#include "MadnessEffect.generated.h"

UCLASS()
class THERITUAL_API AMadnessEffect : public AActor
{
	GENERATED_BODY()
	
private:

	AManagerOfMadness* manager;

public:	
	// Sets default values for this actor's properties
	AMadnessEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ExecuteMadness(float intensity);
	virtual void StopMadness();
	float Intensity = 0.5f;
	float Decrement = 0.2f;
	float Frequency = 3;
};
