// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrailPainterActor.h"
#include "RuneEffectTransform.generated.h"

UCLASS()
class THERITUAL_API ARuneEffectTransform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARuneEffectTransform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = __rune)
	ATrailPainterActor* hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __rune)
	FString RuneName = FString(TEXT("DefaultRuneName"));

	void TriggerRuneEffect(FString DrawnRuneName);

};
