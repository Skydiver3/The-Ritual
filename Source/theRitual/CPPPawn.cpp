// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPPawn.h"

// Sets default values
ACPPPawn::ACPPPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	VRTrackingCenter = CreateDefaultSubobject<USceneComponent>(TEXT("VRTrackingCenter"));
	Head = CreateDefaultSubobject<UCameraComponent>(TEXT("Head"));
	outputText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("outputText"));

	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
	RightHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHand"));

	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
	LeftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHand"));


	Head->SetupAttachment(VRTrackingCenter);
	outputText->SetupAttachment(Head);
	LeftController->SetupAttachment(VRTrackingCenter);
	LeftHand->SetupAttachment(LeftController);
	RightController->SetupAttachment(VRTrackingCenter);
	RightHand->SetupAttachment(RightController);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> cone(TEXT("/Engine/BasicShapes/Cone"));
	this->RightHand->SetStaticMesh(cone.Object);
	this->LeftHand->SetStaticMesh(cone.Object);

	static ConstructorHelpers::FObjectFinder<UMaterial> graymat(TEXT("/Game/TheRitual/Art/Environment/MasterMaterials/M_OpaqueMaster.M_OpaqueMaster"));
	this->RightHand->SetMaterial(0, graymat.Object);
	this->LeftHand->SetMaterial(0, graymat.Object);


	RightController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	LeftController->MotionSource = FXRMotionControllerBase::LeftHandSourceId;

	this->RootComponent = VRTrackingCenter;

}

// Called when the game starts or when spawned
void ACPPPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPPPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPPPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Right_TurnRight", IE_Pressed, this, &ACPPPawn::SnapTurnRight);
	PlayerInputComponent->BindAction("Right_TurnLeft", IE_Pressed, this, &ACPPPawn::SnapTurnLeft);
	PlayerInputComponent->BindAction("TeleportForward", IE_Pressed, this, &ACPPPawn::JumpTeleportForward);
	PlayerInputComponent->BindAxis("MoveLeft_Y", this, &ACPPPawn::ContinuousWalkForward);
	PlayerInputComponent->BindAxis("MoveLeft_X", this, &ACPPPawn::ContinuousWalkSide);

}


void ACPPPawn::JumpTeleportForward() {
	FVector offset = Head->GetForwardVector() * jumpTeleportForwardDistance;
	offset.Z = 0;
	this->AddActorWorldOffset(offset);
}
void ACPPPawn::SnapTurnRight() {
	this->AddActorWorldRotation(FRotator(0, snapTurnAngle, 0));
}
void ACPPPawn::SnapTurnLeft() {
	this->AddActorWorldRotation(FRotator(0, -snapTurnAngle, 0));
}

void ACPPPawn::ContinuousWalkForward(float AxisValue) {
	if (AxisValue == 0)return;

	FVector offset = Head->GetForwardVector() * continuousWalkSpeed;
	offset.Z = 0;
	offset.Normalize();
	//offset *= AxisValue;
	//this->AddActorWorldOffset(offset);
	if (GetMovementComponent() == NULL) ADebug::Log(FString(TEXT("Is null")));
	AddMovementInput(offset, AxisValue);
}
void ACPPPawn::ContinuousWalkSide(float AxisValue) {
	if (AxisValue == 0)return;

	FVector offset = Head->GetRightVector() * continuousWalkSpeed;
	offset.Z = 0;
	offset.Normalize();
	offset *= AxisValue;
	//this->AddActorWorldOffset(offset);
	//this->AddMovementInput(offset);
}
