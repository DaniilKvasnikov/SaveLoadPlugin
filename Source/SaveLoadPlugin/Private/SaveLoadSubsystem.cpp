// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadSubsystem.h"
#include "SaveLoadSettings.h"

void USaveLoadSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize save load subsystem"));

	bool success;
	JsonObject = MakeShareable(new FJsonObject);
	UpdateJsonObject(LoadStringFromFile(success));
}

void USaveLoadSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Deinitialize save load subsystem"));
}

FString USaveLoadSubsystem::string_Load(const FString& Name, const FString& default, bool& success)
{
	FString outString;
	success = JsonObject->TryGetStringField(Name, outString);
	if (success)
		return outString;
	UpdateJsonObject(Name, default);
	SaveJson(GetString());
	return default;
	
}

void USaveLoadSubsystem::string_Save(FString name, FString str)
{
	UpdateJsonObject(name, str);
	SaveJson(GetString());
}

FString USaveLoadSubsystem::GetPathToSaveFile()
{
	const USaveLoadSettings* settings = GetDefault<USaveLoadSettings>();
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectConfigDir(), settings->Filename));
}

void USaveLoadSubsystem::UpdateJsonObject(FString JsonString)
{
	TSharedRef< TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(JsonString);
	FJsonSerializer::Deserialize(JsonReader, JsonObject);
}

void USaveLoadSubsystem::UpdateJsonObject(const FString& Name, const FString& Value)
{
	JsonObject->SetStringField(Name, Value);
}

FString USaveLoadSubsystem::GetString()
{
	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	return OutputString;
}

FString USaveLoadSubsystem::LoadStringFromFile(bool& success)
{
	FString FilePath;
	FString JSON;

	FilePath = GetPathToSaveFile();
	success = FPaths::FileExists(FilePath) && FFileHelper::LoadFileToString(JSON, *FilePath);
	return success ? JSON : "";
}

void USaveLoadSubsystem::SaveJson(const FString& JSON)
{
	const FString FilePath = GetPathToSaveFile();
	FFileHelper::SaveStringToFile(JSON, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get());
}

