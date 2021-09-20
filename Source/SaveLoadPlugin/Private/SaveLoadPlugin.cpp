// Copyright Epic Games, Inc. All Rights Reserved.

#include "SaveLoadPlugin.h"

#include "SaveLoadSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"

#define LOCTEXT_NAMESPACE "FSaveLoadPluginModule"

void FSaveLoadPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	RegisterSettings();
}

void FSaveLoadPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (UObjectInitialized())
	{
		UnregisterSettings();
	}
}

bool FSaveLoadPluginModule::SupportsDynamicReloading()
{
	return true;
}

// Callback for when the settings were saved.
bool FSaveLoadPluginModule::HandleSettingsSaved()
{
	USaveLoadSettings* Settings = GetMutableDefault<USaveLoadSettings>();
	bool ResaveSettings = false;

	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if (ResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

void FSaveLoadPluginModule::RegisterSettings()
{
	// Registering some settings is just a matter of exposing the default UObject of
	// your desired class, feel free to add here all those settings you want to expose
	// to your LDs or artists.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		// Create the new category
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

		//SettingsContainer->DescribeCategory("CustomSettings",
		//	LOCTEXT("RuntimeWDCategoryName", "CustomSettings"),
		//	LOCTEXT("RuntimeWDCategoryDescription", "Game configuration for the CustomSettings game module"));

		// Register the settings
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "SaveLoadSetting",
			LOCTEXT("RuntimeGeneralSettingsName", "SaveLoadSetting"),
			LOCTEXT("RuntimeGeneralSettingsDescription", "Configuration for Save Load plugin"),
			GetMutableDefault<USaveLoadSettings>()
		);

		// Register the save handler to your settings, you might want to use it to
		// validate those or just act to settings changes.
		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw(this, &FSaveLoadPluginModule::HandleSettingsSaved);
		}
	}
}

void FSaveLoadPluginModule::UnregisterSettings()
{
	// Ensure to unregister all of your registered settings here, hot-reload would
	// otherwise yield unexpected results.

	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "CustomSettings", "General");
	}
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSaveLoadPluginModule, SaveLoadPlugin)