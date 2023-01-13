// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrailPainterActor.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
//#include "GeometricRecognizer.h"
#include <theRitual/GeometricRecognizer.h>
#include "GeometricRecognizerTypes.h"
#include "RunePlane.generated.h"
using namespace DollarRecognizer;

UCLASS()
class THERITUAL_API ARunePlane : public AActor
{
	GENERATED_BODY()
	
public:	
	ARunePlane();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	//spawn sub-components: projection plane, bounding box, trail painter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		USceneComponent* RunePlaneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UStaticMeshComponent* BoundingBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		UStaticMeshComponent* RunePlane;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = __hide)
		USceneComponent* TrailPainter;

	//bounding box collision events
	UFUNCTION()
	void EndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
		);
	UFUNCTION()
	void BeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);

	//receive input from drawing hand
	void DrawStart();
	void DrawUpdate();
	void DrawBreak();
	void DrawStop();

	//publish drawing events to blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = __input)
		void OnDrawStart();
	UFUNCTION(BlueprintImplementableEvent, Category = __input)
		void OnDrawBreak();
	UFUNCTION(BlueprintImplementableEvent, Category = __input)
		void OnDrawStop();
	UFUNCTION(BlueprintImplementableEvent, Category = __input)
		void OnRuneRecognized(const FString &runeName);

	//drawing
	ATrailPainterActor* paintingHand;
	void SetPaintingHand(ATrailPainterActor* hand);
	UFUNCTION(BlueprintCallable)
	FVector UpdateTrailPosition();
	UFUNCTION(BlueprintCallable)
		void TriggerRune();
	bool drawingActive = false;

	//has rune been triggered yet? Relevant for multistroke runes
	bool runeTriggered = false;

	int GetRuneIndexFromAngle();
	void TriggerRuneByIndex(int index);
	
	//Dollar recognize
	Path2D path;
	GeometricRecognizer recognizer;
	void InitRecognizer();
	void UpdateRuneRecognizer(FVector pos);
	FString Recognize();

	//rune success feedback
	UFUNCTION(BlueprintCallable)
	bool HasRuneBeenTriggered(FString runeName);
};

