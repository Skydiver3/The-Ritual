// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor.h"
#include "RuneEffect.h"
#include "RuneEffectFlashlightStatueAlign.generated.h"

/**
 * 
 */
UCLASS()
class THERITUAL_API ARuneEffectFlashlightStatueAlign : public ARuneEffect
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	ARuneEffectFlashlightStatueAlign();
	virtual void TriggerRuneEffect(FString DrawnRuneName) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __align)
		AActor* Statue1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __align)
		AActor* Statue2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __align)
		float MaxDist=50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __align)
		float MaxAngle=0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __align)
		float Duration=7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __align)
		AActor* RuneEffectActor;

	UFUNCTION(BlueprintImplementableEvent, Category = __runeEffect)
		void OnAlignRecognized();

	bool GetAligned();
	bool CheckingForAlign = false;
};
