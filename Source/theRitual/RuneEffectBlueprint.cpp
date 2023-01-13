// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneEffectBlueprint.h"


void ARuneEffectBlueprint::BeginPlay()
{
	Super::BeginPlay();
}

void ARuneEffectBlueprint::RecognizeRuneEffect(FString DrawnRuneName) {
	if (RuneName != DrawnRuneName)return;
	if (!Activated)return;
	OnEffectRecognize();
}
void ARuneEffectBlueprint::TriggerRuneEffect(FString DrawnRuneName) {
	if (RuneName != DrawnRuneName)return;
	if (!Activated)return;
	OnEffectTrigger();
}
bool ARuneEffectBlueprint::IsInLineOfSight(AActor* actor, float minAngle) {
	//get line of sight direction vector
	ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
	ACharacterController* castPawn = Cast<ACharacterController>(pawn);
	UCameraComponent* head = castPawn->Head;
	FVector lineOfSight = head->GetForwardVector();

	FQuat betweenQuat;
	FVector axis;
	float angle;

	//get angle to target
	if (actor) {
		FVector directionOfTarget = actor->GetActorLocation() - head->GetComponentLocation();
		betweenQuat = FQuat::FindBetweenVectors(lineOfSight, directionOfTarget);
		betweenQuat.ToAxisAndAngle(axis, angle);

		if (angle > minAngle) return false;
	}
	return true;
}
FVector ARuneEffectBlueprint::GetPlayerPosition() {
	ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
	ACharacterController* castPawn = Cast<ACharacterController>(pawn);
	USceneComponent* base = castPawn->VRTrackingCenter;
	return base->GetComponentLocation();
}