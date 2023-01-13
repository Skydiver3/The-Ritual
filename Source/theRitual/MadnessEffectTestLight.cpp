// Fill out your copyright notice in the Description page of Project Settings.


#include "MadnessEffectTestLight.h"

void AMadnessEffectTestLight::BeginPlay() {
    Super::BeginPlay();
    light = Cast<UPointLightComponent>(lightActor->GetComponentByClass(UPointLightComponent::StaticClass()));
}

void AMadnessEffectTestLight::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (deactivateMadness) {
        deactivateMadness = false;
        light->SetIntensity(10);
    }
}

void AMadnessEffectTestLight::ExecuteMadness(float intensity) {
    light->SetIntensity(200);
    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, [this]() {
        deactivateMadness = true;
        }, 5, 1);
}