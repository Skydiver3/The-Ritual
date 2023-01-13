// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneEffectTeleport.h"
#include <theRitual/CharacterController.h>
#include <theRitual/Debug.h>

void ARuneEffectTeleport::BeginPlay()
{
	Super::BeginPlay();
}

void ARuneEffectTeleport::TriggerRuneEffect(FString DrawnRuneName) {
	if (!GetWorld())return;

	if (DrawnRuneName != RuneName) return;

	ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
	if (pawn)pawn->SetActorLocation(this->GetActorLocation());
	if (pawn)pawn->SetActorRotation(this->GetActorRotation());

	TimesTriggered++;
}