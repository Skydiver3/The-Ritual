// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneEffect.h"
#include "Components/SpotLightComponent.h"
#include "RuneEffectFlashlight.generated.h"

/**
 * 
 */
UCLASS()
class THERITUAL_API ARuneEffectFlashlight : public ARuneEffect
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	ARuneEffectFlashlight();
	virtual void TriggerRuneEffect(FString DrawnRuneName) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __flashlight)
	USpotLightComponent* Flashlight;

	void StartDimming();
	void DecrementFlashlightIntensity(float decrement);
	FTimerHandle Handle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __flashlight)
		float Intensity = 5000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __flashlight)
		float Interval = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __flashlight)
		float Decrement = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __flashlight)
		float Duration = 5;
};
