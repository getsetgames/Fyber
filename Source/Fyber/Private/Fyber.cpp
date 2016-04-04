//
//  Created by Robert Segal on 2016-04-04.
//  Copyright (c) 2016 Get Set Games Inc. All rights reserved.
//

#include "FyberPrivatePCH.h"
#include "FyberSettings.h"
#include "ISettingsModule.h"

DEFINE_LOG_CATEGORY(LogFyber);

#define LOCTEXT_NAMESPACE "Fyber"

class FFyber : public IFyber
{
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FFyber, Fyber )

void FFyber::StartupModule()
{
	// register settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Fyber",
										 LOCTEXT("RuntimeSettingsName", "Fyber"),
										 LOCTEXT("RuntimeSettingsDescription", "Configure the Fyber plugin"),
										 GetMutableDefault<UFyberSettings>()
										 );
	}
}


void FFyber::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
