// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadSubsystem.h"
#include "SaveLoadSettings.h"

FString USaveLoadSubsystem::LoadJson()
{
	const USaveLoadSettings* settings = GetDefault<USaveLoadSettings>();
	return settings->Filename;
}

