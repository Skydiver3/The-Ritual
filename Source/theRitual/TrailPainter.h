// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrailPainter.generated.h"

UCLASS()
class THERITUAL_API ATrailPainter : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrailPainter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = __input)
		void OnDrawStart();
	UFUNCTION(BlueprintImplementableEvent, Category = __input)
		void OnDrawStop();
};
