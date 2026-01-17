//
//  BEAccessibilityConstants.h
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>

#if BROWSERENGINEKIT_HAS_UIKIT

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

// Used when the element is an item in a menu.
BROWSERENGINE_EXTERN UIAccessibilityTraits BEAccessibilityTraitMenuItem NS_SWIFT_NAME(BEAccessibility.menuItem) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

// Used when the element should be treated as a button that opens a pop-up.
BROWSERENGINE_EXTERN UIAccessibilityTraits BEAccessibilityTraitPopUpButton NS_SWIFT_NAME(BEAccessibility.popUpButton) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

// Used when the element should be treated as a radio button.
BROWSERENGINE_EXTERN UIAccessibilityTraits BEAccessibilityTraitRadioButton NS_SWIFT_NAME(BEAccessibility.radioButton) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

// Used when the element should be treated as read-only.
BROWSERENGINE_EXTERN UIAccessibilityTraits BEAccessibilityTraitReadOnly NS_SWIFT_NAME(BEAccessibility.readOnly) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

// Used when the element should be treated as visited (e.g. for a link in a webpage).
BROWSERENGINE_EXTERN UIAccessibilityTraits BEAccessibilityTraitVisited NS_SWIFT_NAME(BEAccessibility.visited) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 Posted when the selection inside an element changes.

 When text inside an editable element changes, or the editing cursor position changes, this notification
 must be posted alongside, and after, BEAccessibilityValueChangedNotification.
 */
BROWSERENGINE_EXTERN UIAccessibilityNotifications BEAccessibilitySelectionChangedNotification NS_SWIFT_NAME(BEAccessibility.selectionChangedNotification) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 Posted when the value of an element changes. Some examples of when this notification is appropriate:
    - The value of an input element changes
    - Text is added or removed from any text control
    - aria-valuenow or aria-valuetext changes

 Furthermore, when text inside an editable element changes, or the editing cursor position changes, this notification
 must be posted alongside, and before, BEAccessibilitySelectionChangedNotification.
 */
BROWSERENGINE_EXTERN UIAccessibilityNotifications BEAccessibilityValueChangedNotification NS_SWIFT_NAME(BEAccessibility.valueChangedNotification) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

#ifdef __swift__
// This struct is not available in Objective-C. Its only purpose is to create a namespace for accessibility symbols in Swift.
typedef struct BEAccessibility { void *_reserved; } BEAccessibility;
#endif

NS_ASSUME_NONNULL_END

#endif // BROWSERENGINEKIT_HAS_UIKIT
