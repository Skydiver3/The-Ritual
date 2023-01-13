// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneEffect.h"
#include "Materials/MaterialInstance.h"
#include "RuneEffectPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class THERITUAL_API ARuneEffectPuzzle : public ARuneEffect
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void TriggerRuneEffect(FString DrawnRuneName) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __puzzle)
		TArray<AActor*> Pieces;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __puzzle)
		float MaxDistance = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __puzzle)
		UStaticMesh* CompleteMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __puzzle)
		FString EnabledRuneName;

	UFUNCTION(BlueprintImplementableEvent, Category = __puzzle)
		void ActivateKiYTrigger();

	bool Triggered = false;
	bool GetAssembled();
	void ActivateRune();
};
