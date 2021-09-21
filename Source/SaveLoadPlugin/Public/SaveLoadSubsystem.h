// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"

#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"

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
	FString string_Load(const FString& Name, const FString& default, bool& success);
	UFUNCTION(BlueprintCallable)
	void string_Save(FString name, FString str);

private:
	TSharedPtr<FJsonObject> JsonObject;

	FString GetPathToSaveFile();
	void UpdateJsonObject(FString JsonString);
	void UpdateJsonObject(const FString& Name, const FString& Value);
	FString GetString();
	void UpdateParameter(FString name, FString str);
	FString LoadStringFromFile(bool& success);
	void SaveJson(const FString& JSON);
};
