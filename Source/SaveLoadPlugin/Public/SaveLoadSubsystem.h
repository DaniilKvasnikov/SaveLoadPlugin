// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "SaveLoadSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SAVELOADPLUGIN_API USaveLoadSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FString LoadJson();
};
