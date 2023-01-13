// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneEffectTeleportLoSConstraint.h"
#include <theRitual/CharacterController.h>
#include "Debug.h"

void ARuneEffectTeleportLoSConstraint::BeginPlay()
{
	Super::BeginPlay();
}

void ARuneEffectTeleportLoSConstraint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Activated)return;

	if (IsInLineOfSight()) {
		if (LookingAt) return; //or tick
		else {
			LookingAt = true;
			//start align
			if (LoSConstraint) {
				AWorldLineOfSightEffect* effect = Cast<AWorldLineOfSightEffect>(LoSConstraint);
				if (effect) {
					effect->EnterAligned();
				}
			}
			if (OtherLoSConstraint) {
				AWorldLineOfSightEffect* effect = Cast<AWorldLineOfSightEffect>(OtherLoSConstraint);
				if (effect) {
					effect->EnterAligned();
				}
			}
		}
	}
	else {
		if (LookingAt) {
			LookingAt = false;
			//end align
			if (LoSConstraint) {
				AWorldLineOfSightEffect* effect = Cast<AWorldLineOfSightEffect>(LoSConstraint);
				if (effect) {
					effect->ExitAligned();
				}
			}
			if (OtherLoSConstraint) {
				AWorldLineOfSightEffect* effect = Cast<AWorldLineOfSightEffect>(OtherLoSConstraint);
				if (effect) {
					effect->ExitAligned();
				}
			}
		}
	}
}

void ARuneEffectTeleportLoSConstraint::Activate() {
	Activated = true;

	if (LoSConstraint) {
		AWorldLineOfSightEffect* effect = Cast<AWorldLineOfSightEffect>(LoSConstraint);
		if (effect)effect->Activated = true;
	}
	if (OtherLoSConstraint) {
		AWorldLineOfSightEffect* effect = Cast<AWorldLineOfSightEffect>(OtherLoSConstraint);
		if (effect)effect->Activated = true;
	}
}

void ARuneEffectTeleportLoSConstraint::RecognizeRuneEffect(FString DrawnRuneName) {
	if (!Activated)return;
	ADebug::Log(DrawnRuneName + FString(" ") + RuneName);

	//check if allowed to teleport
	if (DrawnRuneName != RuneName) return;
	if (!IsInLineOfSight())return;

	OnEffectRecognized();
}
void ARuneEffectTeleportLoSConstraint::TriggerRuneEffect(FString DrawnRuneName) {
	if (!Activated)return;
	ADebug::Log(DrawnRuneName + FString(" ") + RuneName);

	//check if allowed to teleport
	if (DrawnRuneName != RuneName) return;
	if (!IsInLineOfSight())return;

	OnEffectTriggered();
}

void ARuneEffectTeleportLoSConstraint::ExecuteEffect() {
	if (!Activated)return;
	//teleport to target
	ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
	if (!target || !pawn)return;
	FVector destination = target->GetActorLocation();
	//destination.Z = pawn->GetActorLocation().Z; //does not work with different target heights

	//get player height (when game includes teleport to upper floor level)
	ACharacterController* controller = Cast<ACharacterController>(pawn);
	float height = controller->VRTrackingCenter->GetRelativeLocation().Z * -1;
	destination.Z += height;

	if ((pawn->GetActorLocation() - destination).Size() > MaxDistance) return;

	pawn->SetActorLocation(destination);
	pawn->SetActorRotation(target->GetActorRotation());

	OnEffectExecuted();
}

bool ARuneEffectTeleportLoSConstraint::IsInLineOfSight() {

	//get line of sight direction vector
	ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
	ACharacterController* castPawn = Cast<ACharacterController>(pawn);
	UCameraComponent* head = castPawn->Head;
	FVector lineOfSight = head->GetForwardVector();

	FQuat betweenQuat;
	FVector axis;
	float angle;

	//get angle to target rune/ constraint 1
	if (LoSConstraint) {
		FVector directionOfTarget = LoSConstraint->GetActorLocation() - head->GetComponentLocation();
		betweenQuat = FQuat::FindBetweenVectors(lineOfSight, directionOfTarget);
		betweenQuat.ToAxisAndAngle(axis, angle);

		//ADebug::Log(angle);
		if (angle > MinAngle) return false;
	}

	//get angle to amulet/ constraint 2
	if (OtherLoSConstraint) {
		FVector directionOfOtherTarget = OtherLoSConstraint->GetActorLocation() - head->GetComponentLocation();
		betweenQuat = FQuat::FindBetweenVectors(lineOfSight, directionOfOtherTarget);
		betweenQuat.ToAxisAndAngle(axis, angle);

		//ADebug::Log(angle);
		if (angle > MinAngle) return false;
	}

	return true;
}
FVector ARuneEffectTeleportLoSConstraint::GetPlayerPosition() {
	ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
	ACharacterController* castPawn = Cast<ACharacterController>(pawn);
	USceneComponent* base = castPawn->VRTrackingCenter;
	return base->GetComponentLocation();
}