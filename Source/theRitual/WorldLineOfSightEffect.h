// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldLineOfSightEffect.generated.h"

UCLASS()
class THERITUAL_API AWorldLineOfSightEffect : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWorldLineOfSightEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool CheckIfInLineOfSight();
	bool IsInLineOfSight = false;
	bool Activated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		AActor* LoSConstraint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		float MinAngle = 30.f;
	UFUNCTION(BlueprintImplementableEvent, Category = __RuneEffect)
		void EnterLineOfSight();
	UFUNCTION(BlueprintImplementableEvent, Category = __RuneEffect)
		void ExitLineOfSight();
	UFUNCTION(BlueprintImplementableEvent, Category = __RuneEffect)
		void EnterAligned();
	UFUNCTION(BlueprintImplementableEvent, Category = __RuneEffect)
		void ExitAligned();
};