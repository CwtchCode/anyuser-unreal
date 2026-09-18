#include "AnyUserInputModifier.h"
#include "AnyUserSubsystem.h"
#include "Kismet/GameplayStatics.h"

FInputActionValue UInputModifier_AnyUserToggle::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!GameInstance) return CurrentValue;

	UAnyUserSubsystem* Subsystem = GameInstance->GetSubsystem<UAnyUserSubsystem>();
	if (!Subsystem || !Subsystem->IsToggleInsteadOfHold())
	{
		return CurrentValue;
	}

	const bool bIsCurrentlyPressed = CurrentValue.Get<bool>();

	// Detect rising edge (just pressed)
	if (bIsCurrentlyPressed && !bWasPressedLastFrame)
	{
		bIsLatched = !bIsLatched;
	}

	bWasPressedLastFrame = bIsCurrentlyPressed;

	// Return latched state
	return FInputActionValue(bIsLatched);
}

FInputActionValue UInputModifier_AnyUserTremorDebounce::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	if (!GameInstance) return CurrentValue;

	UAnyUserSubsystem* Subsystem = GameInstance->GetSubsystem<UAnyUserSubsystem>();
	if (!Subsystem) return CurrentValue;

	const int32 DelayMs = Subsystem->GetInputRepeatDelayMs();
	if (DelayMs <= 0) return CurrentValue;

	const bool bIsCurrentlyPressed = CurrentValue.Get<bool>();

	if (bIsCurrentlyPressed && !bWasPressed)
	{
		const double CurrentTime = FPlatformTime::Seconds();
		if ((CurrentTime - LastPressTimestamp) * 1000.0 < static_cast<double>(DelayMs))
		{
			// Tremor duplicate bounce absorbed!
			bWasPressed = true;
			return FInputActionValue(false);
		}

		LastPressTimestamp = CurrentTime;
	}

	bWasPressed = bIsCurrentlyPressed;
	return CurrentValue;
}
