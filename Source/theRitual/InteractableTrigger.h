// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableTrigger.generated.h"

UCLASS()
class THERITUAL_API AInteractableTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __interaction)
	UStaticMeshComponent* Collider;
	AActor* HoveredActor;
	AActor* InteractingActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __interaction)
	FName InteractInput = "Grab";

	void StartInteraction();
	void TickInteraction();
	void EndInteraction();

	UFUNCTION(BlueprintImplementableEvent, Category = __interaction)
		void OnHoverStart();
	UFUNCTION(BlueprintImplementableEvent, Category = __interaction)
		void OnHoverEnd();
	UFUNCTION(BlueprintImplementableEvent, Category = __interaction)
		void OnInteractionStart();
	UFUNCTION(BlueprintImplementableEvent, Category = __interaction)
		void OnInteractionTick();
	UFUNCTION(BlueprintImplementableEvent, Category = __interaction)
		void OnInteractionEnd();

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
