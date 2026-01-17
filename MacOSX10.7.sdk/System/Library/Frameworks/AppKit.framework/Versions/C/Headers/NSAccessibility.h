/*
	NSAccessibility.h
	Application Kit
	Copyright (c) 2001-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <AppKit/NSErrors.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>

@class NSString, NSArray;



/*** Accessibility Informal Protocol ***/

@interface NSObject (NSAccessibility)

/* Attribute methods
*/
- (NSArray *)accessibilityAttributeNames;
- (id)accessibilityAttributeValue:(NSString *)attribute;
- (BOOL)accessibilityIsAttributeSettable:(NSString *)attribute;
- (void)accessibilitySetValue:(id)value forAttribute:(NSString *)attribute;

/* Parameterized Attribute methods
*/
- (NSArray *)accessibilityParameterizedAttributeNames;
- (id)accessibilityAttributeValue:(NSString *)attribute forParameter:(id)parameter;

/* Accessibility action methods
*/
- (NSArray *)accessibilityActionNames;
- (NSString *)accessibilityActionDescription:(NSString *)action;
- (void)accessibilityPerformAction:(NSString *)action;

/* Return YES if the UIElement doesn't show up to the outside world - i.e. its parent should return the UIElement's children as its own - cutting the UIElement out. E.g. NSControls are ignored when they are single-celled.
*/
- (BOOL)accessibilityIsIgnored;

/* Returns the deepest descendant of the UIElement hierarchy that contains the point. You can assume the point has already been determined to lie within the receiver. Override this method to do deeper hit testing within a UIElement - e.g. a NSMatrix would test its cells. The point is bottom-left relative screen coordinates.
*/
- (id)accessibilityHitTest:(NSPoint)point;

/* Returns the UI Element that has the focus. You can assume that the search for the focus has already been narrowed down to the receiver. Override this method to do a deeper search with a UIElement - e.g. a NSMatrix would determine if one of its cells has the focus.
*/
- (id)accessibilityFocusedUIElement;


/* The following are optional methods to improve performance of accessible objects with large numbers of children or large numbers of UI Elements returned from attributes that return an array (selected children, or visible children, for instance).  The default implementation for these operations will call -accessibilityAttributeValue: to retrieve the entire array of values, and then perform the appropriate operation.  If these methods are implemented, they will be used instead.  For accessibility objects with many children, the results to these methods can sometimes be calculated without generating the entire array of children which can improve performance.
*/

/* Given an accessibility child of an object, return the index of that child in the parent.  If the provided object is not a child of the receiver, this method should return NSNotFound.
*/
- (NSUInteger)accessibilityIndexOfChild:(id)child;

/* Return the count of an accessibility array attribute.
*/
- (NSUInteger)accessibilityArrayAttributeCount:(NSString *)attribute;

/* Return a subarray of values of an accessibility array attribute.  Note this method does not take a range.  The max count is the maximum desired number of items requested by an accessibility client.  This number may be beyond the bounds of your array.
*/
- (NSArray *)accessibilityArrayAttributeValues:(NSString *)attribute index:(NSUInteger)index maxCount:(NSUInteger)maxCount;

@end


/*** Accessibility Related Methods ***/

@interface NSObject (NSAccessibilityAdditions)

/* For changing the set of attributes on an instance - as an alternative to sub-classing.
*/
- (BOOL)accessibilitySetOverrideValue:(id)value forAttribute:(NSString *)attribute;

@end


/* Getting descriptions for standard roles and actions.
*/
APPKIT_EXTERN NSString *NSAccessibilityRoleDescription(NSString *role, NSString *subrole);
APPKIT_EXTERN NSString *NSAccessibilityRoleDescriptionForUIElement(id element);
APPKIT_EXTERN NSString *NSAccessibilityActionDescription(NSString *action);


/* Error signaling for bad setter value or bad parameter.
*/
APPKIT_EXTERN void NSAccessibilityRaiseBadArgumentException(id element, NSString *attribute, id value);


/*** Ignored UIElements Utilities ***/

APPKIT_EXTERN id NSAccessibilityUnignoredAncestor(id element);
APPKIT_EXTERN id NSAccessibilityUnignoredDescendant(id element);
APPKIT_EXTERN NSArray *NSAccessibilityUnignoredChildren(NSArray *originalChildren);
APPKIT_EXTERN NSArray *NSAccessibilityUnignoredChildrenForOnlyChild(id originalChild);


/*** Posting Notifications ***/

/* Posts a notification to accessibility client observers.  Note that accessibility notifications are not NSNotifications and do not use the NSNotificationCenter mechanism.  These notifications are received by client processes using the AX API defined in <HIServices/Accessibility.h> including AXUIElement.h.

For all notifications, the observer recieves the provided notification string and the AX API representation of the provided element. 

For most notifications, the provided element is checked for observers of the provided notification.

For some notifications, the accessibility parent of the provided element is checked for observers instead.  An example is NSAccessibilityCreatedNotification.  It is impossible for a client to register to observe this notification on a new element, since the element does not exist yet.  So, the function would be called passing in the new element, and the accessibility parent of the element is automatically checked for registered observers.

The following notifications check the accessibility parent of the provided element for observers: NSAccessibilityCreatedNotification, NSAccessibilityWindowCreatedNotification, NSAccessibilityDrawerCreatedNotification, NSAccessibilitySheetCreatedNotification, NSAccessibilityHelpTagCreatedNotification, NSAccessibilityRowExpandedNotification, NSAccessibilityRowCollapsedNotification.

For another set of notifications, the NSApp instance is always the observed element.  An example is NSAccessibilityFocusedUIElementChangedNotification.  The provided element would be the element that now has focus, and the function will automatically check NSApp for registered observers.

The following notifications always check for accessibility observers of NSApp: NSAccessibilityFocusedUIElementChangedNotification, NSAccessibilityFocusedWindowChangedNotification, NSAccessibilityMainWindowChangedNotification.

The rule of thumb is that the affected element should be passed into the function (the newly created element, the newly focused element, the row that was expanded, etc.), and the function will check for observer registrations on the correct element.

*/
APPKIT_EXTERN void NSAccessibilityPostNotification(id element, NSString *notification);


/*** Exception Constants ***/

// name for accessibility exception - declared in NSErrors.h
// APPKIT_EXTERN NSString *NSAccessibilityException;

/* userInfo key for error codes in accessibility exceptions
*/
APPKIT_EXTERN NSString *const NSAccessibilityErrorCodeExceptionInfo;


/*** Accessibility Constants ***/

/* Standard attributes
*/
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
APPKIT_EXTERN NSString *const NSAccessibilityTopLevelUIElementAttribute;	//(id)         - UIElement for the containing top level element
APPKIT_EXTERN NSString *const NSAccessibilitySelectedChildrenAttribute;	//(NSArray *)  - child elements which are selected
APPKIT_EXTERN NSString *const NSAccessibilityVisibleChildrenAttribute;	//(NSArray *)  - child elements which are visible
APPKIT_EXTERN NSString *const NSAccessibilityPositionAttribute;		//(NSValue *)  - (pointValue) position in screen coords
APPKIT_EXTERN NSString *const NSAccessibilitySizeAttribute;		//(NSValue *)  - (sizeValue) size
APPKIT_EXTERN NSString *const NSAccessibilityContentsAttribute;		//(NSArray *)  - main elements
APPKIT_EXTERN NSString *const NSAccessibilityTitleAttribute;		//(NSString *) - visible text (e.g. of a push button)
APPKIT_EXTERN NSString *const NSAccessibilityDescriptionAttribute;	//(NSString *) - instance description
APPKIT_EXTERN NSString *const NSAccessibilityShownMenuAttribute;		//(id)         - menu being displayed
APPKIT_EXTERN NSString *const NSAccessibilityValueDescriptionAttribute	//(NSString *)  - text description of value
    NS_AVAILABLE_MAC(10_5);

                                                                        
/* Misc attributes
*/
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
APPKIT_EXTERN NSString *const NSAccessibilityURLAttribute;		//(NSURL *)    - url
APPKIT_EXTERN NSString *const NSAccessibilityIndexAttribute;		//(NSNumber *)  - (intValue)

APPKIT_EXTERN NSString *const NSAccessibilityRowCountAttribute		//(NSNumber *)  - (intValue) number of rows
    NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSAccessibilityColumnCountAttribute	//(NSNumber *)  - (intValue) number of columns
    NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSAccessibilityOrderedByRowAttribute	//(NSNumber *)  - (boolValue) is ordered by row?
    NS_AVAILABLE_MAC(10_5);
    
APPKIT_EXTERN NSString *const NSAccessibilityWarningValueAttribute	//(id)  - warning value of a level indicator, typically a number
    NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityCriticalValueAttribute	//(id)  - critical value of a level indicator, typically a number
    NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityPlaceholderValueAttribute	//(NSString *)  - placeholder value of a control such as a text field
    NS_AVAILABLE_MAC(10_6);

/* Linkage attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityTitleUIElementAttribute;		//(id)	      - UIElement for the title
APPKIT_EXTERN NSString *const NSAccessibilityServesAsTitleForUIElementsAttribute; //(NSArray *) - UIElements this titles
APPKIT_EXTERN NSString *const NSAccessibilityLinkedUIElementsAttribute;		//(NSArray *) - corresponding UIElements


/* Text-specific attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextAttribute;		//(NSString *) - selected text
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextRangeAttribute;	//(NSValue *)  - (rangeValue) range of selected text
APPKIT_EXTERN NSString *const NSAccessibilityNumberOfCharactersAttribute;	//(NSNumber *) - number of characters
APPKIT_EXTERN NSString *const NSAccessibilityVisibleCharacterRangeAttribute;	//(NSValue *)  - (rangeValue) range of visible text
APPKIT_EXTERN NSString *const NSAccessibilitySharedTextUIElementsAttribute;	//(NSArray *)  - text views sharing text
APPKIT_EXTERN NSString *const NSAccessibilitySharedCharacterRangeAttribute;	//(NSValue *)  - (rangeValue) part of shared text in this view
APPKIT_EXTERN NSString *const NSAccessibilityInsertionPointLineNumberAttribute;	//(NSNumber *) - line# containing caret
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextRangesAttribute	//(NSArray *) - array of NSValue (rangeValue) ranges of selected text
    NS_AVAILABLE_MAC(10_5);
                                                                        
                                                                        
/* Parameterized text-specific attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityLineForIndexParameterizedAttribute;		//(NSNumber *) - line# for char index; param:(NSNumber *)
APPKIT_EXTERN NSString *const NSAccessibilityRangeForLineParameterizedAttribute;		//(NSValue *)  - (rangeValue) range of line; param:(NSNumber *)
APPKIT_EXTERN NSString *const NSAccessibilityStringForRangeParameterizedAttribute;	//(NSString *) - substring; param:(NSValue * - rangeValue)
APPKIT_EXTERN NSString *const NSAccessibilityRangeForPositionParameterizedAttribute;	//(NSValue *)  - (rangeValue) composed char range; param:(NSValue * - pointValue)
APPKIT_EXTERN NSString *const NSAccessibilityRangeForIndexParameterizedAttribute;	//(NSValue *)  - (rangeValue) composed char range; param:(NSNumber *)
APPKIT_EXTERN NSString *const NSAccessibilityBoundsForRangeParameterizedAttribute;	//(NSValue *)  - (rectValue) bounds of text; param:(NSValue * - rangeValue)
APPKIT_EXTERN NSString *const NSAccessibilityRTFForRangeParameterizedAttribute;		//(NSData *)   - rtf for text; param:(NSValue * - rangeValue)
APPKIT_EXTERN NSString *const NSAccessibilityStyleRangeForIndexParameterizedAttribute;	//(NSValue *)  - (rangeValue) extent of style run; param:(NSNumber *)
APPKIT_EXTERN NSString *const NSAccessibilityAttributedStringForRangeParameterizedAttribute; //(NSAttributedString *) - does _not_ use attributes from Appkit/AttributedString.h
                                                                                

/* Text attributed string attributes and constants
*/
APPKIT_EXTERN NSString *const NSAccessibilityFontTextAttribute;			//(NSDictionary *)  - NSAccessibilityFontXXXKey's
APPKIT_EXTERN NSString *const NSAccessibilityForegroundColorTextAttribute;	//CGColorRef
APPKIT_EXTERN NSString *const NSAccessibilityBackgroundColorTextAttribute;	//CGColorRef
APPKIT_EXTERN NSString *const NSAccessibilityUnderlineColorTextAttribute;	//CGColorRef
APPKIT_EXTERN NSString *const NSAccessibilityStrikethroughColorTextAttribute;	//CGColorRef
APPKIT_EXTERN NSString *const NSAccessibilityUnderlineTextAttribute;		//(NSNumber *)	    - underline style
APPKIT_EXTERN NSString *const NSAccessibilitySuperscriptTextAttribute;		//(NSNumber *)	    - superscript>0, subscript<0
APPKIT_EXTERN NSString *const NSAccessibilityStrikethroughTextAttribute;		//(NSNumber *)	    - (boolValue)
APPKIT_EXTERN NSString *const NSAccessibilityShadowTextAttribute;		//(NSNumber *)	    - (boolValue)
APPKIT_EXTERN NSString *const NSAccessibilityAttachmentTextAttribute;		//id - corresponding element
APPKIT_EXTERN NSString *const NSAccessibilityLinkTextAttribute;			//id - corresponding element
APPKIT_EXTERN NSString *const NSAccessibilityMisspelledTextAttribute;		//(NSNumber *)	    - (boolValue)
APPKIT_EXTERN NSString *const NSAccessibilityAutocorrectedTextAttribute NS_AVAILABLE_MAC(10_7);		//(NSNumber *)	    - (boolValue)
    
APPKIT_EXTERN NSString *const NSAccessibilityFontNameKey;	// required
APPKIT_EXTERN NSString *const NSAccessibilityFontFamilyKey;	// optional
APPKIT_EXTERN NSString *const NSAccessibilityVisibleNameKey;	// optional
APPKIT_EXTERN NSString *const NSAccessibilityFontSizeKey;	// required


/* Window-specific attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityMainAttribute;		//(NSNumber *) - (boolValue) is it the main window?
APPKIT_EXTERN NSString *const NSAccessibilityMinimizedAttribute;	//(NSNumber *) - (boolValue) is window minimized?
APPKIT_EXTERN NSString *const NSAccessibilityCloseButtonAttribute;	//(id) - UIElement for close box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityZoomButtonAttribute;	//(id) - UIElement for zoom box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityMinimizeButtonAttribute;	//(id) - UIElement for miniaturize box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityToolbarButtonAttribute;	//(id) - UIElement for toolbar box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityProxyAttribute;		//(id) - UIElement for title's icon (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityGrowAreaAttribute;		//(id) - UIElement for grow box (or nil)
APPKIT_EXTERN NSString *const NSAccessibilityModalAttribute;		//(NSNumber *) - (boolValue) is the window modal
APPKIT_EXTERN NSString *const NSAccessibilityDefaultButtonAttribute;	//(id) - UIElement for default button
APPKIT_EXTERN NSString *const NSAccessibilityCancelButtonAttribute;	//(id) - UIElement for cancel button
APPKIT_EXTERN NSString *const NSAccessibilityFullScreenButtonAttribute NS_AVAILABLE_MAC(10_7); //(id) - UIElement for full screen button (or nil)

/* Application-specific attributes
*/
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
APPKIT_EXTERN NSString *const NSAccessibilityUnknownOrientationValue	NS_AVAILABLE_MAC(10_6);

APPKIT_EXTERN NSString *const NSAccessibilityColumnTitlesAttribute;	//(NSArray *)  - UIElements for titles

APPKIT_EXTERN NSString *const NSAccessibilitySearchButtonAttribute;	//(id)         - UIElement for search field search btn
APPKIT_EXTERN NSString *const NSAccessibilitySearchMenuAttribute;	//(id)         - UIElement for search field menu
APPKIT_EXTERN NSString *const NSAccessibilityClearButtonAttribute;	//(id)         - UIElement for search field clear btn
									

/* Table/outline view attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityRowsAttribute;		//(NSArray *)  - UIElements for rows
APPKIT_EXTERN NSString *const NSAccessibilityVisibleRowsAttribute;	//(NSArray *)  - UIElements for visible rows
APPKIT_EXTERN NSString *const NSAccessibilitySelectedRowsAttribute;	//(NSArray *)  - UIElements for selected rows
APPKIT_EXTERN NSString *const NSAccessibilityColumnsAttribute;		//(NSArray *)  - UIElements for columns
APPKIT_EXTERN NSString *const NSAccessibilityVisibleColumnsAttribute;	//(NSArray *)  - UIElements for visible columns
APPKIT_EXTERN NSString *const NSAccessibilitySelectedColumnsAttribute;	//(NSArray *)  - UIElements for selected columns
APPKIT_EXTERN NSString *const NSAccessibilitySortDirectionAttribute;	//(NSString *) - see sort direction values below
    
/* Cell-based table attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilitySelectedCellsAttribute NS_AVAILABLE_MAC(10_6);	//(NSArray *)  - UIElements for selected cells
APPKIT_EXTERN NSString *const NSAccessibilityVisibleCellsAttribute NS_AVAILABLE_MAC(10_6);	//(NSArray *)  - UIElements for visible cells
APPKIT_EXTERN NSString *const NSAccessibilityRowHeaderUIElementsAttribute NS_AVAILABLE_MAC(10_6);	//(NSArray *)  - UIElements for row headers
APPKIT_EXTERN NSString *const NSAccessibilityColumnHeaderUIElementsAttribute NS_AVAILABLE_MAC(10_6);	//(NSArray *)  - UIElements for column headers

/* Cell-based table parameterized attributes.  The parameter for this attribute is an NSArray containing two NSNumbers, the first NSNumber specifies the column index, the second NSNumber specifies the row index.
*/
APPKIT_EXTERN NSString *const NSAccessibilityCellForColumnAndRowParameterizedAttribute NS_AVAILABLE_MAC(10_6);  // (id) - UIElement for cell at specified row and column

/* Cell attributes.  The index range contains both the starting index, and the index span in a table.
*/
APPKIT_EXTERN NSString *const NSAccessibilityRowIndexRangeAttribute NS_AVAILABLE_MAC(10_6);	//(NSValue *)  - (rangeValue) location and row span
APPKIT_EXTERN NSString *const NSAccessibilityColumnIndexRangeAttribute NS_AVAILABLE_MAC(10_6);   //(NSValue *)  - (rangeValue) location and column span

/* Layout area attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityHorizontalUnitsAttribute NS_AVAILABLE_MAC(10_6);   //(NSString *) - see ruler unit values below
APPKIT_EXTERN NSString *const NSAccessibilityVerticalUnitsAttribute NS_AVAILABLE_MAC(10_6);	    //(NSString *) - see ruler unit values below
APPKIT_EXTERN NSString *const NSAccessibilityHorizontalUnitDescriptionAttribute NS_AVAILABLE_MAC(10_6); //(NSString *)
APPKIT_EXTERN NSString *const NSAccessibilityVerticalUnitDescriptionAttribute NS_AVAILABLE_MAC(10_6);    //(NSString *)

/* Layout area parameterized attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityLayoutPointForScreenPointParameterizedAttribute NS_AVAILABLE_MAC(10_6); //(NSValue *)  - (pointValue); param:(NSValue * - pointValue)
APPKIT_EXTERN NSString *const NSAccessibilityLayoutSizeForScreenSizeParameterizedAttribute NS_AVAILABLE_MAC(10_6); //(NSValue *)  - (sizeValue); param:(NSValue * - sizeValue)
APPKIT_EXTERN NSString *const NSAccessibilityScreenPointForLayoutPointParameterizedAttribute NS_AVAILABLE_MAC(10_6); //(NSValue *)  - (pointValue); param:(NSValue * - pointValue)
APPKIT_EXTERN NSString *const NSAccessibilityScreenSizeForLayoutSizeParameterizedAttribute NS_AVAILABLE_MAC(10_6); //(NSValue *)  - (sizeValue); param:(NSValue * - sizeValue)

/* Layout item attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityHandlesAttribute NS_AVAILABLE_MAC(10_6); //(NSArray *)  - UIElements for handles
    
/* Sort direction values
*/
APPKIT_EXTERN NSString *const NSAccessibilityAscendingSortDirectionValue;
APPKIT_EXTERN NSString *const NSAccessibilityDescendingSortDirectionValue;
APPKIT_EXTERN NSString *const NSAccessibilityUnknownSortDirectionValue;

/* Outline attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityDisclosingAttribute;	//(NSNumber *) - (boolValue) is disclosing rows?
APPKIT_EXTERN NSString *const NSAccessibilityDisclosedRowsAttribute;	//(NSArray *)  - UIElements for disclosed rows
APPKIT_EXTERN NSString *const NSAccessibilityDisclosedByRowAttribute;	//(id)         - UIElement for disclosing row
APPKIT_EXTERN NSString *const NSAccessibilityDisclosureLevelAttribute;	//(NSNumber *) - indentation level

/* Slider attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityAllowedValuesAttribute;	//(NSArray *) - array of allowed values
APPKIT_EXTERN NSString *const NSAccessibilityLabelUIElementsAttribute;	//(NSArray *) - array of label UIElements
APPKIT_EXTERN NSString *const NSAccessibilityLabelValueAttribute;	//(NSNumber *) - value of a label UIElement

/* Matte attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityMatteHoleAttribute;		//(NSValue *) - (rect value) bounds of matte hole in screen coords
APPKIT_EXTERN NSString *const NSAccessibilityMatteContentUIElementAttribute; //(id) - UIElement clipped by the matte

/* Ruler view attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityMarkerUIElementsAttribute;		//(NSArray *)
APPKIT_EXTERN NSString *const NSAccessibilityMarkerValuesAttribute;		//
APPKIT_EXTERN NSString *const NSAccessibilityMarkerGroupUIElementAttribute;	//(id)
APPKIT_EXTERN NSString *const NSAccessibilityUnitsAttribute;			//(NSString *) - see ruler unit values below
APPKIT_EXTERN NSString *const NSAccessibilityUnitDescriptionAttribute;		//(NSString *)
APPKIT_EXTERN NSString *const NSAccessibilityMarkerTypeAttribute;		//(NSString *) - see ruler marker type values below
APPKIT_EXTERN NSString *const NSAccessibilityMarkerTypeDescriptionAttribute;	//(NSString *)

/* UI element identification attributes
*/
APPKIT_EXTERN NSString *const NSAccessibilityIdentifierAttribute		//(NSString *)
    NS_AVAILABLE_MAC(10_7);

/* Ruler marker type values
*/
APPKIT_EXTERN NSString *const NSAccessibilityLeftTabStopMarkerTypeValue;
APPKIT_EXTERN NSString *const NSAccessibilityRightTabStopMarkerTypeValue;
APPKIT_EXTERN NSString *const NSAccessibilityCenterTabStopMarkerTypeValue;
APPKIT_EXTERN NSString *const NSAccessibilityDecimalTabStopMarkerTypeValue;
APPKIT_EXTERN NSString *const NSAccessibilityHeadIndentMarkerTypeValue;
APPKIT_EXTERN NSString *const NSAccessibilityTailIndentMarkerTypeValue;
APPKIT_EXTERN NSString *const NSAccessibilityFirstLineIndentMarkerTypeValue;
APPKIT_EXTERN NSString *const NSAccessibilityUnknownMarkerTypeValue;

/* Ruler unit values
*/
APPKIT_EXTERN NSString *const NSAccessibilityInchesUnitValue;
APPKIT_EXTERN NSString *const NSAccessibilityCentimetersUnitValue;
APPKIT_EXTERN NSString *const NSAccessibilityPointsUnitValue;
APPKIT_EXTERN NSString *const NSAccessibilityPicasUnitValue;
APPKIT_EXTERN NSString *const NSAccessibilityUnknownUnitValue;

/* Actions
*/
APPKIT_EXTERN NSString *const NSAccessibilityPressAction;
APPKIT_EXTERN NSString *const NSAccessibilityIncrementAction;
APPKIT_EXTERN NSString *const NSAccessibilityDecrementAction;
APPKIT_EXTERN NSString *const NSAccessibilityConfirmAction;
APPKIT_EXTERN NSString *const NSAccessibilityPickAction;
APPKIT_EXTERN NSString *const NSAccessibilityCancelAction;
APPKIT_EXTERN NSString *const NSAccessibilityRaiseAction;
APPKIT_EXTERN NSString *const NSAccessibilityShowMenuAction; 
APPKIT_EXTERN NSString *const NSAccessibilityDeleteAction; 

/* Focus notifications
*/
APPKIT_EXTERN NSString *const NSAccessibilityMainWindowChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityFocusedWindowChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityFocusedUIElementChangedNotification;

/* Application notifications
*/
APPKIT_EXTERN NSString *const NSAccessibilityApplicationActivatedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityApplicationDeactivatedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityApplicationHiddenNotification;
APPKIT_EXTERN NSString *const NSAccessibilityApplicationShownNotification;

/* Window notifications
*/
APPKIT_EXTERN NSString *const NSAccessibilityWindowCreatedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityWindowMovedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityWindowResizedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityWindowMiniaturizedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityWindowDeminiaturizedNotification;

/* Drawer & sheet notifications
*/
APPKIT_EXTERN NSString *const NSAccessibilityDrawerCreatedNotification;
APPKIT_EXTERN NSString *const NSAccessibilitySheetCreatedNotification;

/* Element notifications
*/
APPKIT_EXTERN NSString *const NSAccessibilityUIElementDestroyedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityValueChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityTitleChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityResizedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityMovedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityCreatedNotification;

/* Misc notifications
*/
APPKIT_EXTERN NSString *const NSAccessibilityHelpTagCreatedNotification;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilityRowCountChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedChildrenChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedRowsChangedNotification;
APPKIT_EXTERN NSString *const NSAccessibilitySelectedColumnsChangedNotification;

APPKIT_EXTERN NSString *const NSAccessibilityRowExpandedNotification		NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityRowCollapsedNotification		NS_AVAILABLE_MAC(10_6);

/* Cell-table notifications
*/
APPKIT_EXTERN NSString *const NSAccessibilitySelectedCellsChangedNotification NS_AVAILABLE_MAC(10_6);

/* Layout area notifications
*/
APPKIT_EXTERN NSString *const NSAccessibilityUnitsChangedNotification NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilitySelectedChildrenMovedNotification NS_AVAILABLE_MAC(10_6);


/* Roles
*/
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
APPKIT_EXTERN NSString *const NSAccessibilityHelpTagRole;
APPKIT_EXTERN NSString *const NSAccessibilityMatteRole; 
APPKIT_EXTERN NSString *const NSAccessibilityRulerRole;
APPKIT_EXTERN NSString *const NSAccessibilityRulerMarkerRole;
APPKIT_EXTERN NSString *const NSAccessibilityLinkRole;
APPKIT_EXTERN NSString *const NSAccessibilityDisclosureTriangleRole NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSAccessibilityGridRole		NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSAccessibilityRelevanceIndicatorRole;
APPKIT_EXTERN NSString *const NSAccessibilityLevelIndicatorRole NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityCellRole NS_AVAILABLE_MAC(10_6); // As found in a cell-based table
APPKIT_EXTERN NSString *const NSAccessibilityPopoverRole NS_AVAILABLE_MAC(10_7);

/* Layout-area roles
*/
APPKIT_EXTERN NSString *const NSAccessibilityLayoutAreaRole NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityLayoutItemRole NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityHandleRole NS_AVAILABLE_MAC(10_6);


/* Subroles
*/
APPKIT_EXTERN NSString *const NSAccessibilityUnknownSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityCloseButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityZoomButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityMinimizeButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityToolbarButtonSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityTableRowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityOutlineRowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilitySecureTextFieldSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityStandardWindowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityDialogSubrole;
APPKIT_EXTERN NSString *const NSAccessibilitySystemDialogSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityFloatingWindowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilitySystemFloatingWindowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityIncrementArrowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityDecrementArrowSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityIncrementPageSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityDecrementPageSubrole;
APPKIT_EXTERN NSString *const NSAccessibilitySearchFieldSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityTextAttachmentSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityTextLinkSubrole;
APPKIT_EXTERN NSString *const NSAccessibilityTimelineSubrole			NS_AVAILABLE_MAC(10_5);
APPKIT_EXTERN NSString *const NSAccessibilitySortButtonSubrole			NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityRatingIndicatorSubrole		NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityContentListSubrole			NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityDefinitionListSubrole		NS_AVAILABLE_MAC(10_6);
APPKIT_EXTERN NSString *const NSAccessibilityFullScreenButtonSubrole		NS_AVAILABLE_MAC(10_7);

/* Deprecated
*/
APPKIT_EXTERN NSString *const NSAccessibilitySortButtonRole	NS_DEPRECATED_MAC(10_4, 10_6);

