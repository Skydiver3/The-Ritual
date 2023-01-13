// Fill out your copyright notice in the Description page of Project Settings.


#include "MadnessEffect.h"
#include <theRitual/ManagerOfMadness.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
AMadnessEffect::AMadnessEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMadnessEffect::BeginPlay()
{
	Super::BeginPlay();
	//TODO: put this somewhere else
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AManagerOfMadness::StaticClass(), FoundActors);
	manager = Cast<AManagerOfMadness>(FoundActors[0]);
	manager->OnTriggerMadnessEffects.AddUObject(this, &AMadnessEffect::ExecuteMadness);
	manager->OnStopMadnessEffects.AddUObject(this, &AMadnessEffect::StopMadness);
	
}

// Called every frame
void AMadnessEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMadnessEffect::ExecuteMadness(float intensity) {

}
void AMadnessEffect::StopMadness() {

}

