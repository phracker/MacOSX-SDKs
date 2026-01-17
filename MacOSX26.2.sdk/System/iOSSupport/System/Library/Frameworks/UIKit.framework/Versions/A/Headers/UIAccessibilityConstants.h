#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityConstants.h>)
//
//  UIAccessibilityConstants.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*
 Accessibility Traits
 
 Traits are combined in a mask to help assistive applications understand
 the meaning and intended use of a particular accessibility element.
 
 UIKit applies appropriate traits to all standard controls, however the
 following traits may be used in conjunction with custom controls.
 
 When setting accessibility traits, combine custom traits with 
 [super accessibilityTraits]. An incorrect combination of custom traits
 will cause accessibility clients to incorrectly interpret the element.
 Use common sense when combining traits.
 */
typedef uint64_t UIAccessibilityTraits NS_TYPED_ENUM API_AVAILABLE(watchos(2.0));

// Used when the element has no traits.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitNone API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when the element should be treated as a button.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitButton API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when the element should be treated as a link.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitLink API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when an element acts as a header for a content section (e.g. the title of a navigation bar).
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitHeader API_AVAILABLE(ios(6.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when the text field element should also be treated as a search field.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitSearchField API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when the element should be treated as an image. Can be combined with button or link, for example.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitImage API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Used when the element is selected.
 For example, a selected row in a table or a selected button within a segmented control.
 */
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitSelected API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when the element plays its own sound when activated.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitPlaysSound API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when the element acts as a keyboard key.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitKeyboardKey API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when the element should be treated as static text that cannot change.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitStaticText API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Used when an element can be used to provide a quick summary of current 
 conditions in the app when the app first launches.  For example, when Weather
 first launches, the element with today's weather conditions is marked with
 this trait.
 */
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitSummaryElement API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when the control is not enabled and does not respond to user input.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitNotEnabled API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Used when the element frequently updates its label or value, but too often to send notifications.
 Allows an accessibility client to poll for changes. A stopwatch would be an example.
 */
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitUpdatesFrequently API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Used when activating an element starts a media session (e.g. playing a movie, recording audio) 
 that should not be interrupted by output from an assistive technology, like VoiceOver.
 */
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitStartsMediaSession API_AVAILABLE(ios(4.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Used when an element can be "adjusted" (e.g. a slider). The element must also 
 implement accessibilityIncrement and accessibilityDecrement.
 */
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitAdjustable API_AVAILABLE(ios(4.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used when an element allows direct touch interaction for VoiceOver users (for example, a view representing a piano keyboard).
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitAllowsDirectInteraction API_AVAILABLE(ios(5.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Informs VoiceOver that it should scroll to the next page when it finishes reading the contents of the
 element. VoiceOver will scroll by calling accessibilityScroll: with UIAccessibilityScrollDirectionNext and will 
 stop scrolling when it detects the content has not changed.
 */
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitCausesPageTurn API_AVAILABLE(ios(5.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Used when a view or accessibility container represents an ordered list of tabs.
 The object with this trait should return NO for isAccessibilityElement.
 */
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitTabBar API_AVAILABLE(ios(10.0), watchos(3.0)) NS_SWIFT_NONISOLATED;

// Used when the element should be treated as a toggle.
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitToggleButton API_AVAILABLE(ios(17.0), watchos(10.0)) NS_SWIFT_NONISOLATED;

/*
 Used when the element has zoom functionality.
 */
UIKIT_EXTERN const UIAccessibilityTraits UIAccessibilityTraitSupportsZoom API_AVAILABLE(ios(17.0), watchos(10.0)) NS_SWIFT_NONISOLATED;

/*
 Accessibility Notifications
 
 UIKit posts notifications for standard events as appropriate, however the
 following notifications may be posted to accommodate custom controls
 and events.
 */
typedef uint32_t UIAccessibilityNotifications NS_TYPED_ENUM API_AVAILABLE(watchos(2.0));

/*
 Should be posted when a new view appears that encompasses a major portion of the screen.
 Optionally, pass the element that VoiceOver should move to after processing the notification.
 */
UIKIT_EXTERN const UIAccessibilityNotifications UIAccessibilityScreenChangedNotification API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Should be posted when the layout of a screen changes, for example when an individual
 element appears or disappears.
 Optionally, pass the element that VoiceOver should move to after processing the notification.
 */
UIKIT_EXTERN const UIAccessibilityNotifications UIAccessibilityLayoutChangedNotification API_AVAILABLE(watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Should be posted when an announcement needs to be conveyed to VoiceOver. 
 VoiceOver will output the announcement string that is used as the argument.
 The argument is a NSString.
 */
UIKIT_EXTERN const UIAccessibilityNotifications UIAccessibilityAnnouncementNotification API_AVAILABLE(ios(4.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Should be posted after accessibilityScroll: is called and the scrolling action has completed.
 A string representing the status of the new scroll position should be used as the argument
 (e.g. "Page 2 of 5"). If the same status is used repeatedly, the assistive technology will
 indicate a border has been reached.
 The argument is a NSString.
 */
UIKIT_EXTERN const UIAccessibilityNotifications UIAccessibilityPageScrolledNotification API_AVAILABLE(ios(4.2), watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Should be posted to pause an assistive technology's operations temporarily.
 For example, you may want to pause scanning in Switch Control while your app plays an animation.
 An identifier representing the assistive technology should be used as the argument.
 Currently, these notifications only apply to Switch Control.
 The notifications must be balanced.  That is, every UIAccessibilityPauseAssistiveTechnologyNotification
 should be followed by a matching UIAccessibilityResumeAssistiveTechnologyNotification with the same argument.
 If the user performs an action that requires the assistive technology to resume operations,
 it may do so before it receives the corresponding UIAccessibilityResumeAssistiveTechnologyNotification.
 The argument is a NSString.
 */
UIKIT_EXTERN const UIAccessibilityNotifications UIAccessibilityPauseAssistiveTechnologyNotification API_AVAILABLE(ios(8.0), watchos(2.0)) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN const UIAccessibilityNotifications UIAccessibilityResumeAssistiveTechnologyNotification API_AVAILABLE(ios(8.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

/*
 Listen for this notification to know when VoiceOver finishes outputting an announcement. 
 The userInfo dictionary contains UIAccessibilityAnnouncementKeyString and UIAccessibilityAnnouncementKeyWasSuccessful.
 */
UIKIT_EXTERN NSNotificationName const UIAccessibilityAnnouncementDidFinishNotification API_AVAILABLE(ios(6.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// The corresponding value is the string that was used for the announcement.
UIKIT_EXTERN NSString *const UIAccessibilityAnnouncementKeyStringValue API_AVAILABLE(ios(6.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// The corresponding value is an NSNumber representing whether VoiceOver successfully outputted the announcement.
UIKIT_EXTERN NSString *const UIAccessibilityAnnouncementKeyWasSuccessful API_AVAILABLE(ios(6.0), watchos(2.0)) NS_SWIFT_NONISOLATED;


// In order to know when an assistive technology has focused on an element listen to this notification
// The newly focused element will be referenced by UIAccessibilityElementFocusedKeyElement in the userInfo dictionary.
UIKIT_EXTERN NSNotificationName const UIAccessibilityElementFocusedNotification API_AVAILABLE(ios(9.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// The corresponding value is the element that is now focused by the assistive technology.
UIKIT_EXTERN NSString *const UIAccessibilityFocusedElementKey API_AVAILABLE(ios(9.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// The corresponding value is the element that had previously been focused by the assistive technology.
UIKIT_EXTERN NSString *const UIAccessibilityUnfocusedElementKey API_AVAILABLE(ios(9.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// The corresponding value is the identifier of the assistive technology
UIKIT_EXTERN NSString *const UIAccessibilityAssistiveTechnologyKey API_AVAILABLE(ios(9.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

typedef NSString * UIAccessibilityAssistiveTechnologyIdentifier NS_TYPED_ENUM API_AVAILABLE(watchos(5.0));

/*
 The following identifier should be used as the argument when posting a UIAccessibilityPauseAssistiveTechnologyNotification
 or a UIAccessibilityResumeAssistiveTechnologyNotification.
 */
UIKIT_EXTERN UIAccessibilityAssistiveTechnologyIdentifier const UIAccessibilityNotificationSwitchControlIdentifier API_AVAILABLE(ios(8.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// Used to identify VoiceOver as the assistive technology.
UIKIT_EXTERN UIAccessibilityAssistiveTechnologyIdentifier const UIAccessibilityNotificationVoiceOverIdentifier API_AVAILABLE(ios(9.0), watchos(2.0)) NS_SWIFT_NONISOLATED;


/*
 The following values describe how the receiver's elements should be navigated by an assistive technology.
 */
typedef NS_ENUM(NSInteger, UIAccessibilityNavigationStyle) {
    /*
     The assistive technology will automatically determine how the receiver's elements should be navigated.
     This is the default value.
     */
    UIAccessibilityNavigationStyleAutomatic = 0,
    
    /*
     The receiver's elements should be navigated as separate elements.
     */
    UIAccessibilityNavigationStyleSeparate = 1,
    
    /*
     The receiver’s elements should be combined and navigated as a single item.
     When the combined item has been selected, the assistive technology will navigate each element separately.
     */
    UIAccessibilityNavigationStyleCombined = 2,
} API_AVAILABLE(ios(8.0), watchos(2.0));


typedef NS_ENUM(NSInteger, UIAccessibilityContainerType) {
    UIAccessibilityContainerTypeNone = 0,
    UIAccessibilityContainerTypeDataTable,     // If using this container type, you must also implement the UIAccessibilityContainerDataTable protocol.
    UIAccessibilityContainerTypeList,
    UIAccessibilityContainerTypeLandmark,
    UIAccessibilityContainerTypeSemanticGroup API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) // Assistive technologies might query the accessibility properties set on the container, such as the accessibilityLabel, in order to output appropriate information about the semantic group to the user
} API_AVAILABLE(ios(11.0), watchos(4.0));

typedef NS_OPTIONS(NSUInteger, UIAccessibilityDirectTouchOptions) {
    UIAccessibilityDirectTouchOptionNone = 0,
    // Allows a direct touch area to immediately receive touch events without VoiceOver speaking. Appropriate
    // for apps that provide direct audio feedback during interaction that would conflict with VoiceOver (like a drum pad in a music creation app).
    UIAccessibilityDirectTouchOptionSilentOnTouch = 1 << 0,
    // Requires VoiceOver to activate the element before touch passthrough starts.
    UIAccessibilityDirectTouchOptionRequiresActivation = 1 << 1,
} NS_SWIFT_NAME(UIAccessibility.DirectTouchOptions) API_AVAILABLE(ios(17.0), watchos(10.0));

// The following constants can be used with either the accessibilityTextualContext property, or with the
// UIAccessibilityTextAttributeContext attributed key.
typedef NSString * UIAccessibilityTextualContext NS_TYPED_EXTENSIBLE_ENUM API_AVAILABLE(ios(13.0), watchos(6.0));
UIKIT_EXTERN UIAccessibilityTextualContext const UIAccessibilityTextualContextWordProcessing API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN UIAccessibilityTextualContext const UIAccessibilityTextualContextNarrative API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN UIAccessibilityTextualContext const UIAccessibilityTextualContextMessaging API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN UIAccessibilityTextualContext const UIAccessibilityTextualContextSpreadsheet API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN UIAccessibilityTextualContext const UIAccessibilityTextualContextFileSystem API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN UIAccessibilityTextualContext const UIAccessibilityTextualContextSourceCode API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;
UIKIT_EXTERN UIAccessibilityTextualContext const UIAccessibilityTextualContextConsole API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;


// The following constants can be used with either the accessibilityAnnouncementPriority property, or with the
// UIAccessibilityAnnouncementPriority attributed key.
typedef NSString * UIAccessibilityPriority NS_TYPED_ENUM API_AVAILABLE(ios(17.0), watchos(10.0));
// Announcements will interrupt other speech and cannot be interrupted once started.
UIKIT_EXTERN UIAccessibilityPriority const UIAccessibilityPriorityHigh API_AVAILABLE(ios(17.0), watchos(10.0)) NS_SWIFT_NONISOLATED;
// Announcements will interrupt existing speech, but are interruptible if a new speech utterance is started.
UIKIT_EXTERN UIAccessibilityPriority const UIAccessibilityPriorityDefault API_AVAILABLE(ios(17.0), watchos(10.0)) NS_SWIFT_NONISOLATED;
// Announcements are queued and spoken when other speech utterances have completed.
UIKIT_EXTERN UIAccessibilityPriority const UIAccessibilityPriorityLow API_AVAILABLE(ios(17.0), watchos(10.0)) NS_SWIFT_NONISOLATED;

typedef NS_ENUM(NSInteger, UIAccessibilityExpandedStatus) {
    UIAccessibilityExpandedStatusUnsupported = 0,
    UIAccessibilityExpandedStatusExpanded,
    UIAccessibilityExpandedStatusCollapsed
} NS_SWIFT_NAME(UIAccessibility.ExpandedStatus) API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0), watchos(11.0));

/*
 Accessibility Speech Attributes
 
 The following attributes can be used in an NSAttributedString to modify how
 an assistive technology like VoiceOver will pronounce the string.
 */

// Use an NSNumber with a YES or NO value.
// If YES, then all punctuation will be spoken (e.g. when displaying code).
// If NO, then no punctuation will be spoken.
// By default, if this attribute is not present, the user's settings will be used.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilitySpeechAttributePunctuation API_AVAILABLE(ios(7.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// Use an NSString with a BCP-47 language code to identify the language of a segment of a string.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilitySpeechAttributeLanguage API_AVAILABLE(ios(7.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// Use an NSNumber with a value between [0-2] that specifies the pitch.
// For example, you may want to lower the pitch when an object is deleted, or raise the pitch if an object is inserted.
// Default value == 1.0f.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilitySpeechAttributePitch API_AVAILABLE(ios(7.0), watchos(2.0)) NS_SWIFT_NONISOLATED;

// The corresponding value for this key should be a NSNumber with a YES or NO value.
// If YES, then this announcement will be queued behind existing speech; if NO, then it will interrupt existing speech.
// Default behavior is to interrupt existing speech.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilitySpeechAttributeQueueAnnouncement API_AVAILABLE(ios(11.0), watchos(4.0)) API_DEPRECATED_WITH_REPLACEMENT("UIAccessibilitySpeechAttributeAnnouncementPriority", ios(11.0, 17.0), visionos(1.0, 1.0)) NS_SWIFT_NONISOLATED;

// Use with a UIAccessibilityAnnouncementPriority value to specify whether this announcement can be queued or interrupted.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilitySpeechAttributeAnnouncementPriority API_AVAILABLE(ios(17.0), watchos(10.0)) NS_SWIFT_NONISOLATED;

// Use an NSString, containing International Phonetic Alphabet (IPA) symbols.
// Controls the pronunciation of a word or phrase, e.g. a proper name.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilitySpeechAttributeIPANotation API_AVAILABLE(ios(11.0), watchos(4.0)) NS_SWIFT_NONISOLATED;

// Use an NSNumber with a YES or NO value to specify whether each letter in the string should be spoken separately.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilitySpeechAttributeSpellOut API_AVAILABLE(ios(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;


/*
 Accessibility Text Attributes
 
 The following attributes can be used in the NSAttributedString returned by attributeText methods of views conforming to UITextInput
 to convey extra information about the text.
 
 Use existing NSAttributedString attributes for properties not defined here from <UIKit/NSAttributedString.h>
 
 To include an inline element (like an image or table), use NSAttachmentAttributeName and set the value to the element.
 */

// Use an NSNumber where the value is [0, 6]. Use 0 to indicate the absence of a specific heading level.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilityTextAttributeHeadingLevel API_AVAILABLE(ios(11.0), watchos(4.0)) NS_SWIFT_NONISOLATED;

// Use an NSArray of localized NSStrings to convey custom text attributes.
// For example, a range of text may have multiple custom 'annotation styles, which can be described with this key.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilityTextAttributeCustom API_AVAILABLE(ios(11.0), watchos(4.0)) NS_SWIFT_NONISOLATED;

// Use a UIAccessibilityTextualContext to specify how this text content should be interpreted by assistive technologies.
UIKIT_EXTERN NSAttributedStringKey const UIAccessibilityTextAttributeContext API_AVAILABLE(ios(13.0), tvos(13.0), watchos(6.0)) NS_SWIFT_NONISOLATED;

#ifdef __swift__
// This struct is not available in Objective-C. Its only purpose is to create a namespace for accessibility symbols in Swift.
typedef struct UIAccessibility { void *_reserved; } UIAccessibility;
#endif

NS_HEADER_AUDIT_END(nullability, sendability)


#else
#import <UIKitCore/UIAccessibilityConstants.h>
#endif
