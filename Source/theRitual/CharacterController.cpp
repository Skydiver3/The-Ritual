// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	VRTrackingCenter = CreateDefaultSubobject<USceneComponent>(TEXT("VRTrackingCenter"));
	Head = CreateDefaultSubobject<UCameraComponent>(TEXT("Head"));
	outputText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("outputText"));

	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));

	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));

	VRTrackingCenter->SetupAttachment(GetCapsuleComponent());
	Head->SetupAttachment(VRTrackingCenter);
	outputText->SetupAttachment(Head);
	LeftController->SetupAttachment(VRTrackingCenter);
	RightController->SetupAttachment(VRTrackingCenter);

	RightController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	LeftController->MotionSource = FXRMotionControllerBase::LeftHandSourceId;

	this->RootComponent = this->GetCapsuleComponent();
	//this->RootComponent = VRTrackingCenter;

}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (velocity.Size() <= deadZone)return;

	velocity.Normalize();

	FVector forward = Head->GetForwardVector();
	forward.Z = 0;
	forward.Normalize();
	FVector side = Head->GetRightVector();
	side.Z = 0;
	side.Normalize();

	this->AddMovementInput(side *velocity.X, continuousWalkSpeed);
	this->AddMovementInput(forward*velocity.Y, continuousWalkSpeed);
	
	velocity = FVector::ZeroVector;
}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Right_TurnRight", IE_Pressed, this, &ACharacterController::SnapTurnRight);
	PlayerInputComponent->BindAction("Right_TurnLeft", IE_Pressed, this, &ACharacterController::SnapTurnLeft);
	PlayerInputComponent->BindAction("TeleportForward", IE_Pressed, this, &ACharacterController::JumpTeleportForward);
	PlayerInputComponent->BindAxis("MoveLeft_Y", this, &ACharacterController::ContinuousWalkForward);
	PlayerInputComponent->BindAxis("MoveLeft_X", this, &ACharacterController::ContinuousWalkSide);

}


void ACharacterController::JumpTeleportForward() {
	/*FVector offset = Head->GetForwardVector() * jumpTeleportForwardDistance;
	offset.Z = 0;
	this->AddActorWorldOffset(offset);*/
}
void ACharacterController::SnapTurnRight() {
	
}
void ACharacterController::SnapTurnLeft() {
	
}

void ACharacterController::ContinuousWalkForward(float AxisValue) {
	//if (AxisValue <= deadZone)velocity.Y = 0;
	velocity.Y = AxisValue;
}
void ACharacterController::ContinuousWalkSide(float AxisValue) {
	//if (AxisValue <= deadZone)velocity.X = 0;
	velocity.X = AxisValue;
}

