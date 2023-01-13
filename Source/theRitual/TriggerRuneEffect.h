// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime/Engine/Classes/Engine/StaticMeshActor.h>
#include "TriggerRuneEffect.generated.h"

UCLASS()
class THERITUAL_API ATriggerRuneEffect : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerRuneEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AStaticMeshActor* actor;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void EnableRune();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = __rune)
		AActor* RuneEffectActor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = __rune)
		FString RuneName;

};
