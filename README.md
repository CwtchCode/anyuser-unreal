# AnyUser Unreal Engine 5 Plugin

Universal accessibility standard and Behavioral Interceptors for **Unreal Engine 5** (5.0 - 5.4+).

Eliminate "Configuration Fatigue" by configuring screen shake dampening, hold-vs-toggle input, aim assistance, and audio filters before Frame 1.

---

## 📦 Installation

1. Copy the `sdk/unreal/` folder into your project's `Plugins/` directory:
   ```
   YourUnrealProject/
   └── Plugins/
       └── AnyUser/
           ├── AnyUser.uplugin
           └── Source/
               └── AnyUser/
                   ├── AnyUser.Build.cs
                   ├── Public/
                   └── Private/
   ```

2. Open your project in Unreal Engine.
3. If prompted to rebuild missing modules, click **Yes**.
4. In **Edit &rarr; Plugins**, ensure **AnyUser Accessibility Standard** is enabled.

---

## 🚀 Quick Start Guide

### 1. Ingestion Subsystem (`UAnyUserSubsystem`)
`UAnyUserSubsystem` is a `UGameInstanceSubsystem` that automatically runs on boot and persists across all level transitions:
- Automatically looks for `Saved/profile.anyuser` or `Content/profile.anyuser`.
- Accessible in C++ via:
  ```cpp
  UAnyUserSubsystem* AnyUser = GetGameInstance()->GetSubsystem<UAnyUserSubsystem>();
  float UiScale = AnyUser->GetUiScale();
  float ScreenShake = AnyUser->GetScreenShake();
  bool bIsToggle = AnyUser->IsToggleInsteadOfHold();
  ```
- Accessible in Blueprints via **Get Any User Subsystem** node.

---

## 🎮 Behavioral Interceptors

### 1. Camera Shake Dampener (`UAnyUserCameraModifier`)
Attach `UAnyUserCameraModifier` to your `PlayerCameraManager`:
- Automatically scales and clamps all camera shake impulses by `profile.vision.screen_shake`.
- If `screen_shake == 0.0f` (static safe), all camera shake is completely zeroed out to eliminate vestibular triggers and motion sickness.

In Blueprints:
- On `Event BeginPlay` in your Player Controller:
  - Call **Add Camera Modifier** with class set to `AnyUserCameraModifier`.

### 2. Enhanced Input Modifiers
Add AnyUser input modifiers directly to your Input Actions (`IA_Sprint`, `IA_Fire`):
- **`AnyUser: Hold to Toggle Interceptor`**:
  - Automatically converts button holds into continuous toggles when `motor.toggle_instead_of_hold` is active.
- **`AnyUser: Tremor Debounce Interceptor`**:
  - Automatically absorbs accidental double-taps within `motor.input_repeat_delay_ms` to support players with motor tremors.

---

## 📜 Canonical Schema
Draft-07 specification:
[https://anyuser.net/schema/v1/anyuser-schema.json](https://anyuser.net/schema/v1/anyuser-schema.json)
