// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneEffectTransform.h"
#include "EngineUtils.h"
#include <theRitual/Debug.h>

// Sets default values
ARuneEffectTransform::ARuneEffectTransform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARuneEffectTransform::BeginPlay()
{
	Super::BeginPlay();

	FVector offset = FVector(0, 0, 50);
	this->AddActorWorldOffset(offset);

	TArray<ATrailPainterActor*> TrailPainters;
	for (TActorIterator<ATrailPainterActor> It(GetWorld()); It; ++It)
	{
		TrailPainters.Add(*It);
	}
	if (TrailPainters.Num() == 0)return;

	hand = TrailPainters[0];
	hand->OnRuneRecognized.AddUObject(this, &ARuneEffectTransform::TriggerRuneEffect);
}

// Called every frame
void ARuneEffectTransform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARuneEffectTransform::TriggerRuneEffect(FString DrawnRuneName) {
	if (DrawnRuneName != RuneName) return;

	FVector offset = FVector(0, 0, 50);
	this->AddActorWorldOffset(offset);
}