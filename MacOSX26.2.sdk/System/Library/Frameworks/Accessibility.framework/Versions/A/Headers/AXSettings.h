//
//  AXSettings.h
//  Accessibility
//
//  Copyright © 2022-2023 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Accessibility/AXFoundation.h>

NS_ASSUME_NONNULL_BEGIN

// Returns whether the system setting to prefer horizontal text is enabled for languages that support both vertical and horizontal text layout.
AX_EXTERN BOOL AXPrefersHorizontalTextLayout(void) API_AVAILABLE(ios(17.0), macos(14.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT;
AX_EXTERN NSNotificationName const AXPrefersHorizontalTextLayoutDidChangeNotification API_AVAILABLE(ios(17.0), macos(14.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT;

// Returns whether the system setting for displaying animations in an animated image is on or off.
AX_EXTERN BOOL AXAnimatedImagesEnabled(void) API_AVAILABLE(ios(17.0), macos(14.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT;
AX_EXTERN NSNotificationName const AXAnimatedImagesEnabledDidChangeNotification API_AVAILABLE(ios(17.0), macos(14.0), tvos(17.0), watchos(10.0)) NS_REFINED_FOR_SWIFT;

/// Returns whether Assistive Access is running.
/// The value does not change during a process's lifetime, so it is not necessary to observe changes.
AX_EXTERN BOOL AXAssistiveAccessEnabled(void) API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_SWIFT_NAME(getter:AccessibilitySettings.isAssistiveAccessEnabled());

#if TARGET_OS_VISION
// When true, indicates that the user prefers alternatives to head anchored content
// Alternate anchors should be used for most head anchored UI, such as world anchors
AX_EXTERN BOOL AXPrefersHeadAnchorAlternative(void) API_AVAILABLE(visionos(1.0)) NS_REFINED_FOR_SWIFT;
AX_EXTERN NSNotificationName const AXPrefersHeadAnchorAlternativeDidChangeNotification API_AVAILABLE(visionos(1.0)) NS_REFINED_FOR_SWIFT;
#endif

// Returns whether the system setting to prefer non-blinking text insertion indicators in editable text fields is enabled. Apps that draw custom insertion indicators should honor this setting.
AX_EXTERN BOOL AXPrefersNonBlinkingTextInsertionIndicator(void) API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT;
AX_EXTERN NSNotificationName const AXPrefersNonBlinkingTextInsertionIndicatorDidChangeNotification API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_SWIFT_NAME(AccessibilitySettings.prefersNonBlinkingTextInsertionIndicatorDidChangeNotification);

// Prefers that user interface items that rely on a prolonged, continuous swipe action provide an alternative requiring less physical dexterity or effort.
AX_EXTERN BOOL AXPrefersActionSliderAlternative(void) API_AVAILABLE(ios(26.1), macos(26.1), tvos(26.1), watchos(26.1), visionos(26.1)) NS_REFINED_FOR_SWIFT;
AX_EXTERN NSNotificationName const AXPrefersActionSliderAlternativeDidChangeNotification API_AVAILABLE(ios(26.1), macos(26.1), tvos(26.1), watchos(26.1), visionos(26.1)) NS_SWIFT_NAME(AccessibilitySettings.prefersActionSliderAlternativeDidChangeNotification);

// Returns whether the system preference for show borders is enabled
AX_EXTERN BOOL AXShowBordersEnabled(void) API_AVAILABLE(ios(26.1), macos(26.1), tvos(26.1), watchos(26.1), visionos(26.1)) NS_REFINED_FOR_SWIFT;
AX_EXTERN NSNotificationName const AXShowBordersEnabledStatusDidChangeNotification API_AVAILABLE(ios(26.1), macos(26.1), tvos(26.1), watchos(26.1), visionos(26.1)) NS_SWIFT_NAME(AccessibilitySettings.showBordersEnabledStatusDidChangeNotification);

typedef NS_ENUM(NSInteger, AXSettingsFeature) {
    // Jump to the setting for "Allow Apps to Request to Use" in Personal Voice. This is relevant for the AVSpeechSynthesis.personalVoiceAuthorizationStatus API.
    AXSettingsFeaturePersonalVoiceAllowAppsToRequestToUse = 1,
    // Jump to the setting for "Allow Apps to Add Audio to Calls." This is relevant for the AVAudioSession.preferredMicrophoneInjectionMode API.
    AXSettingsFeatureAllowAppsToAddAudioToCalls API_AVAILABLE(ios(18.2), macos(15.2), tvos(18.2), watchos(11.2), visionos(2.2)),
    AXSettingsFeatureAssistiveTouch API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), watchos(26.0), visionos(26.0)),
    AXSettingsFeatureAssistiveTouchDevices API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), watchos(26.0), visionos(26.0)),
    AXSettingsFeatureDwellControl API_AVAILABLE(ios(26.0), macos(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
} NS_SWIFT_NAME(AccessibilitySettings.Feature) API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0));

// Open the Settings app to a specific section.
// If successful, the completion handler will set error to nil.
AX_EXTERN void AXOpenSettingsFeature(AXSettingsFeature feature, void(^_Nullable completionHandler)(NSError *_Nullable error)) API_AVAILABLE(ios(18.0), macos(15.0), tvos(18.0), watchos(11.0), visionos(2.0)) NS_REFINED_FOR_SWIFT;

NS_ASSUME_NONNULL_END
