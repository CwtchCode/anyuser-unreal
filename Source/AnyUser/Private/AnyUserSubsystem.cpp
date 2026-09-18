#include "AnyUserSubsystem.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "JsonObjectConverter.h"

void UAnyUserSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Initialize with canonical Draft-07 baseline
	CurrentProfile = FAnyUserProfile();

	AutoDiscoverProfile();
}

void UAnyUserSubsystem::AutoDiscoverProfile()
{
	const FString SavedPath = FPaths::ProjectSavedDir() / TEXT("profile.anyuser");
	const FString ContentPath = FPaths::ProjectContentDir() / TEXT("profile.anyuser");

	if (FPaths::FileExists(SavedPath))
	{
		LoadProfileFromFile(SavedPath);
	}
	else if (FPaths::FileExists(ContentPath))
	{
		LoadProfileFromFile(ContentPath);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[AnyUser] No local profile.anyuser found. Operating on standard accessibility defaults."));
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

		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("[AnyUser] Failed to parse profile JSON against AnyUser schema."));
	return false;
}
