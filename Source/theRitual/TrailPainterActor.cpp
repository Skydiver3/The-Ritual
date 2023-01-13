// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailPainterActor.h"
#include "RunePlane.h"
#include "MadnessEffect.h"
#include <theRitual/CharacterController.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "EngineUtils.h"
#include <theRitual/RuneEffect.h>

// Sets default values
ATrailPainterActor::ATrailPainterActor()
{
	PrimaryActorTick.bCanEverTick = true;

	//load rune plane blueprint class for spawning it later
	//static ConstructorHelpers::FObjectFinder<UBlueprint> BPClass(TEXT("/Game/TheRitual/Core/RuneDrawing/BP_RunePlane.BP_RunePlane"));
	//runePlaneClass = (UClass*)BPClass.Object->GeneratedClass;
}

void ATrailPainterActor::BeginPlay()
{
	Super::BeginPlay();

	//handle input
	EnableInput(GetWorld()->GetFirstPlayerController());
	UInputComponent* myInputComp = this->InputComponent; 
	myInputComp->BindAction(DrawInput, IE_Pressed, this, &ATrailPainterActor::DrawStart);
	myInputComp->BindAction(DrawInput, IE_Released, this, &ATrailPainterActor::DrawStop);
}

void ATrailPainterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATrailPainterActor::DrawStart() {
	//spawn rune drawing plane
	ADebug::Log(FString(TEXT("start drawing")));
	if (isDrawing) 
	{
		OnDrawStart.Broadcast();
	}
	else {
		isDrawing = true;

		//get pawn for reference
		ACharacter* pawn = GetWorld()->GetFirstPlayerController()->GetCharacter();
		ACharacterController* castPawn = Cast<ACharacterController>(pawn);

		//spawn plane
		AActor* runePlane = GetWorld()->SpawnActor<AActor>(ProjectileType);

		//set plane location
		FVector spawnLocation = castPawn->Head->GetComponentLocation();
		FVector lineOfSight = castPawn->Head->GetForwardVector();
		lineOfSight.Z = 0;
		//spawnLocation += lineOfSight * 5; //spawn at hand
		
		FVector headToHand = this->GetActorLocation() - castPawn->Head->GetComponentLocation();
		FVector handDistance = headToHand.ProjectOnTo(lineOfSight);
		spawnLocation += handDistance; //spawn in front of head

		//runePlane->SetActorLocation(this->GetActorLocation()); //spawn at hand
		runePlane->SetActorLocation(spawnLocation); //spawn in front of head

		//assign painting hand
		ARunePlane* runePlaneCast = Cast<ARunePlane>(runePlane);
		runePlaneCast->SetPaintingHand(this);

		//set plane rotation
		FVector forward = runePlaneCast->GetActorLocation() - castPawn->Head->GetComponentLocation();
		forward.Z = 0;
		runePlaneCast->SetActorRotation(forward.Rotation());
	}
}

//broadcast input to rune plane
void ATrailPainterActor::DrawBreak() {
	OnDrawBreak.Broadcast();
}
void ATrailPainterActor::DrawStop() {
	OnDrawStop.Broadcast();
	//isDrawing = false;
}

//broadcast rune success to effect subscribers
void ATrailPainterActor::RecognizeRune(FString RuneName) {
	//Trigger magic
	ADebug::Log(FString(TEXT("recognize "))+RuneName);
	OnRuneRecognized.Broadcast(RuneName);
}
//broadcast rune success to effect subscribers
void ATrailPainterActor::TriggerRune(FString RuneName) {
	//Trigger magic
	ADebug::Log(FString(TEXT("trigger "))+RuneName);
	OnRuneTriggered.Broadcast(RuneName);

	//Trigger madness
	if (HasRuneBeenActivated(RuneName)) {
		if (!GetImmunized(RuneName)) {  //has rune been called enough times for madness to have lost effect?
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AManagerOfMadness::StaticClass(), FoundActors);
			AManagerOfMadness* manager = Cast<AManagerOfMadness>(FoundActors[0]);
			manager->TriggerMadness();
		}
	}
	isDrawing = false;
}

//clear drawing slot for new rune
void ATrailPainterActor::FailRune() {
	isDrawing = false;
}

bool ATrailPainterActor::HasRuneBeenActivated(FString runeName) {

	TArray<ARuneEffect*> RuneEffects;
	for (TActorIterator<ARuneEffect> It(GetWorld()); It; ++It)
	{
		RuneEffects.Add(*It);
	}
	for (ARuneEffect* effect : RuneEffects) {
		if (effect->RuneName == runeName) {
			if (effect->Activated) {
				return true;
			}
		}
	}
	return false;
}
float ATrailPainterActor::GetImmunized(FString runeName) {
	//find all rune effects
	TArray<ARuneEffect*> RuneEffects;
	for (TActorIterator<ARuneEffect> It(GetWorld()); It; ++It)
	{
		RuneEffects.Add(*It);
	}
	//check all runes
	for (ARuneEffect* effect : RuneEffects) {
		if (effect->RuneName == runeName) {
			//if any rune effect of this name has been called too often:
			//madness no longer happens for any rune effect of this name
			ADebug::Log(runeName);
			ADebug::Log(effect->TimesTriggered);
			effect->TimesTriggered++;
			if (effect->TimesTriggered > effect->MadnessTolerance) {
				return true;
			}
		}
	}
	return false;
}