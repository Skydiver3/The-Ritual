// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneEffectFlashlight.h"
#include <theRitual/Debug.h>

ARuneEffectFlashlight::ARuneEffectFlashlight() {
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));

}
void ARuneEffectFlashlight::BeginPlay()
{
	Super::BeginPlay();
	Flashlight->SetIntensity(0);
	Activated = false;
}
void ARuneEffectFlashlight::TriggerRuneEffect(FString DrawnRuneName)
{
	if (RuneName != DrawnRuneName)return;
	if (!Activated)return;

	Flashlight->SetIntensity(Intensity);

	//start dimming after Duration in Seconds
	GetWorld()->GetTimerManager().SetTimer(Handle, [this]() {
		StartDimming();
		},1, false,Duration);
}
void ARuneEffectFlashlight::StartDimming() {
	//set timer to decrement
	GetWorld()->GetTimerManager().SetTimer(Handle, [this]() {
		DecrementFlashlightIntensity(Decrement);
		}, Interval, true, 1);
}
void ARuneEffectFlashlight::DecrementFlashlightIntensity(float decrement) {

	if(Flashlight->Intensity>decrement)	Flashlight->SetIntensity(Flashlight->Intensity - decrement);
	else {
		Flashlight->SetIntensity(0);

		GetWorld()->GetTimerManager().ClearTimer(Handle);
	}
}