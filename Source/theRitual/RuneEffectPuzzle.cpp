// Fill out your copyright notice in the Description page of Project Settings.


#include "RuneEffectPuzzle.h"
#include "EngineUtils.h"
#include "Debug.h"

void ARuneEffectPuzzle::Tick(float DeltaTime)
{
	//if (Activated)return;

	//are all distances below maxDistance?
	if (!GetAssembled())return;

	//activate (reconstruction) rune
	ActivateRune();
}

void ARuneEffectPuzzle::TriggerRuneEffect(FString DrawnRuneName)
{
	if (!Activated)return;
	if (DrawnRuneName != RuneName)return;
	if (Triggered)return;
	if (!GetAssembled())return;
	if (!CompleteMesh)return;
	TimesTriggered++;

	//destroy all pieces except first
	for (int i = Pieces.Num()-1; i > 0; i--) {
		Pieces[i]->Destroy();
	}
	//static mesh of first is now [PlateMesh]
	UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(Pieces[0]->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	mesh->SetStaticMesh(CompleteMesh);


	//make sure plate can only be fixed once
	Destroy();
}

bool ARuneEffectPuzzle::GetAssembled() {

	//for each piece(except first piece)(or including first piece because distance to yourself is always zero)
	//get distance to first piece
	FVector origin = Pieces[0]->GetActorLocation();
	for (AActor* actor : Pieces) {
		float distance = (actor->GetActorLocation() - origin).Size();
		if (distance > MaxDistance) return false;
	}
	//if survived until this point, all pieces are close together. Success.
	return true;
}

void ARuneEffectPuzzle::ActivateRune() {
	TArray<ARuneEffect*> Effects;
	for (TActorIterator<ARuneEffect> It(GetWorld()); It; ++It)
	{
		Effects.Add(*It);
		if (It->RuneName == RuneName) {
			It->Activate();
			ADebug::Log(TEXT("enable rune ") + EnabledRuneName);
			ActivateKiYTrigger();
		}
	}
	Activated = true;
}
