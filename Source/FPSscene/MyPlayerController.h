// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSSCENE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void SetupInputComponent() override;

	void PrintMap();

	
};

USTRUCT()
struct FBlock
{
	GENERATED_BODY()

		UPROPERTY()
		FString name;

	UPROPERTY()
		FVector pos;

	UPROPERTY()
		FVector scale;

	UPROPERTY()
		FVector extent;

	UPROPERTY()
		FQuat rotation;
};

USTRUCT()
struct FStage
{
	GENERATED_BODY()

		UPROPERTY()
		FString name;

	UPROPERTY()
		TArray<FBlock> actors;

};