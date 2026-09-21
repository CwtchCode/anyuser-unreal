#include "AnyUserSubsystem.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"
#include "Engine/UserInterfaceSettings.h"

void UAnyUserSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Initialize with canonical Draft-07 baseline
	CurrentProfile = FAnyUserProfile();

	AutoDiscoverProfile();
}

void UAnyUserSubsystem::AutoDiscoverProfile()
{
	TArray<FString> CandidatePaths = {
		// 1. Standard Global OS Documents Path: Documents/AnyUser/profile.anyuser
		FPaths::Combine(FPlatformProcess::UserDir(), TEXT("AnyUser"), TEXT("profile.anyuser")),
		FPaths::Combine(FPlatformProcess::UserDir(), TEXT("Documents"), TEXT("AnyUser"), TEXT("profile.anyuser")),
		// 2. Project local and saved paths
		FPaths::ProjectSavedDir() / TEXT("profile.anyuser"),
		FPaths::ProjectContentDir() / TEXT("profile.anyuser"),
		FPaths::ProjectDir() / TEXT("profile.anyuser"),
		FPaths::ProjectContentDir() / TEXT("AnyUser") / TEXT("profile.anyuser")
	};

	// Also check environment variables for Windows (%USERPROFILE%) and Linux/macOS ($HOME)
	const FString UserProfileEnv = FPlatformMisc::GetEnvironmentVariable(TEXT("USERPROFILE"));
	if (!UserProfileEnv.IsEmpty())
	{
		CandidatePaths.Add(UserProfileEnv / TEXT("Documents") / TEXT("AnyUser") / TEXT("profile.anyuser"));
	}
	const FString HomeEnv = FPlatformMisc::GetEnvironmentVariable(TEXT("HOME"));
	if (!HomeEnv.IsEmpty())
	{
		CandidatePaths.Add(HomeEnv / TEXT("Documents") / TEXT("AnyUser") / TEXT("profile.anyuser"));
	}

	bool bLoaded = false;
	for (const FString& Path : CandidatePaths)
	{
		if (FPaths::FileExists(Path))
		{
			UE_LOG(LogTemp, Log, TEXT("[AnyUser] Discovered profile at: %s"), *Path);
			bLoaded = LoadProfileFromFile(Path);
			if (bLoaded)
			{
				break;
			}
		}
	}

	if (!bLoaded)
	{
		UE_LOG(LogTemp, Log, TEXT("[AnyUser] No local or global profile.anyuser found. Operating on standard accessibility defaults."));
		ApplyDropInInterceptors();
	}
}

bool UAnyUserSubsystem::LoadProfileFromFile(const FString& FilePath)
{
	if (!FPaths::FileExists(FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("[AnyUser] Profile not found at: %s"), *FilePath);
		return false;
	}

	FString JsonContent;
	if (FFileHelper::LoadFileToString(JsonContent, *FilePath))
	{
		return LoadProfileFromJson(JsonContent);
	}

	UE_LOG(LogTemp, Error, TEXT("[AnyUser] Failed to read content from file: %s"), *FilePath);
	return false;
}

bool UAnyUserSubsystem::LoadProfileFromJson(const FString& JsonString)
{
	FAnyUserProfile ParsedProfile;
	if (FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &ParsedProfile, 0, 0))
	{
		CurrentProfile = ParsedProfile;
		OnProfileLoaded.Broadcast(CurrentProfile);
		OnProfileChanged.Broadcast(CurrentProfile);
		
		UE_LOG(LogTemp, Log, TEXT("[AnyUser] Profile loaded successfully. UI Scale: %.2f | Screen Shake: %.2f | Aim Assist: %.2f"),
			CurrentProfile.vision.ui_scale,
			CurrentProfile.vision.screen_shake,
			CurrentProfile.motor.aim_assist_strength);

		ApplyDropInInterceptors();
		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("[AnyUser] Failed to parse profile JSON against AnyUser schema."));
	return false;
}

void UAnyUserSubsystem::ApplyDropInInterceptors()
{
	if (!bIsEnabled)
	{
		return;
	}

	// Drop-In Interceptor: Automatic global Slate & UMG UI scaling
	if (CurrentProfile.vision.ui_scale > 0.0f)
	{
		if (UUserInterfaceSettings* UISettings = GetMutableDefault<UUserInterfaceSettings>())
		{
			UISettings->ApplicationScale = CurrentProfile.vision.ui_scale;
			UE_LOG(LogTemp, Log, TEXT("[AnyUser] Drop-In Interceptor: Applied global UI ApplicationScale = %.2f"), CurrentProfile.vision.ui_scale);
		}
	}
}

void UAnyUserSubsystem::SetEnabled(bool bActive)
{
	bIsEnabled = bActive;
	if (bIsEnabled)
	{
		ApplyDropInInterceptors();
		UE_LOG(LogTemp, Log, TEXT("[AnyUser] Profile enabled. Accessibility overrides applied."));
	}
	else
	{
		// Revert drop-in interceptors to vanilla defaults
		if (UUserInterfaceSettings* UISettings = GetMutableDefault<UUserInterfaceSettings>())
		{
			UISettings->ApplicationScale = 1.0f;
		}
		UE_LOG(LogTemp, Log, TEXT("[AnyUser] Profile disabled. Reverted to vanilla game defaults."));
	}
	OnProfileChanged.Broadcast(CurrentProfile);
}

bool UAnyUserSubsystem::ToggleEnabled()
{
	SetEnabled(!bIsEnabled);
	return bIsEnabled;
}

