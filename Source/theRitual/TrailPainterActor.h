// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrailPainterActor.generated.h"

UCLASS()
class THERITUAL_API ATrailPainterActor : public AActor
{
	GENERATED_BODY()

public:
	ATrailPainterActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __drawing)
		FName DrawInput = FName(TEXT("DrawRight"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __drawing)
		UBlueprint* RunePlaneBlueprint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __drawing)
	TSubclassOf<AActor>  ProjectileType;
	
	//spawn drawing plane
	TSubclassOf<AActor> runePlaneClass;

	//register input
	void DrawStart();
	void DrawBreak();
	void DrawStop();

	//broadcast input to rune plane
	DECLARE_MULTICAST_DELEGATE(FDelegate);
	FDelegate OnDrawStart;
	FDelegate OnDrawBreak;
	FDelegate OnDrawStop;

	//broadcast rune success event to rune effect subscribers
	//DECLARE_DELEGATE_OneParam(FStringDelegate, FString);
	DECLARE_MULTICAST_DELEGATE_OneParam(FStringDelegate, FString);
	FStringDelegate OnRuneRecognized;
	FStringDelegate OnRuneTriggered;

	void RecognizeRune(FString RuneName);
	void TriggerRune(FString RuneName);
	void FailRune();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __drawing)
	bool isDrawing = false;

	bool HasRuneBeenActivated(FString runeName);
	float GetImmunized(FString runeName);
};
