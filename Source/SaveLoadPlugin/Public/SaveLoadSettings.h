// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveLoadSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class SAVELOADPLUGIN_API USaveLoadSettings : public UObject
{
	GENERATED_BODY()

public:
	USaveLoadSettings(const FObjectInitializer& ObjectInitializer);

	/** Sample bool property */
	UPROPERTY(EditAnywhere, config, Category = Custom)
		FString Filename = TEXT("FileSettings.json");
};
