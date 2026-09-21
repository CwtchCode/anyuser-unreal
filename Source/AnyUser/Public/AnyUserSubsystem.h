#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AnyUserTypes.h"
#include "AnyUserSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyUserProfileLoaded, const FAnyUserProfile&, Profile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyUserProfileChanged, const FAnyUserProfile&, Profile);

/**
 * UAnyUserSubsystem - GameInstance Subsystem managing .anyuser accessibility profiles.
 * Persists across all level transitions and exposes Behavioral Interceptors.
 */
UCLASS()
class ANYUSER_API UAnyUserSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(BlueprintAssignable, Category = "AnyUser|Events")
	FOnAnyUserProfileLoaded OnProfileLoaded;

	UPROPERTY(BlueprintAssignable, Category = "AnyUser|Events")
	FOnAnyUserProfileChanged OnProfileChanged;

	UFUNCTION(BlueprintCallable, Category = "AnyUser|Profile")
	bool LoadProfileFromFile(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "AnyUser|Profile")
	bool LoadProfileFromJson(const FString& JsonString);

	UFUNCTION(BlueprintPure, Category = "AnyUser|Profile")
	const FAnyUserProfile& GetActiveProfile() const { return CurrentProfile; }

	// Quick Accessors
	UFUNCTION(BlueprintPure, Category = "AnyUser|Vision")
	float GetUiScale() const { return CurrentProfile.vision.ui_scale; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Vision")
	float GetScreenShake() const { return CurrentProfile.vision.screen_shake; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Vision")
	FString GetColorblindFilter() const { return CurrentProfile.vision.colorblind_filter; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Vision")
	bool IsHighContrastMode() const { return CurrentProfile.vision.high_contrast_mode; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Motor")
	bool IsToggleInsteadOfHold() const { return CurrentProfile.motor.toggle_instead_of_hold; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Motor")
	float GetAimAssistStrength() const { return CurrentProfile.motor.aim_assist_strength; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Motor")
	int32 GetInputRepeatDelayMs() const { return CurrentProfile.motor.input_repeat_delay_ms; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Audio")
	bool IsTinnitusCut() const { return CurrentProfile.audio.tinnitus_frequency_cut; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Audio")
	bool IsDialogueBoost() const { return CurrentProfile.audio.dialogue_boost; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Cognitive")
	bool IsReadingLevelSimplified() const { return CurrentProfile.cognitive.reading_level_simplified; }

	UFUNCTION(BlueprintPure, Category = "AnyUser|Cognitive")
	bool IsDisableTimeLimits() const { return CurrentProfile.cognitive.disable_time_limits; }

	UFUNCTION(BlueprintCallable, Category = "AnyUser|Interceptors")
	void ApplyDropInInterceptors();

private:
	UPROPERTY()
	FAnyUserProfile CurrentProfile;

	void AutoDiscoverProfile();
};
