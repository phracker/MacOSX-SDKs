/*
	NSAccessibility.h
	Application Kit
	Copyright (c) 2001-2002, Apple Computer, Inc.
	All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

#import <AppKit/AppKitDefines.h>
#import <AppKit/NSErrors.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>

@class NSString, NSArray;


//
// Accessibility Informal Protocol
//

@interface NSObject (NSAccessibility)

// attribute methods
- (NSArray *)accessibilityAttributeNames;
- (id)accessibilityAttributeValue:(NSString *)attribute;
- (BOOL)accessibilityIsAttributeSettable:(NSString *)attribute;
- (void)accessibilitySetValue:(id)value forAttribute:(NSString *)attribute;

// action methods
- (NSArray *)accessibilityActionNames;
- (NSString *)accessibilityActionDescription:(NSString *)action;
- (void)accessibilityPerformAction:(NSString *)action;

// Return YES if the UIElement doesn't show up to the outside world - i.e. its parent should return the UIElement's children as its own - cutting the UIElement out. E.g. NSControls are ignored when they are single-celled.
- (BOOL)accessibilityIsIgnored;

// Returns the deepest descendant of the UIElement hierarchy that contains the point. You can assume the point has already been determined to lie within the receiver. Override this method to do deeper hit testing within a UIElement - e.g. a NSMatrix would test its cells. The point is bottom-left relative screen coordinates.
- (id)accessibilityHitTest:(NSPoint)point;

// Returns the UI Element that has the focus. You can assume that the search for the focus has already been narrowed down to the reciever. Override this method to do a deeper search with a UIElement - e.g. a NSMatrix would determine if one of its cells has the focus.
- (id)accessibilityFocusedUIElement;

@end


//
// Ignored UIElements Utilities
//

APPKIT_EXTERN id NSAccessibilityUnignoredAncestor(id element);
APPKIT_EXTERN id NSAccessibilityUnignoredDescendant(id element);
APPKIT_EXTERN NSArray *NSAccessibilityUnignoredChildren(NSArray *originalChildren);
APPKIT_EXTERN NSArray *NSAccessibilityUnignoredChildrenForOnlyChild(id originalChild);


//
// Posting Notifications
//

// Posts a notification about element to anyone registered on element.
APPKIT_EXTERN void NSAccessibilityPostNotification(id element, NSString *notification);


//
// Exception Constants
//

// name for accessibility exception - declared in NSErrors.h
// APPKIT_EXTERN NSString *NSAccessibilityException;

// userInfo key for error codes in accessibility exceptions
APPKIT_EXTERN NSString *const NSAccessibilityErrorCodeExceptionInfo;


//
// Accessibility Constants
//

// standard attributes
APPKIT_EXTERN NSString *const NSAccessibilityRoleAttribute;		//(NSString *) - type, non-localized (e.g. radioButton)
APPKIT_EXTERN NSString *const NSAccessibilityRoleDescriptionAttribute;	//(NSString *) - user readable role (e.g. "radio button")
APPKIT_EXTERN NSString *const NSAccessibilitySubroleAttribute;		//(NSString *) - type, non-localized (e.g. closeButton)
APPKIT_EXTERN NSString *const NSAccessibilityHelpAttribute;		//(NSString *) - instance description (e.g. a tool tip) 
APPKIT_EXTERN NSString *const NSAccessibilityTitleAttribute;		//(NSString *) - annotation (e.g. text of a push button)
APPKIT_EXTERN NSString *const NSAccessibilityValueAttribute;		//(id)         - element's value
APPKIT_EXTERN NSString *const NSAccessibilityMinValueAttribute;		//(id)         - element's min value
APPKIT_EXTERN NSString *const NSAccessibilityMaxValueAttribute;		//(id)         - element's max value
APPKIT_EXTERN NSString *const NSAccessibilityEnabledAttribute;		//(NSNumber *) - (boolValue) responds to user?
APPKIT_EXTERN NSString *const NSAccessibilityFocusedAttribute;		//(NSNumber *) - (boolValue) has keyboard focus?
APPKIT_EXTERN NSString *const NSAccessibilityParentAttribute;		//(id)         - element containing you
APPKIT_EXTERN NSString *const NSAccessibilityChildrenAttribute;		//(NSArray *)  - elements you contain
APPKIT_EXTERN NSString *const NSAccessibilityWindowAttribute;		//(id)         - UIElement for the containing window
APPKIT_EXTERN NSString *const NSAccessibilitySelectedChildrenAttribute;	//(NSArray *)  - child elements which are selected
APPKIT_EXTERN NSString *const NSAccessibilityVisibleChildrenAttribute;	//(NSArray *)  - child elements which are visible
APPKIT_EXTERN NSString *const NSAccessibilityPositionAttribute;		//(NSValue *)  - (pointValue) position in screen coords
APPKIT_EXTERN NSString *const NSAccessibilitySizeAttribute;		//(NSValue *)  - (sizeValue) size
APPKIT_EXTERN NSString *const NSAccessibilityContentsAttribute;		//(NSArray *)   - main elements
APPKIT_EXTERN NSString *const NSAccessibilityPreviousContentsAttribute;	//(NSArray *)   - main elements
APPKIT_EXTERN NSString *const NSAccessibilityNextContentsAttribute;	//(NSArray *)   - main elements

// text specific attributes
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextAttribute;	//(NSString *) - currently selected text
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextRangeAttribute;//(NSValue *)  - (rangeValue) range of currently selectd text

// window specific attributes
APPKIT_EXTERN NSString *const NSAccessibilityMainAttribute;		//(NSNumber *) - (boolValue) is it the main window?
APPKIT_EXTERN NSString *const NSAccessibilityMinimizedAttribute;	//(NSNumber *) - (boolValue) is window minimized?
APPKIT_EXTERN NSString *const NSAccessibilityCloseButtonAttribute;	//(id) - UIElement for close box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityZoomButtonAttribute;	//(id) - UIElement for zoom box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityMinimizeButtonAttribute;	//(id) - UIElement for miniaturize box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityToolbarButtonAttribute;	//(id) - UIElement for toolbar box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityProxyAttribute;		//(id) - UIElement for title's icon (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityGrowAreaAttribute;		//(id) - UIElement for grow box (or nil)

// application specific attributes
APPKIT_EXTERN NSString *const NSAccessibilityMenuBarAttribute;		//(id)         - UIElement for the menu bar
APPKIT_EXTERN NSString *const NSAccessibilityWindowsAttribute;		//(NSArray *)  - UIElements for the windows
APPKIT_EXTERN NSString *const NSAccessibilityFrontmostAttribute;	//(NSNumber *) - (boolValue) is the app active?
APPKIT_EXTERN NSString *const NSAccessibilityHiddenAttribute;		//(NSNumber *) - (boolValue) is the app hidden?
APPKIT_EXTERN NSString *const NSAccessibilityMainWindowAttribute;	//(id)         - UIElement for the main window.
APPKIT_EXTERN NSString *const NSAccessibilityFocusedWindowAttribute;	//(id)         - UIElement for the key window.
APPKIT_EXTERN NSString *const NSAccessibilityFocusedUIElementAttribute;	//(id)         - Currently focused UIElement.

// misc attributes
APPKIT_EXTERN NSString *const NSAccessibilityHeaderAttribute;		//(id)         - UIElement for header.
APPKIT_EXTERN NSString *const NSAccessibilityEditedAttribute;		//(NSNumber *) - (boolValue) is it dirty?
APPKIT_EXTERN NSString *const NSAccessibilityTabsAttribute;		//(NSArray *)  - UIElements for tabs
APPKIT_EXTERN NSString *const NSAccessibilityTitleUIElementAttribute;	//(id)         - UIElement for the title
APPKIT_EXTERN NSString *const NSAccessibilityHorizontalScrollBarAttribute;//(id)       - UIElement for the horizontal scroller
APPKIT_EXTERN NSString *const NSAccessibilityVerticalScrollBarAttribute;//(id)         - UIElement for the vertical scroller
APPKIT_EXTERN NSString *const NSAccessibilityOverflowButtonAttribute;	//(id)         - UIElement for overflow
APPKIT_EXTERN NSString *const NSAccessibilityIncrementButtonAttribute;	//(id)         - UIElement for increment
APPKIT_EXTERN NSString *const NSAccessibilityDecrementButtonAttribute;	//(id)         - UIElement for decrement
APPKIT_EXTERN NSString *const NSAccessibilityFilenameAttribute;		//(NSString *) - filename
APPKIT_EXTERN NSString *const NSAccessibilityExpandedAttribute;		//(NSNumber *) - (boolValue) in expanded state?
APPKIT_EXTERN NSString *const NSAccessibilitySelectedAttribute;		//(NSNumber *) - (boolValue) is selected?
APPKIT_EXTERN NSString *const NSAccessibilityColumnTitlesAttribute;	//(NSArray *)  - UIElements for titles
APPKIT_EXTERN NSString *const NSAccessibilitySplittersAttribute;	//(NSArray *)  - UIElements for splitters
APPKIT_EXTERN NSString *const NSAccessibilityDocumentAttribute;		//(NSString *) - url for open document

APPKIT_EXTERN NSString *const NSAccessibilityOrientationAttribute;	//(NSString *) - NSAccessibilityXXXOrientation
APPKIT_EXTERN NSString *const NSAccessibilityVerticalOrientationValue;
APPKIT_EXTERN NSString *const NSAccessibilityHorizontalOrientationValue;


// table/outline view attributes
APPKIT_EXTERN NSString *const NSAccessibilityRowsAttribute;		//(NSArray *)  - UIElements for rows
APPKIT_EXTERN NSString *const NSAccessibilityVisibleRowsAttribute;	//(NSArray *)  - UIElements for visible rows
APPKIT_EXTERN NSString *const NSAccessibilitySelectedRowsAttribute;	//(NSArray *)  - UIElements for selected rows
APPKIT_EXTERN NSString *const NSAccessibilityColumnsAttribute;		//(NSArray *)  - UIElements for columns
APPKIT_EXTERN NSString *const NSAccessibilityVisibleColumnsAttribute;	//(NSArray *)  - UIElements for visible columns
APPKIT_EXTERN NSString *const NSAccessibilitySelectedColumnsAttribute;	//(NSArray *)  - UIElements for selected columns
APPKIT_EXTERN NSString *const NSAccessibilitySortDirectionAttribute;	//(???)

// outline attributes
APPKIT_EXTERN NSString *const NSAccessibilityDisclosingAttribute;	//(NSNumber *) - (boolValue) is diclosing rows?
APPKIT_EXTERN NSString *const NSAccessibilityDisclosedRowsAttribute;	//(NSArray *)  - UIElements for disclosed rows
APPKIT_EXTERN NSString *const NSAccessibilityDisclosedByRowAttribute;	//(id)         - UIElement for disclosing row


// actions
APPKIT_EXTERN NSString *const NSAccessibilityPressAction;
APPKIT_EXTERN NSString *const NSAccessibilityIncrementAction;
APPKIT_EXTERN NSString *const NSAccessibilityDecrementAction;
APPKIT_EXTERN NSString *const NSAccessibilityConfirmAction;
APPKIT_EXTERN NSString *const NSAccessibilityPickAction;


// focus notifications
APPKIT_EXTERN NSString *const NSAccessibilityMainWindowChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityFocusedWindowChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityFocusedUIElementChangedNotification;

// application notifications
APPKIT_EXTERN NSString *const NSAccessibilityApplicationActivatedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityApplicationDeactivatedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityApplicationHiddenNotification;
APPKIT_EXTERN NSString *const NSAccessibilityApplicationShownNotification;

// window notifications
APPKIT_EXTERN NSString *const NSAccessibilityWindowCreatedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityWindowMovedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityWindowResizedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityWindowMiniaturizedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityWindowDeminiaturizedNotification;

// element notifications
APPKIT_EXTERN NSString *const NSAccessibilityValueChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityUIElementDestroyedNotification;

// roles
APPKIT_EXTERN NSString *const NSAccessibilityUnknownRole;
APPKIT_EXTERN NSString *const NSAccessibilityButtonRole;
APPKIT_EXTERN NSString *const NSAccessibilityRadioButtonRole;
APPKIT_EXTERN NSString *const NSAccessibilityCheckBoxRole;
APPKIT_EXTERN NSString *const NSAccessibilitySliderRole;
APPKIT_EXTERN NSString *const NSAccessibilityTabGroupRole;
APPKIT_EXTERN NSString *const NSAccessibilityTextFieldRole;
APPKIT_EXTERN NSString *const NSAccessibilityStaticTextRole;
APPKIT_EXTERN NSString *const NSAccessibilityTextAreaRole;
APPKIT_EXTERN NSString *const NSAccessibilityScrollAreaRole;
APPKIT_EXTERN NSString *const NSAccessibilityPopUpButtonRole;
APPKIT_EXTERN NSString *const NSAccessibilityMenuButtonRole;
APPKIT_EXTERN NSString *const NSAccessibilityTableRole;
APPKIT_EXTERN NSString *const NSAccessibilityApplicationRole;
APPKIT_EXTERN NSString *const NSAccessibilityGroupRole;
APPKIT_EXTERN NSString *const NSAccessibilityRadioGroupRole;
APPKIT_EXTERN NSString *const NSAccessibilityListRole;
APPKIT_EXTERN NSString *const NSAccessibilityScrollBarRole;
APPKIT_EXTERN NSString *const NSAccessibilityValueIndicatorRole;
APPKIT_EXTERN NSString *const NSAccessibilityImageRole;
APPKIT_EXTERN NSString *const NSAccessibilityMenuBarRole;
APPKIT_EXTERN NSString *const NSAccessibilityMenuRole;
APPKIT_EXTERN NSString *const NSAccessibilityMenuItemRole;
APPKIT_EXTERN NSString *const NSAccessibilityColumnRole;
APPKIT_EXTERN NSString *const NSAccessibilityRowRole;
APPKIT_EXTERN NSString *const NSAccessibilityToolbarRole;
APPKIT_EXTERN NSString *const NSAccessibilityBusyIndicatorRole;
APPKIT_EXTERN NSString *const NSAccessibilityProgressIndicatorRole;
APPKIT_EXTERN NSString *const NSAccessibilityRelevanceIndicatorRole;
APPKIT_EXTERN NSString *const NSAccessibilityWindowRole;
APPKIT_EXTERN NSString *const NSAccessibilityWindowTitleRole;
APPKIT_EXTERN NSString *const NSAccessibilityWindowProxyRole;
APPKIT_EXTERN NSString *const NSAccessibilityDrawerRole;
APPKIT_EXTERN NSString *const NSAccessibilitySystemWideRole;
APPKIT_EXTERN NSString *const NSAccessibilityOutlineRole;
APPKIT_EXTERN NSString *const NSAccessibilityIncrementorRole;
APPKIT_EXTERN NSString *const NSAccessibilityBrowserRole;
APPKIT_EXTERN NSString *const NSAccessibilityComboBoxRole;
APPKIT_EXTERN NSString *const NSAccessibilitySplitGroupRole;
APPKIT_EXTERN NSString *const NSAccessibilitySplitterRole;
APPKIT_EXTERN NSString *const NSAccessibilityColorWellRole;
APPKIT_EXTERN NSString *const NSAccessibilityGrowAreaRole;
APPKIT_EXTERN NSString *const NSAccessibilitySheetRole;

// subroles
APPKIT_EXTERN NSString *const NSAccessibilityUnknownSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityCloseButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityZoomButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityMinimizeButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityToolbarButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityTableRowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityOutlineRowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilitySecureTextFieldSubrole;

#endif
