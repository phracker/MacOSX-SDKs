//
//  AEAssessmentConfiguration.h
//  AutomaticAssessmentConfiguration
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <AutomaticAssessmentConfiguration/AEVisibility.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class AEAssessmentApplication;
@class AEAssessmentParticipantConfiguration;

/// Configuration information for an assessment session.
///
/// Create a configuration instance and pass it to the ``AEAssessmentSession/init(configuration:)`` initializer of an ``AEAssessmentSession`` instance to create a new assessment session. Before using the configuration, indicate which exceptions you want to allow for the assessment session's restrictions by setting values on the configuration instance. For example, you can set values to allow dictation and certain aspects of autocorrect:
///
/// ```swift
/// let config = AEAssessmentConfiguration()
///
/// #if os(iOS) // These exceptions available only on iOS and iPadOS.
/// config.allowsDictation = true
/// config.autocorrectMode = [.punctuation, .spelling]
/// #endif
///
/// let session = AEAssessmentSession(configuration: config)
/// ```
///
/// While you provide a configuration instance when creating a session on iOS, iPadOS, and macOS, specific exceptions apply only to certain platforms. In particular, on macOS, you can selectively make specific apps besides your own available during an assessment — for example, to allow users to access a calculator or a dictionary. All other exceptions apply only to iOS and iPadOS.
///
/// ## Topics
///
/// ### Allowing access to other apps
///
/// - ``setConfiguration(_:for:)``
/// - ``configurationsByApplication``
/// - ``remove(_:)``
/// - ``mainParticipantConfiguration``
/// - ``AEAssessmentApplication``
/// - ``AEAssessmentParticipantConfiguration``
///
/// ### Allowing accessibility
///
/// - ``allowsAccessibilityKeyboard``
/// - ``allowsAccessibilityLiveCaptions``
/// - ``allowsAccessibilityReader``
/// - ``allowsAccessibilitySpeech``
/// - ``allowsAccessibilityTypingFeedback``
/// - ``allowsDictation``
///
/// ### Allowing typing assistance
///
/// - ``allowsContinuousPathKeyboard``
/// - ``allowsKeyboardShortcuts``
/// - ``allowsPredictiveKeyboard``
/// - ``allowsPasswordAutoFill``
///
/// ### Allowing corrections
///
/// - ``allowsSpellCheck``
/// - ``autocorrectMode-swift.property``
/// - ``AutocorrectMode-swift.struct``
///
/// ### Allowing handoff
///
/// - ``allowsActivityContinuation``
///
/// ### Allowing content capture
///
/// - ``allowsScreenshots``
///
API_AVAILABLE(ios(13.4), macos(10.15.4), macCatalyst(14.0))
API_UNAVAILABLE(visionos)
@interface AEAssessmentConfiguration: NSObject <NSCopying>

/// The set of autocorrect features that you can enable during an assessment.
///
/// Use one or more of the autocorrect modes to set the ``AEAssessmentConfiguration/autocorrectMode-swift.property`` property of an ``AEAssessmentConfiguration`` instance. For example, you can enable both spelling and punctuation corrections by combining ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/spelling`` and ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/punctuation``:
///
/// ```swift
/// let config = AEAssessmentConfiguration()
///
/// #if os(iOS) // Available only on iOS and iPadOS.
/// config.autocorrectMode = [.punctuation, .spelling]
/// #endif
///
/// let session = AEAssessmentSession(configuration: config)
/// ```
///
/// ## Topics
///
/// ### Creating a mode
///
/// - ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/init(rawValue:)``
///
/// ### Modes
///
/// - ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/punctuation``
/// - ``AEAssessmentConfiguration/AutocorrectMode-swift.struct/spelling``
/// - ``AEAutocorrectMode/AEAutocorrectModeNone``
///
API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0))
API_UNAVAILABLE(visionos)
typedef NS_OPTIONS(NSUInteger, AEAutocorrectMode) {
    AEAutocorrectModeNone = 0,
    /// A mode in which autocorrect checks for spelling as the user types.
    ///
    AEAutocorrectModeSpelling = 1 << 0,
    /// A mode in which autocorrect checks punctuation as the user types.
    ///
    AEAutocorrectModePunctuation = 1 << 1,
} NS_SWIFT_NAME(AEAssessmentConfiguration.AutocorrectMode);

/// The autocorrect mode that specifies which autocorrect features to allow during an assessment.
///
/// Users can turn on autocorrect in the Settings app (General > Keyboard > Auto-Correction). An assessment session disables this feature by default, but you can allow it by setting ``AEAssessmentConfiguration/autocorrectMode-swift.property`` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session. Set the mode's value to some combination of the the values from the ``AEAssessmentConfiguration/AutocorrectMode-swift.struct`` structure.
///
@property (nonatomic, assign) AEAutocorrectMode autocorrectMode API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0));

/// A Boolean value that indicates whether to allow spell check during an assessment.
///
/// Users can activate the spell checker by turning on the Check Spelling feature in the Settings app (General > Keyboard). An assessment session disables spell checking by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsSpellCheck`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsSpellCheck API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0));

/// A Boolean value that indicates whether to enable the predictive keyboard during an assessment.
///
/// Users can turn on the Predictive Keyboard feature in the Settings app (General > Keyboard). An assessment session disables this feature by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsPredictiveKeyboard`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsPredictiveKeyboard API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0));

/// A Boolean value that indicates whether to allow keyboard shortcuts during an assessment.
///
/// Users can add Keyboard Shortcuts in the Settings app (General > Keyboard > Text Replacement). An assessment session disables the use of keyboard shortcuts by default, but you can allow them by setting ``AEAssessmentConfiguration/allowsKeyboardShortcuts`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsKeyboardShortcuts API_AVAILABLE(ios(14.0), macCatalyst(18.0), macos(15.0));

/// A Boolean value that indicates whether to allow Handoff during an assessment.
///
/// Handoff lets users start an activity on one device and seamlessly resume the activity on another. Users control whether a device participates in Handoff by turning the feature on or off in the Settings app (General > AirPlay & Handoff > Handoff). An assessment disables this feature by default, but you can allow users undergoing an assessment to continue to use Handoff by setting ``AEAssessmentConfiguration/allowsActivityContinuation`` to `true`.
///
@property (nonatomic, assign) BOOL allowsActivityContinuation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow the use of dictation during an assessment.
///
/// By turning on Enable Dictation (General > Keyboard in the Settings app on iOS and iPadOS), users can speak into their device and have the words they speak converted to text. An assessment session disables this feature by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsDictation`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsDictation API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow alternative input methods in the Accessibility Keyboard during an assessment.
///
/// Users can enable the Accessibility Keyboard in the Settings app (Accessibility > Keyboard > Accessibility Keyboard) to access an on-screen keyboard with alternative input methods. An assessment session disables alternative input methods in the Accessibility Keyboard by default, but you can allow them by setting ``AEAssessmentConfiguration/allowsAccessibilityKeyboard`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityKeyboard API_AVAILABLE(macos(26.1), macCatalyst(26.1)) API_UNAVAILABLE(ios);

/// A Boolean value that indicates whether to allow Live Captions during an assessment.
///
/// Users can enable Live Captions in the Settings app (Accessibility > Live Captions) to receive real-time transcription of spoken audio as text on screen. An assessment session disables Live Captions by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsAccessibilityLiveCaptions`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityLiveCaptions API_AVAILABLE(ios(26.1), macCatalyst(26.1), macos(26.1));

/// A Boolean value that indicates whether to allow the Accessibility Reader during an assessment.
///
/// Users can enable the Accessibility Reader in the Settings app (Accessibility > Read & Speak > Accessibility Reader) to have text content formatted or read aloud. An assessment session disables the Accessibility Reader by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsAccessibilityReader`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityReader API_AVAILABLE(ios(26.1), macCatalyst(26.1), macos(26.1));

/// A Boolean value that indicates whether to allow the speech-related accessibility features during an assessment.
///
/// A device reads text aloud for users who need it. In particular, users can enable the following features from Accessibility > Spoken Content in the Settings app on iOS and iPadOS:
/// - Speak Selection
/// - Speak Screen
/// - Typing Feedback > Speak Words
///
/// An assessment session disables these features by default, but you can allow them by setting ``AEAssessmentConfiguration/allowsAccessibilitySpeech`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilitySpeech API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow accessibility typing feedback during an assessment.
///
/// Users can enable typing feedback features in the Settings app (Accessibility > Keyboards & Typing > Typing Feedback)  to receive audio feedback when typing. An assessment session disables these accessibility typing feedback features by default, but you can allow them by setting ``AEAssessmentConfiguration/allowsAccessibilityTypingFeedback`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsAccessibilityTypingFeedback API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow password autofill during an assessment.
///
/// Users can store passwords for use with Password Autofill by turning on the feature in the Settings app (General > Passwords > AutoFill Passwords). An assessment session disables Password Autofill by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsPasswordAutoFill`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsPasswordAutoFill API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow Slide to Type to operate during an assessment.
///
/// Users can turn on Slide to Type in the Settings app (General > Keyboard). An assessment session disables this feature by default, but you can allow it by setting ``AEAssessmentConfiguration/allowsContinuousPathKeyboard`` to `true` in the ``AEAssessmentConfiguration`` instance that you use to initialize a session.
///
@property (nonatomic, assign) BOOL allowsContinuousPathKeyboard API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, macCatalyst);

/// A Boolean value that indicates whether to allow screenshots copied to the clipboard during an assessment.
///
/// An assessment session disables the ability to take screenshots by default to maintain assessment integrity. This property specifically applies to screenshots that are copied to the clipboard, typically those taken using the Command+Control+Shift+3 and Command+Control+Shift+4 keyboard shortcuts. You can allow clipboard screenshots by setting `allowsScreenshots` to `true`.
///
/// - Note: The clipboard is cleared before the assessment session ends to prevent exporting captured content.
///
@property (nonatomic, assign) BOOL allowsScreenshots API_AVAILABLE(macos(26.1), macCatalyst(26.1)) API_UNAVAILABLE(ios);

/// The app-specific configuration for the app that invokes the assessment.
///
/// Use this property to get and customize the app-specific configuration that's applied to your own app. For example, you can set the `allowsNetworkAccess` property for your own app:
///
/// ```swift
/// let config = AEAssessmentConfiguration()
/// config.mainParticipantConfiguration.allowsNetworkAccess = false
/// ```
///
@property (nonatomic, strong, readonly) AEAssessmentParticipantConfiguration *mainParticipantConfiguration API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

/// The collection of apps available during an assessment, along with their associated configurations.
///
/// Access this property to get a list of the currently allowed secondary apps and their individual configurations. Add apps to the list by calling the ``AEAssessmentConfiguration/setConfiguration(_:for:)`` method. Remove them from the list by calling the ``AEAssessmentConfiguration/remove(_:)`` method.
///
@property (nonatomic, copy, readonly) NSDictionary<AEAssessmentApplication *, AEAssessmentParticipantConfiguration *> *configurationsByApplication API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

/// Adds an app to the list of apps available during an assessment.
///
/// Use this method to make an app besides your own available during an assessment. Create a representation of the app that you want to allow as an ``AEAssessmentApplication`` instance, and the configuration for that app using an ``AEAssessmentParticipantConfiguration`` instance:
///
/// ```swift
/// let calculator = AEAssessmentApplication(bundleIdentifier: "com.apple.calculator")
/// let calculatorConfig = AEAssessmentParticipantConfiguration()
/// calculatorConfig.allowsNetworkAccess = false // Calculator doesn't need the network.
/// ```
///
/// Use the app and its configuration to create an assessment configuration, and either create an assessment session with that, or update an existing session as shown below:
///
/// ```swift
/// let configuration = AEAssessmentConfiguration()
/// configuration.setConfiguration(calculatorConfig, for: calculator)
/// session.update(to: configuration)
/// ```
///
/// You can get a list of the currently allowed apps by accessing the ``AEAssessmentConfiguration/configurationsByApplication`` property. You can disallow a previously allowed app by using the ``AEAssessmentConfiguration/remove(_:)`` method.
///
/// - Parameters:
///   - configuration: The configuration of the secondary app.
///   - application: The app that you want to configure.
///
- (void)setConfiguration:(AEAssessmentParticipantConfiguration *)configuration forApplication:(AEAssessmentApplication *)application API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

/// Removes the availability of a previously allowed app.
///
/// Use this method to remove apps that you previously added to the list of apps that are available during an assessment with the ``AEAssessmentConfiguration/setConfiguration(_:for:)`` method. You can get the list of currently allowed apps by accessing the configuration's ``AEAssessmentConfiguration/configurationsByApplication`` property.
///
/// - Parameters:
///   - application: The app that you want to remove from the list of allowed secondary apps.
///
- (void)removeApplication:(AEAssessmentApplication *)application API_AVAILABLE(ios(17.5), macCatalyst(15.0), macos(12.0));

@end

NS_ASSUME_NONNULL_END
