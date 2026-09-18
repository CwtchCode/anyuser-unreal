#pragma once

#include "CoreMinimal.h"
#include "AnyUserTypes.generated.h"

USTRUCT(BlueprintType)
struct FAnyUserSubtitles
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision|Subtitles")
	bool enabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision|Subtitles")
	FString size = TEXT("medium");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision|Subtitles")
	bool speaker_names = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision|Subtitles", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float background_opacity = 0.75f;
};

USTRUCT(BlueprintType)
struct FAnyUserVision
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision")
	FString colorblind_filter = TEXT("none");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision")
	bool high_contrast_mode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision", meta = (ClampMin = "0.5", ClampMax = "3.0"))
	float ui_scale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision")
	FString font_preference = TEXT("default");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float screen_shake = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision")
	bool flashing_effects = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Vision")
	FAnyUserSubtitles subtitles;
};

USTRUCT(BlueprintType)
struct FAnyUserMotor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Motor")
	bool toggle_instead_of_hold = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Motor")
	bool qte_auto_complete = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Motor", meta = (ClampMin = "0", ClampMax = "1000"))
	int32 input_repeat_delay_ms = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Motor", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float aim_assist_strength = 0.0f;
};

USTRUCT(BlueprintType)
struct FAnyUserAudio
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Audio")
	bool dialogue_boost = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Audio")
	bool mono_audio = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Audio", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float background_music_ducking = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Audio")
	bool tinnitus_frequency_cut = false;
};

USTRUCT(BlueprintType)
struct FAnyUserCognitive
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Cognitive")
	bool reading_level_simplified = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Cognitive")
	bool disable_time_limits = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Cognitive")
	FString tutorial_reminders = TEXT("medium");
};

USTRUCT(BlueprintType)
struct FAnyUserMetadata
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Metadata")
	FString profile_name = TEXT("Default");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Metadata")
	FString created_at;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Metadata")
	FString updated_at;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser|Metadata")
	FString device_hint;
};

USTRUCT(BlueprintType)
struct FAnyUserProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser")
	FString version = TEXT("1.0");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser")
	FString schema = TEXT("https://anyuser.net/schema/v1/anyuser-schema.json");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser")
	FAnyUserMetadata metadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser")
	FAnyUserVision vision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser")
	FAnyUserMotor motor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser")
	FAnyUserAudio audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnyUser")
	FAnyUserCognitive cognitive;
};
