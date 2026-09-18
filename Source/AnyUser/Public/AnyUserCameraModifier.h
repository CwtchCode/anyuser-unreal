#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "AnyUserCameraModifier.generated.h"

/**
 * UAnyUserCameraModifier - Camera Modifier that intercepts screen shake trauma.
 * Clamps or eliminates camera shake offsets based on profile.vision.screen_shake.
 */
UCLASS()
class ANYUSER_API UAnyUserCameraModifier : public UCameraModifier
{
	GENERATED_BODY()

public:
	UAnyUserCameraModifier();

	virtual bool ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;
};
