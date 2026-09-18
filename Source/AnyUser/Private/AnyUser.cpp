#include "AnyUser.h"

#define LOCTEXT_NAMESPACE "FAnyUserModule"

void FAnyUserModule::StartupModule()
{
	UE_LOG(LogTemp, Log, TEXT("[AnyUser] AnyUser Accessibility Standard Plugin Initialized."));
}

void FAnyUserModule::ShutdownModule()
{
	UE_LOG(LogTemp, Log, TEXT("[AnyUser] AnyUser Accessibility Standard Plugin Shutdown."));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAnyUserModule, AnyUser)
