#include "RestPluginModule.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "RestPlugin"

class FRestPluginModule : public IRestPluginModule
{
	// Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FRestPluginModule, IRestPluginModule)

void FRestPluginModule::StartupModule()
{
}

void FRestPluginModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
