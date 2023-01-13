// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneEffectFlashlightStatueAlign.h"
#include <theRitual/CharacterController.h>

ARuneEffectFlashlightStatueAlign::ARuneEffectFlashlightStatueAlign()
{
}

void ARuneEffectFlashlightStatueAlign::BeginPlay() {
	Super::BeginPlay();
	Activated = false;
}
void ARuneEffectFlashlightStatueAlign::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	//activate the teleport if aligning during that time
	if (CheckingForAlign) {
		if (GetAligned()) {
			if (RuneEffectActor) {
				ADebug::Log(TEXT("activate teleport"));
				ARuneEffect* runeEffect = Cast<ARuneEffect>(RuneEffectActor);
				if (runeEffect) {
					TimesTriggered++;
					runeEffect->Activate();
				}
			}
			//call blueprint event
			OnAlignRecognized();
		}
	}
}
void ARuneEffectFlashlightStatueAlign::TriggerRuneEffect(FString DrawnRuneName)
{
	if (!Activated)return;
	if (RuneName != DrawnRuneName)return;

	//activate and then deactivate after time
	CheckingForAlign = true;
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, [this]() {
		CheckingForAlign = false;
		}, 1, false, Duration);

}

bool ARuneEffectFlashlightStatueAlign::GetAligned() {
	//get line between statues -> place actors at top
	//that is statuevector
	FVector statueVector = Statue2->GetActorLocation() - Statue1->GetActorLocation();

	//get distance hand-statueVector
	//	get pawn for reference
	ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
	ACharacterController* castPawn = Cast<ACharacterController>(pawn);
	UMotionControllerComponent* r = castPawn->RightController;
	UMotionControllerComponent* l = castPawn->LeftController;

	//	create plane with statueVector normal and r/l as base
	//  calculate distance of statueVector/plane intersection and r/l
	FVector p1 = Statue1->GetActorLocation();
	FVector p2 = Statue2->GetActorLocation();
	FVector base = r->GetComponentLocation();
	FVector n = statueVector;
	FVector closest = FMath::LinePlaneIntersection(p1, p2, base, n);

	float distR = (base - closest).Size();
	base = l->GetComponentLocation();
	closest = FMath::LinePlaneIntersection(p1, p2, base, n);
	float distL = (base - closest).Size();

	//get angle hand-statueVector
	FQuat betweenQuat;
	FVector axis;
	float angleR;
	float angleL;
	FVector handForward = r->GetForwardVector();
	betweenQuat = FQuat::FindBetweenVectors(handForward, statueVector);
	betweenQuat.ToAxisAndAngle(axis, angleR);
	handForward = l->GetForwardVector();
	betweenQuat = FQuat::FindBetweenVectors(handForward, statueVector);
	betweenQuat.ToAxisAndAngle(axis, angleL);

	//are both below maxDistance/maxAngle?
	if (distR < MaxDist && angleR < MaxAngle) return true;
	if (distL < MaxDist && angleL < MaxAngle) return true;

	//if yes, congratulations. if no, sucks to be you i guess
	return false;
}
