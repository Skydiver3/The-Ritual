// Fill out your copyright notice in the Description page of Project Settings.


#include "RunePlane.h"
#include "Debug.h"
#include "EngineUtils.h"
#include <theRitual/RuneEffect.h>
#include "Math/Vector.h"

// Sets default values
ARunePlane::ARunePlane()
{
	ADebug::Log(FString(TEXT("spawn plane")));
	PrimaryActorTick.bCanEverTick = true;

	//initialize sub-components
	RunePlaneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	TrailPainter = CreateDefaultSubobject<USceneComponent>(TEXT("TrailPainter"));

	BoundingBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoundingBox"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> cube(TEXT("/Engine/BasicShapes/Cube"));
	this->BoundingBox->SetStaticMesh(cube.Object);
	this->BoundingBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	RunePlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RunePlane"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> plane(TEXT("/Engine/BasicShapes/Plane"));
	this->RunePlane->SetStaticMesh(plane.Object);
	this->RunePlane->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	this->RunePlane->SetWorldLocation(this->BoundingBox->GetComponentLocation());

	RunePlane->SetupAttachment(RunePlaneRoot);
	BoundingBox->SetupAttachment(RunePlaneRoot);
	TrailPainter->SetupAttachment(RunePlaneRoot);
}

void ARunePlane::BeginPlay()
{
	Super::BeginPlay();
	//start drawing effect on spawned
	InitRecognizer();
	DrawStart();

	//set collision dynamics for bounding box sub-component
	BoundingBox->OnComponentBeginOverlap.AddDynamic(this, &ARunePlane::BeginOverlap);
	BoundingBox->OnComponentEndOverlap.AddDynamic(this, &ARunePlane::EndOverlap);

}

void ARunePlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ADebug::Log(FString(TEXT("tick")));
	if (drawingActive&&!runeTriggered) {
		DrawUpdate();
	}
}

//bounding box collision events
void ARunePlane::BeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {

}
void ARunePlane::EndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
) {
	if (runeTriggered)return;
	paintingHand->FailRune();
	this->Destroy();
}

//bind drawing events to input functions of painting hand
void ARunePlane::SetPaintingHand(ATrailPainterActor* hand) {
	paintingHand = hand;
	paintingHand->OnDrawStart.AddUObject(this, &ARunePlane::DrawStart);
	paintingHand->OnDrawBreak.AddUObject(this, &ARunePlane::DrawBreak);
	paintingHand->OnDrawStop.AddUObject(this, &ARunePlane::DrawStop);
}

//drawing events called from painting hand
void ARunePlane::DrawStart() {
	if (runeTriggered) return;
	drawingActive = true;
	UpdateTrailPosition();
	OnDrawStart();
}
void ARunePlane::DrawUpdate() {
	FVector pos = UpdateTrailPosition();
	GetRuneIndexFromAngle();

	UpdateRuneRecognizer(pos);
}
void ARunePlane::DrawBreak() {
	if (runeTriggered)return;
	drawingActive = false;
	OnDrawBreak();
}
void ARunePlane::DrawStop() {
	if (runeTriggered)return;
	drawingActive = false;
	runeTriggered = true;
	OnDrawStop();

	//blueprint event for rune feedback
	FString recognizedRune = Recognize();
	paintingHand->RecognizeRune(recognizedRune);
	OnRuneRecognized(recognizedRune);
}
//called 
void ARunePlane::TriggerRune() {
	FString recognizedRune = Recognize();
	//if (!HasRuneBeenTriggered(recognizedRune))return;
	paintingHand->TriggerRune(recognizedRune);
}
//drawing
FVector ARunePlane::UpdateTrailPosition() {
	if (!paintingHand)return FVector::ZeroVector;

	//get hand position
	FVector handPosition = paintingHand->GetActorLocation();

	//get plane
	FVector planeNormal = RunePlane->GetUpVector();
	FVector planePoint = RunePlane->GetComponentLocation();
	FPlane plane = FPlane(planePoint, planeNormal);

	//get closest point on plane to hand position
	FVector pointOnPlane = FVector::PointPlaneProject(handPosition, plane);

	//move trail painter object to that point
	TrailPainter->SetWorldLocation(pointOnPlane);

	//return painter position relative to plane world position
	//z coordinate should be staying the same
	//project point to RunePlane.Right Vector and get the length
	FVector localPos = pointOnPlane - planePoint;
	float y = localPos.Z;
	FVector rCoordinate = localPos.ProjectOnTo(RunePlane->GetRightVector());
	float x = rCoordinate.Size();
	if ((RunePlane->GetRightVector() - rCoordinate).Size() > (-RunePlane->GetRightVector() - rCoordinate).Size()) x *= -1;

	FVector rotatedCoordinates = FVector(x, y, 0);

	rotatedCoordinates *= 10;

	return rotatedCoordinates;
}

int ARunePlane::GetRuneIndexFromAngle() {
	//get vector from plane center to current trail position
	FVector pointer = TrailPainter->GetComponentLocation() - RunePlane->GetComponentLocation();
	//get angle to up axis
	FQuat betweenQuat = FQuat::FindBetweenVectors(pointer, FVector::UpVector);
	FVector axis;
	float angle;
	betweenQuat.ToAxisAndAngle(axis, angle);

	//get closest to (0,45,90, 135, 180, -135, -90, -45°)
	const int length = 5;
	float range = PI;
	float j = range/length;
	float start = 0;
	float nums[length];
	for (size_t i = 0; i < length; i++)	{nums[i] = start + i * j;}
	float difs[length];
	float smallest = 10000;
	float smallestIndex = 0;
	for (int i = 0; i < length; i++)
	{
		difs[i] = angle - nums[i];
		if (difs[i] < 0)difs[i] *= -1;
		if (difs[i] < smallest) {
			smallest = difs[i];
			smallestIndex = i;
		}
	}

	return smallestIndex;
}

void ARunePlane::TriggerRuneByIndex(int index) {
	//Convert index to string and trigger rune with that
	FString runeName = FString("Rune ") + FString::FromInt(index);
	paintingHand->TriggerRune(runeName);

}

void ARunePlane::InitRecognizer() {
	recognizer.loadTemplates();
	path.clear();
}
void ARunePlane::UpdateRuneRecognizer(FVector pos) {
	Point2D point = Point2D(pos.X, pos.Y);
	path.push_back(point);
}
FString ARunePlane::Recognize() {
	RecognitionResult result = recognizer.recognize(path);
	ADebug::Log(result.name);
	return result.name.c_str();
}

bool ARunePlane::HasRuneBeenTriggered(FString runeName) {

	TArray<ARuneEffect*> RuneEffects;
	for (TActorIterator<ARuneEffect> It(GetWorld()); It; ++It)
	{
		RuneEffects.Add(*It);
	}
	for (ARuneEffect* effect : RuneEffects) {
		if (effect->RuneName==runeName) {
			if (effect->Activated) {
				return true;
			}
		}
	}
	return false;
}