// Fill out your copyright notice in the Description page of Project Settings.


#include "Debug.h"

// Sets default values
ADebug::ADebug()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
ADebug::~ADebug()
{
	if (ADebug::Instance && ADebug::Instance == this) {
		ADebug::Instance = nullptr;
	}
}

ADebug* ADebug::Instance;
// Called when the game starts or when spawned
void ADebug::BeginPlay()
{
	Super::BeginPlay();
	if (!ADebug::Instance) {
		TArray<UTextRenderComponent*> texts;
		this->GetComponents<UTextRenderComponent>(OUT texts, true);
		if (texts.Num() > 0)debugText = texts[0];

		ADebug::Instance = this;
	}
	else this->Destroy();
	
}
void ADebug::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	if (ADebug::Instance && ADebug::Instance == this) {
		ADebug::Instance = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ADebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADebug::Log(FString logText) {
	if (!ADebug::Instance)return;
	if (ADebug::Instance->debugText)	ADebug::LogAdd(logText);
}
void ADebug::Log(std::string logString) {
	if (!ADebug::Instance)return;
	if (ADebug::Instance->debugText)	ADebug::LogAdd(logString.c_str());
}
void ADebug::Log(int logInt) {
	if (!ADebug::Instance)return;
	if (ADebug::Instance->debugText)	ADebug::LogAdd(FString::FromInt(logInt));
}
void ADebug::Log(float logFloat) {
	if (!ADebug::Instance)return;
	if (ADebug::Instance->debugText)	ADebug::LogAdd(FString::SanitizeFloat(logFloat));
}
void ADebug::Log(double logDouble) {
	if (!ADebug::Instance)return;
	if (ADebug::Instance->debugText)	ADebug::LogAdd(FString::SanitizeFloat(logDouble));
}
void ADebug::Log(FVector logVector) {
	if (!ADebug::Instance)return;
	if (ADebug::Instance->debugText) {
		FString output = FString("(");
		output += FString::SanitizeFloat(logVector.X) + FString(", ");
		output += FString::SanitizeFloat(logVector.Y) + FString(", ");
		output += FString::SanitizeFloat(logVector.Z) + FString(")");
		ADebug::LogAdd(output);
	}
}

void ADebug::LogAdd(FString logText) {
	FText text = ADebug::Instance->debugText->Text;
	
	FString string = text.ToString();
	while (string.Len() > Instance->maxLength && string.Contains("\n")) {
		int firstLineBreak = string.Find("\n");
		string.RemoveFromStart(string.LeftChop(firstLineBreak));
	}
	
	FString add = FString("\n [") + FString::FromInt(string.Len()) + FString("] ") + logText;
	text = FText::FromString(string+add);

	ADebug::Instance->debugText->SetText(text);
}

