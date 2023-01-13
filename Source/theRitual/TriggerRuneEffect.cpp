// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerRuneEffect.h"
#include <theRitual/RuneEffect.h>
#include "EngineUtils.h"
#include "RuneEffect.h"
#include "RuneEffectFlashlight.h"
#include <theRitual/Debug.h>

// Sets default values
ATriggerRuneEffect::ATriggerRuneEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATriggerRuneEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerRuneEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerRuneEffect::EnableRune() {
	if (RuneEffectActor) {
		ADebug::Log(TEXT("enable rune"));
		ARuneEffect* runeEffect = Cast<ARuneEffect>(RuneEffectActor);
		if (runeEffect) {
			runeEffect->Activate();
		}
	}
	else {
		TArray<ARuneEffect*> Effects;
		for (TActorIterator<ARuneEffect> It(GetWorld()); It; ++It)
		{
			Effects.Add(*It);
			if (It->RuneName == RuneName) {
				It->Activate();
				ADebug::Log(TEXT("enable rune ") + RuneName);
			}
		}
	}
}
