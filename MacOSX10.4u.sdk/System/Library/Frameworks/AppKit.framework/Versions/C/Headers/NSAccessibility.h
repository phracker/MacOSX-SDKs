/*
	NSAccessibility.h
	Application Kit
	Copyright (c) 2001-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <AppKit/NSErrors.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>

@class NSString, NSArray;


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

//
// Accessibility Informal Protocol
//

@interface NSObject (NSAccessibility)

// attribute methods
- (NSArray *)accessibilityAttributeNames;
- (id)accessibilityAttributeValue:(NSString *)attribute;
- (BOOL)accessibilityIsAttributeSettable:(NSString *)attribute;
- (void)accessibilitySetValue:(id)value forAttribute:(NSString *)attribute;

// parameterized attribute methods
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (NSArray *)accessibilityParameterizedAttributeNames;
- (id)accessibilityAttributeValue:(NSString *)attribute forParameter:(id)parameter;
#endif

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
// Accessibility Related Methods
//

@interface NSObject (NSAccessibilityAdditions)

// For changing the set of attributes on an instance - as an alternative to sub-classing.
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
- (BOOL)accessibilitySetOverrideValue:(id)value forAttribute:(NSString *)attribute;
#endif

@end


// Getting descriptions for standard roles and actions.
APPKIT_EXTERN NSString *NSAccessibilityRoleDescription(NSString *role, NSString *subrole)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAccessibilityRoleDescriptionForUIElement(id element)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *NSAccessibilityActionDescription(NSString *action)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


// error signaling for bad setter value or bad parameter.
APPKIT_EXTERN void NSAccessibilityRaiseBadArgumentException(id element, NSString *attribute, id value)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;


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
APPKIT_EXTERN NSString *const NSAccessibilityValueAttribute;		//(id)         - element's value
APPKIT_EXTERN NSString *const NSAccessibilityMinValueAttribute;		//(id)         - element's min value
APPKIT_EXTERN NSString *const NSAccessibilityMaxValueAttribute;		//(id)         - element's max value
APPKIT_EXTERN NSString *const NSAccessibilityEnabledAttribute;		//(NSNumber *) - (boolValue) responds to user?
APPKIT_EXTERN NSString *const NSAccessibilityFocusedAttribute;		//(NSNumber *) - (boolValue) has keyboard focus?
APPKIT_EXTERN NSString *const NSAccessibilityParentAttribute;		//(id)         - element containing you
APPKIT_EXTERN NSString *const NSAccessibilityChildrenAttribute;		//(NSArray *)  - elements you contain
APPKIT_EXTERN NSString *const NSAccessibilityWindowAttribute;		//(id)         - UIElement for the containing window
APPKIT_EXTERN NSString *const NSAccessibilityTopLevelUIElementAttribute	//(id)         - UIElement for the containing top level element
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedChildrenAttribute;	//(NSArray *)  - child elements which are selected
APPKIT_EXTERN NSString *const NSAccessibilityVisibleChildrenAttribute;	//(NSArray *)  - child elements which are visible
APPKIT_EXTERN NSString *const NSAccessibilityPositionAttribute;		//(NSValue *)  - (pointValue) position in screen coords
APPKIT_EXTERN NSString *const NSAccessibilitySizeAttribute;		//(NSValue *)  - (sizeValue) size
APPKIT_EXTERN NSString *const NSAccessibilityContentsAttribute;		//(NSArray *)  - main elements
APPKIT_EXTERN NSString *const NSAccessibilityTitleAttribute;		//(NSString *) - visible text (e.g. of a push button)
APPKIT_EXTERN NSString *const NSAccessibilityDescriptionAttribute	//(NSString *) - instance description
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityShownMenuAttribute		//(id)         - menu being displayed
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
                                                                        
// misc attributes
APPKIT_EXTERN NSString *const NSAccessibilityPreviousContentsAttribute;	//(NSArray *)  - main elements
APPKIT_EXTERN NSString *const NSAccessibilityNextContentsAttribute;	//(NSArray *)  - main elements
APPKIT_EXTERN NSString *const NSAccessibilityHeaderAttribute;		//(id)         - UIElement for header.
APPKIT_EXTERN NSString *const NSAccessibilityEditedAttribute;		//(NSNumber *) - (boolValue) is it dirty?
APPKIT_EXTERN NSString *const NSAccessibilityTabsAttribute;		//(NSArray *)  - UIElements for tabs
APPKIT_EXTERN NSString *const NSAccessibilityHorizontalScrollBarAttribute;//(id)       - UIElement for the horizontal scroller
APPKIT_EXTERN NSString *const NSAccessibilityVerticalScrollBarAttribute;//(id)         - UIElement for the vertical scroller
APPKIT_EXTERN NSString *const NSAccessibilityOverflowButtonAttribute;	//(id)         - UIElement for overflow
APPKIT_EXTERN NSString *const NSAccessibilityIncrementButtonAttribute;	//(id)         - UIElement for increment
APPKIT_EXTERN NSString *const NSAccessibilityDecrementButtonAttribute;	//(id)         - UIElement for decrement
APPKIT_EXTERN NSString *const NSAccessibilityFilenameAttribute;		//(NSString *) - filename
APPKIT_EXTERN NSString *const NSAccessibilityExpandedAttribute;		//(NSNumber *) - (boolValue) is expanded?
APPKIT_EXTERN NSString *const NSAccessibilitySelectedAttribute;		//(NSNumber *) - (boolValue) is selected?
APPKIT_EXTERN NSString *const NSAccessibilitySplittersAttribute;	//(NSArray *)  - UIElements for splitters
APPKIT_EXTERN NSString *const NSAccessibilityDocumentAttribute;		//(NSString *) - url as string - for open document
APPKIT_EXTERN NSString *const NSAccessibilityURLAttribute		//(NSURL *)    - url
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityIndexAttribute		//(NSNumber *)  - (intValue)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// linkage attributes
APPKIT_EXTERN NSString *const NSAccessibilityTitleUIElementAttribute;		//(id)	      - UIElement for the title
APPKIT_EXTERN NSString *const NSAccessibilityServesAsTitleForUIElementsAttribute//(NSArray *) - UIElements this titles
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityLinkedUIElementsAttribute		//(NSArray *) - corresponding UIElements
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


// text specific attributes
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextAttribute;		//(NSString *) - selected text
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextRangeAttribute;	//(NSValue *)  - (rangeValue) range of selected text
APPKIT_EXTERN NSString *const NSAccessibilityNumberOfCharactersAttribute	//(NSNumber *) - number of characters
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityVisibleCharacterRangeAttribute	//(NSValue *)  - (rangeValue) range of visible text
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySharedTextUIElementsAttribute	//(NSArray *)  - text views sharing text
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySharedCharacterRangeAttribute	//(NSValue *)  - (rangeValue) part of shared text in this view
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityInsertionPointLineNumberAttribute	//(NSNumber *) - line# containing caret
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
                                                                        
                                                                        
// parameterized text specific attributes
APPKIT_EXTERN NSString *const NSAccessibilityLineForIndexParameterizedAttribute		//(NSNumber *) - line# for char index; param:(NSNumber *)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityRangeForLineParameterizedAttribute		//(NSValue *)  - (rangeValue) range of line; param:(NSNumber *)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityStringForRangeParameterizedAttribute	//(NSString *) - substring; param:(NSValue * - rangeValue)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityRangeForPositionParameterizedAttribute	//(NSValue *)  - (rangeValue) composed char range; param:(NSValue * - pointValue)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityRangeForIndexParameterizedAttribute	//(NSValue *)  - (rangeValue) composed char range; param:(NSNumber *)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityBoundsForRangeParameterizedAttribute	//(NSValue *)  - (rectValue) bounds of text; param:(NSValue * - rangeValue)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityRTFForRangeParameterizedAttribute		//(NSData *)   - rtf for text; param:(NSValue * - rangeValue)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityStyleRangeForIndexParameterizedAttribute	//(NSValue *)  - (rangeValue) extent of style run; param:(NSNumber *)
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityAttributedStringForRangeParameterizedAttribute //(NSAttributedString *) - does _not_ use attributes from Appkit/AttributedString.h
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
                                                                                

// text attributed string attributes and constants
APPKIT_EXTERN NSString *const NSAccessibilityFontTextAttribute			//(NSDictionary *)  - NSAccessibilityFontXXXKey's
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityForegroundColorTextAttribute	//CGColorRef
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityBackgroundColorTextAttribute	//CGColorRef
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityUnderlineColorTextAttribute	//CGColorRef
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityStrikethroughColorTextAttribute	//CGColorRef
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityUnderlineTextAttribute		//(NSNumber *)	    - underline style
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySuperscriptTextAttribute		//(NSNumber *)	    - superscript>0, subscript<0
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityStrikethroughTextAttribute		//(NSNumber *)	    - (boolValue)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityShadowTextAttribute		//(NSNumber *)	    - (boolValue)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityAttachmentTextAttribute		//id - corresponding element
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityLinkTextAttribute			//id - corresponding element
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityMisspelledTextAttribute		//(NSNumber *)	    - (boolValue)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
    
APPKIT_EXTERN NSString *const NSAccessibilityFontNameKey	// required
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityFontFamilyKey	// optional
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityVisibleNameKey	// optional
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityFontSizeKey	// required
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


// window specific attributes
APPKIT_EXTERN NSString *const NSAccessibilityMainAttribute;		//(NSNumber *) - (boolValue) is it the main window?
APPKIT_EXTERN NSString *const NSAccessibilityMinimizedAttribute;	//(NSNumber *) - (boolValue) is window minimized?
APPKIT_EXTERN NSString *const NSAccessibilityCloseButtonAttribute;	//(id) - UIElement for close box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityZoomButtonAttribute;	//(id) - UIElement for zoom box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityMinimizeButtonAttribute;	//(id) - UIElement for miniaturize box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityToolbarButtonAttribute;	//(id) - UIElement for toolbar box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityProxyAttribute;		//(id) - UIElement for title's icon (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityGrowAreaAttribute;		//(id) - UIElement for grow box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityModalAttribute		//(NSNumber *) - (boolValue) is the window modal
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityDefaultButtonAttribute	//(id) - UIElement for default button
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityCancelButtonAttribute	//(id) - UIElement for cancel button
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
                                                                        
// application specific attributes
APPKIT_EXTERN NSString *const NSAccessibilityMenuBarAttribute;		//(id)         - UIElement for the menu bar
APPKIT_EXTERN NSString *const NSAccessibilityWindowsAttribute;		//(NSArray *)  - UIElements for the windows
APPKIT_EXTERN NSString *const NSAccessibilityFrontmostAttribute;	//(NSNumber *) - (boolValue) is the app active?
APPKIT_EXTERN NSString *const NSAccessibilityHiddenAttribute;		//(NSNumber *) - (boolValue) is the app hidden?
APPKIT_EXTERN NSString *const NSAccessibilityMainWindowAttribute;	//(id)         - UIElement for the main window.
APPKIT_EXTERN NSString *const NSAccessibilityFocusedWindowAttribute;	//(id)         - UIElement for the key window.
APPKIT_EXTERN NSString *const NSAccessibilityFocusedUIElementAttribute;	//(id)         - Currently focused UIElement.

APPKIT_EXTERN NSString *const NSAccessibilityOrientationAttribute;	//(NSString *) - NSAccessibilityXXXOrientationValue
APPKIT_EXTERN NSString *const NSAccessibilityVerticalOrientationValue;
APPKIT_EXTERN NSString *const NSAccessibilityHorizontalOrientationValue;
APPKIT_EXTERN NSString *const NSAccessibilityColumnTitlesAttribute;	//(NSArray *)  - UIElements for titles

APPKIT_EXTERN NSString *const NSAccessibilitySearchButtonAttribute	//(id)         - UIElement for search field search btn
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySearchMenuAttribute	//(id)         - UIElement for search field menu
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityClearButtonAttribute	//(id)         - UIElement for search field clear btn
    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
									

// table/outline view attributes
APPKIT_EXTERN NSString *const NSAccessibilityRowsAttribute;		//(NSArray *)  - UIElements for rows
APPKIT_EXTERN NSString *const NSAccessibilityVisibleRowsAttribute;	//(NSArray *)  - UIElements for visible rows
APPKIT_EXTERN NSString *const NSAccessibilitySelectedRowsAttribute;	//(NSArray *)  - UIElements for selected rows
APPKIT_EXTERN NSString *const NSAccessibilityColumnsAttribute;		//(NSArray *)  - UIElements for columns
APPKIT_EXTERN NSString *const NSAccessibilityVisibleColumnsAttribute;	//(NSArray *)  - UIElements for visible columns
APPKIT_EXTERN NSString *const NSAccessibilitySelectedColumnsAttribute;	//(NSArray *)  - UIElements for selected columns
APPKIT_EXTERN NSString *const NSAccessibilitySortDirectionAttribute	//(NSString *) - see sort direction values below
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
    
// sort direction values
APPKIT_EXTERN NSString *const NSAccessibilityAscendingSortDirectionValue	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityDescendingSortDirectionValue	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityUnknownSortDirectionValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// outline attributes
APPKIT_EXTERN NSString *const NSAccessibilityDisclosingAttribute;	//(NSNumber *) - (boolValue) is diclosing rows?
APPKIT_EXTERN NSString *const NSAccessibilityDisclosedRowsAttribute;	//(NSArray *)  - UIElements for disclosed rows
APPKIT_EXTERN NSString *const NSAccessibilityDisclosedByRowAttribute;	//(id)         - UIElement for disclosing row
APPKIT_EXTERN NSString *const NSAccessibilityDisclosureLevelAttribute	//(NSNumber *) - indentation level
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// slider attributes
APPKIT_EXTERN NSString *const NSAccessibilityAllowedValuesAttribute	//(NSArray *) - array of allowed values
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityLabelUIElementsAttribute	//(NSArray *) - array of label UIElements
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityLabelValueAttribute	//(NSNumber *) - value of a label UIElement
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// matte attributes
APPKIT_EXTERN NSString *const NSAccessibilityMatteHoleAttribute		//(NSValue *) - (rect value) bounds of matte hole in screen coords
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityMatteContentUIElementAttribute //(id) - UIElement clipped by the matte
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// ruler view attributes
APPKIT_EXTERN NSString *const NSAccessibilityMarkerUIElementsAttribute		//(NSArray *)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityMarkerValuesAttribute		//
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityMarkerGroupUIElementAttribute	//(id)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityUnitsAttribute			//(NSString *) - see ruler unit values below
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityUnitDescriptionAttribute		//(NSString *)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityMarkerTypeAttribute		//(NSString *) - see ruler marker type values below
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityMarkerTypeDescriptionAttribute	//(NSString *)
    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// ruler marker type values
APPKIT_EXTERN NSString *const NSAccessibilityLeftTabStopMarkerTypeValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityRightTabStopMarkerTypeValue	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityCenterTabStopMarkerTypeValue	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityDecimalTabStopMarkerTypeValue	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityHeadIndentMarkerTypeValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityTailIndentMarkerTypeValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityFirstLineIndentMarkerTypeValue	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityUnknownMarkerTypeValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// ruler unit values
APPKIT_EXTERN NSString *const NSAccessibilityInchesUnitValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityCentimetersUnitValue	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityPointsUnitValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityPicasUnitValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityUnknownUnitValue		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// actions
APPKIT_EXTERN NSString *const NSAccessibilityPressAction;
APPKIT_EXTERN NSString *const NSAccessibilityIncrementAction;
APPKIT_EXTERN NSString *const NSAccessibilityDecrementAction;
APPKIT_EXTERN NSString *const NSAccessibilityConfirmAction;
APPKIT_EXTERN NSString *const NSAccessibilityPickAction;
APPKIT_EXTERN NSString *const NSAccessibilityCancelAction	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityRaiseAction	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityShowMenuAction	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
APPKIT_EXTERN NSString *const NSAccessibilityDeleteAction	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

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

// drawer & sheet notifications
APPKIT_EXTERN NSString *const NSAccessibilityDrawerCreatedNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySheetCreatedNotification	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

// element notifications
APPKIT_EXTERN NSString *const NSAccessibilityUIElementDestroyedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityValueChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityTitleChangedNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityResizedNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityMovedNotification			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityCreatedNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

// misc notifications
APPKIT_EXTERN NSString *const NSAccessibilityHelpTagCreatedNotification		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextChangedNotification	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityRowCountChangedNotification	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedChildrenChangedNotification    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedRowsChangedNotification	    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedColumnsChangedNotification	    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


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
APPKIT_EXTERN NSString *const NSAccessibilityWindowRole;
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
APPKIT_EXTERN NSString *const NSAccessibilityHelpTagRole	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityMatteRole		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
APPKIT_EXTERN NSString *const NSAccessibilityRulerRole		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityRulerMarkerRole	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySortButtonRole	AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityLinkRole		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


// subroles
APPKIT_EXTERN NSString *const NSAccessibilityUnknownSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityCloseButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityZoomButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityMinimizeButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityToolbarButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityTableRowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityOutlineRowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilitySecureTextFieldSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityStandardWindowSubrole		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityDialogSubrole			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySystemDialogSubrole		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityFloatingWindowSubrole		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySystemFloatingWindowSubrole	AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityIncrementArrowSubrole		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityDecrementArrowSubrole		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityIncrementPageSubrole		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityDecrementPageSubrole		AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilitySearchFieldSubrole			AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
APPKIT_EXTERN NSString *const NSAccessibilityTextAttachmentSubrole		AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 
APPKIT_EXTERN NSString *const NSAccessibilityTextLinkSubrole			AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER; 

#endif
