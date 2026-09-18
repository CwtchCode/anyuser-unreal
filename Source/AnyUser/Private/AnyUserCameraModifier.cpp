#include "AnyUserCameraModifier.h"
#include "AnyUserSubsystem.h"
#include "Kismet/GameplayStatics.h"

UAnyUserCameraModifier::UAnyUserCameraModifier()
{
	Priority = 254; // High priority to ensure it scales final camera shake
}

bool UAnyUserCameraModifier::ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!GameInstance)
	{
		return Super::ModifyCamera(DeltaTime, ViewLocation, ViewRotation, FOV, NewViewLocation, NewViewRotation, NewFOV);
	}

	UAnyUserSubsystem* AnyUserSubsystem = GameInstance->GetSubsystem<UAnyUserSubsystem>();
	if (!AnyUserSubsystem)
	{
		return Super::ModifyCamera(DeltaTime, ViewLocation, ViewRotation, FOV, NewViewLocation, NewViewRotation, NewFOV);
	}

	const float ShakeMultiplier = AnyUserSubsystem->GetScreenShake();

	// If user requested static safe mode (screen_shake == 0.0), clamp to un-shaken position
	if (ShakeMultiplier <= 0.001f)
	{
		NewViewLocation = ViewLocation;
		NewViewRotation = ViewRotation;
		NewFOV = FOV;
		return true;
	}

	return Super::ModifyCamera(DeltaTime, ViewLocation, ViewRotation, FOV, NewViewLocation, NewViewRotation, NewFOV);
}
