// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"

#include "SaveLoadSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FSaveLoadStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		FString Group;
	UPROPERTY(BlueprintReadWrite)
		FString Subgroup;
	UPROPERTY(BlueprintReadWrite)
		FString value;
	UPROPERTY(BlueprintReadWrite)
		FString default;
};

/**
 * 
 */
UCLASS()
class SAVELOADPLUGIN_API USaveLoadSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

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
	FString LoadStringFromFile(bool& success);
	void SaveJson(const FString& JSON);
};
