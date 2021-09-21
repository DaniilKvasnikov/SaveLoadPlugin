// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadSubsystem.h"
#include "SaveLoadSettings.h"

FString USaveLoadSubsystem::GetPathToSaveFile()
{
	const USaveLoadSettings* settings = GetDefault<USaveLoadSettings>();
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectConfigDir(), settings->Filename));
}

FString USaveLoadSubsystem::GetString()
{
	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	return OutputString;
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

void USaveLoadSubsystem::UpdateParameter(FString name, FString str)
{
	UpdateJsonObject(name, str);
	SaveJson(GetString());
}

FString USaveLoadSubsystem::LoadJson(const FString& Name, const FString& default, bool& success)
{
	UpdateJsonObject(LoadStringFromFile(success));
	FString outString;
	success = success && JsonObject->TryGetStringField(Name, outString);
	if (!success)
	{
		outString = default;
		UpdateParameter(Name, default);
	}
	return outString;
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
	FFileHelper::SaveStringToFile(JSON, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
	UE_LOG(LogTemp, Warning, TEXT("JSON write %s"), *JSON);
}

