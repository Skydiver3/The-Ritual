// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ManagerOfMadness.generated.h"

UCLASS()
class THERITUAL_API AManagerOfMadness : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AManagerOfMadness();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float MadnessValue = 1.0f;
	float MadnessIncrement = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __madness)
	float MadnessDuration = 3.0f;
	void TriggerMadness();
	DECLARE_MULTICAST_DELEGATE_OneParam(Float1Delegate, float);
	Float1Delegate OnTriggerMadnessEffects;
	void StopMadness();
	DECLARE_MULTICAST_DELEGATE(VoidDelegate);
	VoidDelegate OnStopMadnessEffects;

	bool HasRuneBeenTriggered(FString runeName);
};
