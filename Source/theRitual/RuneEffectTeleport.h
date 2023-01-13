// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneEffect.h"
#include "GameFramework/Actor.h"
#include "RuneEffectTeleport.generated.h"

/**
 * 
 */
UCLASS()
class THERITUAL_API ARuneEffectTeleport : public ARuneEffect
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void TriggerRuneEffect(FString DrawnRuneName) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		FVector targetPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		AActor* target;
};
