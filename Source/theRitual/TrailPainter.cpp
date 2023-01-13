// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailPainter.h"
#include <theRitual/Debug.h>
#include <iostream>



// Sets default values
ATrailPainter::ATrailPainter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrailPainter::BeginPlay()
{
    Super::BeginPlay();

    ADebug::Log(TEXT("interpret stuff"));



}

// Called every frame
void ATrailPainter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATrailPainter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Draw", IE_Pressed, this, &ATrailPainter::OnDrawStart);
	PlayerInputComponent->BindAction("Draw", IE_Released, this, &ATrailPainter::OnDrawStop);
}

