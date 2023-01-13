// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrailPainterActor.h"
#include "RuneEffect.generated.h"

UCLASS()
class THERITUAL_API ARuneEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARuneEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Register();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __rune)
		ATrailPainterActor* hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __rune)
		FString RuneName = FString(TEXT("DefaultRuneName"));

	virtual void TriggerRuneEffect(FString DrawnRuneName);
	virtual void RecognizeRuneEffect(FString DrawnRuneName);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __rune)
	bool Activated = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __rune)
	float TimesTriggered = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __rune)
	float MadnessTolerance = 1;
	virtual void Activate();
};
