// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MadnessEffect.h"
#include "MadnessEffectBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class THERITUAL_API AMadnessEffectBlueprint : public AMadnessEffect
{
	GENERATED_BODY()
public:
	virtual void ExecuteMadness(float intensity) override;
	UFUNCTION(BlueprintImplementableEvent, Category = __input)
		void OnMadnessStart();
	virtual void StopMadness() override;
	UFUNCTION(BlueprintImplementableEvent, Category = __input)
		void OnMadnessStop();
	UFUNCTION(BlueprintCallable)
		bool IsInLineOfSight(AActor* actor, float minAngle);

};
