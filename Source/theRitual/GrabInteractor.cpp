// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabInteractor.h"
#include "Components/PrimitiveComponent.h"
#include <theRitual/Debug.h>

// Sets default values
AGrabInteractor::AGrabInteractor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrabInteractor::BeginPlay()
{
	Super::BeginPlay();
	//UActorComponent* HandActor = GetComponentByClass(TSubclassOf<UStaticMeshComponent>());
	//Hand = Cast<UStaticMeshComponent>(HandActor);

	TArray<UTextRenderComponent*> texts;
	this->GetComponents<UTextRenderComponent>(OUT texts, true);
	debugText = texts[0];
	debugText->SetText(FString("begin play start"));

	TArray<UStaticMeshComponent*> Meshes;
	this->GetComponents<UStaticMeshComponent>(OUT Meshes, true);
	Hand = Meshes[0];

	//set collision dynamics for hand collider sub-component
	Hand->OnComponentBeginOverlap.AddDynamic(this, &AGrabInteractor::BeginOverlap);
	//Hand->OnComponentHit.Add(this, &AGrabInteractor::BeginOverlap);
	Hand->OnComponentEndOverlap.AddDynamic(this, &AGrabInteractor::EndOverlap);


	//handle input
	EnableInput(GetWorld()->GetFirstPlayerController());
	UInputComponent* myInputComp = this->InputComponent;
	myInputComp->BindAction(GrabAction, IE_Pressed, this, &AGrabInteractor::StartGrab);
	myInputComp->BindAction(GrabAction, IE_Released, this, &AGrabInteractor::ReleaseGrab);

	debugText->SetText(FString("begin play done"));
}

// Called every frame
void AGrabInteractor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrabInteractor::StartGrab() {
	if (!hoveredActor)return;
	ADebug::Log(FString("begin grab" ));

	/*TArray<UPrimitiveComponent*> ActorComponents;
	grabbedActor->GetComponents<UPrimitiveComponent>(OUT ActorComponents, false);
	for (UPrimitiveComponent* comp : ActorComponents) {
		comp->SetSimulatePhysics(false);
	}*/

	grabbedActor = hoveredActor;
	grabbedActor->AttachToComponent(Hand, FAttachmentTransformRules::KeepWorldTransform);
	//grabbedActor->AttachToComponent(Hand, FAttachmentTransformRules::KeepRelativeTransform);
	
}
void AGrabInteractor::ReleaseGrab() {
	debugText->SetText(FString("end grab"));
	if (!grabbedActor)return;
	grabbedActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	TArray<UPrimitiveComponent*> ActorComponents;
	grabbedActor->GetComponents<UPrimitiveComponent>(OUT ActorComponents, false);
	for (UPrimitiveComponent* comp : ActorComponents) {
		comp->SetSimulatePhysics(true);
	}

	grabbedActor = nullptr;
}

//bounding box collision events
void AGrabInteractor::BeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	ADebug::Log(FString("begin overlap"+OtherActor->GetName()));
	if (!(OtherComp->ComponentTags.Contains(FName(TEXT("Interactable"))))) return;
	ADebug::Log(FString("can interact with"+OtherActor->GetName()));
	hoveredActor = OtherActor;
}
void AGrabInteractor::EndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
) {
	debugText->SetText(FString("end overlap"));
	if (OtherActor == hoveredActor)hoveredActor = nullptr;
}