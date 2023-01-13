// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <iostream>
#include <Runtime/Engine/Classes/Components/TextRenderComponent.h>
#include "Debug.generated.h"

UCLASS()
class THERITUAL_API ADebug : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADebug();
	~ADebug();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	static void LogAdd(FString logText);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static ADebug* Instance;
	int maxLength = 500;

	static void Log(FString logText);
	static void Log(std::string logString);
	static void Log(int logInt);
	static void Log(float logFloat);
	static void Log(double logDouble);
	static void Log(FVector logVector);


	UTextRenderComponent* debugText;
};
