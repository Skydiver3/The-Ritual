// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RuneEffect.h"
#include "GameFramework/Actor.h"
#include "WorldLineOfSightEffect.h"
#include "RuneEffectTeleportLoSConstraint.generated.h"

UCLASS()
class THERITUAL_API ARuneEffectTeleportLoSConstraint : public ARuneEffect
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	virtual void RecognizeRuneEffect(FString DrawnRuneName) override;
	virtual void TriggerRuneEffect(FString DrawnRuneName) override;


	UFUNCTION(BlueprintImplementableEvent, Category = __RuneEffect)
		void OnEffectRecognized();
	UFUNCTION(BlueprintImplementableEvent, Category = __RuneEffect)
		void OnEffectTriggered();
	UFUNCTION(BlueprintCallable)
	void ExecuteEffect();
	UFUNCTION(BlueprintImplementableEvent, Category = __RuneEffect)
	void OnEffectExecuted();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		FVector targetPosition;

	//teleport here
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		AActor* target;
	//look at rune
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		AActor* LoSConstraint;
	//look at amulet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		AActor* OtherLoSConstraint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
		float MaxDistance = 500;
	
	//get is player looking at both constraints
	bool IsInLineOfSight();
	//max angle from view vector to rune and amulet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __RuneEffect)
	float MinAngle= 0.3f;
	bool LookingAt = false;

	UFUNCTION(BlueprintCallable)
	FVector GetPlayerPosition();
};
