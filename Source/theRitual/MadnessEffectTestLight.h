// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MadnessEffect.h"
#include "Components/PointLightComponent.h"
#include "MadnessEffectTestLight.generated.h"

/**
 * 
 */
UCLASS()
class THERITUAL_API AMadnessEffectTestLight : public AMadnessEffect
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void ExecuteMadness(float intensity) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __lightEffect)
		AActor* lightActor;
	UPointLightComponent* light;
	bool deactivateMadness = false;
};
