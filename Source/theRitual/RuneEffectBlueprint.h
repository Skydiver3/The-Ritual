// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneEffect.h"
#include <theRitual/CharacterController.h>
#include "RuneEffectBlueprint.generated.h"

/**
 * 
 */
UCLASS()
class THERITUAL_API ARuneEffectBlueprint : public ARuneEffect
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void RecognizeRuneEffect(FString DrawnRuneName) override; 
	virtual void TriggerRuneEffect(FString DrawnRuneName) override; 
	UFUNCTION(BlueprintImplementableEvent, Category = __runeEffect)
	void OnEffectRecognize();
	UFUNCTION(BlueprintImplementableEvent, Category = __runeEffect)
	void OnEffectTrigger();
	UFUNCTION(BlueprintCallable)
		bool IsInLineOfSight(AActor* actor, float minAngle);
	UFUNCTION(BlueprintCallable)
		FVector GetPlayerPosition();
};
