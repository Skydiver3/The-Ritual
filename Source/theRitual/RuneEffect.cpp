// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneEffect.h"
#include "EngineUtils.h"
#include <theRitual/Debug.h>

// Sets default values
ARuneEffect::ARuneEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARuneEffect::BeginPlay() 
{
	Super::BeginPlay();
	//delay registration to make sure everything is set up by then
	FTimerHandle    handle;
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {Register();}, 1,false, 1);

}
void ARuneEffect::Register() {
	//find trail painters
	TArray<ATrailPainterActor*> TrailPainters;
	for (TActorIterator<ATrailPainterActor> It(GetWorld()); It; ++It)
	{
		TrailPainters.Add(*It);
	}

	//register first hand
	if (TrailPainters.Num() < 1)return;
	hand = TrailPainters[0];
	hand->OnRuneTriggered.AddUObject(this, &ARuneEffect::TriggerRuneEffect);
	hand->OnRuneRecognized.AddUObject(this, &ARuneEffect::RecognizeRuneEffect);

	//register second hand
	if (TrailPainters.Num() < 2)return;
	hand = TrailPainters[1];
	hand->OnRuneTriggered.AddUObject(this, &ARuneEffect::TriggerRuneEffect);
	hand->OnRuneRecognized.AddUObject(this, &ARuneEffect::RecognizeRuneEffect);

	ADebug::Log(FString(TEXT("registring effect")));
}

// Called every frame
void ARuneEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARuneEffect::TriggerRuneEffect(FString DrawnRuneName) {

}
void ARuneEffect::RecognizeRuneEffect(FString DrawnRuneName) {

}

void ARuneEffect::Activate(){
	Activated = true;
}