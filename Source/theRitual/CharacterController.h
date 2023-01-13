// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "MotionControllerComponent.h"
#include "UObject/ConstructorHelpers.h"
#include <Runtime/HeadMountedDisplay/Public/XRMotionControllerBase.h>
#include "Debug.h"
#include "CharacterController.generated.h"

UCLASS()
class THERITUAL_API ACharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		USceneComponent* VRTrackingCenter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UCameraComponent* Head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UTextRenderComponent* outputText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UMotionControllerComponent* LeftController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UMotionControllerComponent* RightController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __locomotion)
		float deadZone = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __locomotion)
		float snapTurnAngle = 45.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __locomotion)
		float jumpTeleportForwardDistance = 100.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __locomotion)
		float continuousWalkSpeed = 0.1f;

	//locomotion
	FVector velocity;
	void SnapTurnRight();
	void SnapTurnLeft();
	void JumpTeleportForward();
	void ContinuousWalkForward(float AxisValue);
	void ContinuousWalkSide(float AxisValue);
	void TeleportTo(FVector destination);

};
