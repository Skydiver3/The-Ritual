// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime/Engine/Classes/Components/TextRenderComponent.h>
#include "GrabInteractor.generated.h"

UCLASS()
class THERITUAL_API AGrabInteractor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGrabInteractor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __grabInteraction)
		FName GrabAction = FName("GrabRight");

	UTextRenderComponent* debugText;

	UStaticMeshComponent* Hand;

	AActor* hoveredActor;
	AActor* grabbedActor;
	void StartGrab();
	void ReleaseGrab();

	UFUNCTION()
		void BeginOverlap(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
	UFUNCTION()
		void EndOverlap(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);
};
