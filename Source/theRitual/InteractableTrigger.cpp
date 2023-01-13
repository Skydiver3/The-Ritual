// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableTrigger.h"

// Sets default values
AInteractableTrigger::AInteractableTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableTrigger::BeginPlay()
{
	Super::BeginPlay();

	//set collision dynamics for hand collider sub-component
	if (!Collider)return;
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AInteractableTrigger::BeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &AInteractableTrigger::EndOverlap);

	//handle input
	EnableInput(GetWorld()->GetFirstPlayerController());
	UInputComponent* myInputComp = this->InputComponent;
	myInputComp->BindAction(InteractInput, IE_Pressed, this, &AInteractableTrigger::StartInteraction);
	myInputComp->BindAction(InteractInput, IE_Released, this, &AInteractableTrigger::EndInteraction);
}

// Called every frame
void AInteractableTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InteractingActor)TickInteraction();
}

void AInteractableTrigger::StartInteraction() {
	if (!HoveredActor)return;
	InteractingActor = HoveredActor;
	OnInteractionStart();
}
void AInteractableTrigger::TickInteraction() {
	if (!HoveredActor||!InteractingActor)return;
	if(InteractingActor)
	OnInteractionTick();
}
void AInteractableTrigger::EndInteraction() {
	if (!HoveredActor||!InteractingActor)return;
	InteractingActor = nullptr;
	OnInteractionEnd();
}


//bounding box collision events
void AInteractableTrigger::BeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	//set hovering
	if (OtherComp->ComponentTags.Contains(FName(TEXT("Hand")))) {
		HoveredActor = OtherActor;
		OnHoverStart();
	}
}
void AInteractableTrigger::EndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
) {
	//set not hovering
	if (OtherActor == HoveredActor) {
		OnHoverEnd();
		EndInteraction();
		HoveredActor = nullptr;
	}
}
