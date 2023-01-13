// Fill out your copyright notice in the Description page of Project Settings.


#include "MadnessEffectBlueprint.h"
#include "GameFramework/Actor.h"
#include <theRitual/CharacterController.h>


void AMadnessEffectBlueprint::ExecuteMadness(float intensity) {
    
    OnMadnessStart();
}
void AMadnessEffectBlueprint::StopMadness() {
    
    OnMadnessStop();
}
bool AMadnessEffectBlueprint::IsInLineOfSight(AActor* actor, float minAngle) {
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