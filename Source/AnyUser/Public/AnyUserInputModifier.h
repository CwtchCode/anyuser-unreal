#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "AnyUserInputModifier.generated.h"

/**
 * UInputModifier_AnyUserToggle
 * Enhanced Input Modifier that converts continuous button holds into a latching toggle
 * when AnyUser motor.toggle_instead_of_hold is active.
 */
UCLASS(meta = (DisplayName = "AnyUser: Hold to Toggle Interceptor"))
class ANYUSER_API UInputModifier_AnyUserToggle : public UInputModifier
{
	GENERATED_BODY()

protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;

private:
	bool bIsLatched = false;
	bool bWasPressedLastFrame = false;
};

/**
 * UInputModifier_AnyUserTremorDebounce
 * Enhanced Input Modifier that absorbs rapid duplicate presses within motor.input_repeat_delay_ms.
 */
UCLASS(meta = (DisplayName = "AnyUser: Tremor Debounce Interceptor"))
class ANYUSER_API UInputModifier_AnyUserTremorDebounce : public UInputModifier
{
	GENERATED_BODY()

protected:
	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime) override;

private:
	double LastPressTimestamp = 0.0;
	bool bWasPressed = false;
};
