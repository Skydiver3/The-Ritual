// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldLineOfSightEffect.h"
#include <theRitual/CharacterController.h>
#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
#include "Debug.h"

// Sets default values
AWorldLineOfSightEffect::AWorldLineOfSightEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWorldLineOfSightEffect::BeginPlay()
{
	Super::BeginPlay();
	if(!LoSConstraint)LoSConstraint = this;
}

// Called every frame
void AWorldLineOfSightEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Activated)return;

	bool updatedInLoS = CheckIfInLineOfSight();
	if (IsInLineOfSight) {
		if (!updatedInLoS) {
			ExitLineOfSight();
		}
	}
	else {
		if (updatedInLoS) {
			EnterLineOfSight();
		}
	}
	IsInLineOfSight = updatedInLoS;
}


bool AWorldLineOfSightEffect::CheckIfInLineOfSight() {
	if (!Activated)return false;
	if (!LoSConstraint)return false;

	//get line of sight direction vector
	ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
	ACharacterController* castPawn = Cast<ACharacterController>(pawn);
	UCameraComponent* head = castPawn->Head;
	FVector lineOfSight = head->GetForwardVector();

	FQuat betweenQuat;
	FVector axis;
	float angle;

	//get angle to target rune/ constraint 1
	FVector directionOfTarget = LoSConstraint->GetActorLocation() - head->GetComponentLocation();
	betweenQuat = FQuat::FindBetweenVectors(lineOfSight, directionOfTarget);
	betweenQuat.ToAxisAndAngle(axis, angle);

	if (angle > MinAngle) return false;

	return true;
}