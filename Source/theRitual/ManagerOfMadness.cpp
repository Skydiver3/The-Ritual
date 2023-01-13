// Fill out your copyright notice in the Description page of Project Settings.


#include "ManagerOfMadness.h"

// Sets default values
AManagerOfMadness::AManagerOfMadness()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AManagerOfMadness::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AManagerOfMadness::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AManagerOfMadness::TriggerMadness() {
	//called from magic effect or drawing plane
	OnTriggerMadnessEffects.Broadcast(MadnessValue);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, [this]() {
		StopMadness();
		}, 1, false, MadnessDuration);
}

void AManagerOfMadness::StopMadness() {
	OnStopMadnessEffects.Broadcast();
}
