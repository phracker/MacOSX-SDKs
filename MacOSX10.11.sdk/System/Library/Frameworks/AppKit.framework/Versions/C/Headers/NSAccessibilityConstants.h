/*
	NSAccessibilityConstants.h
	Application Kit
	Copyright (c) 2001-2015, Apple Inc.
	All rights reserved.
*/
#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

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
APPKIT_EXTERN NSString *const NSAccessibilitySharedFocusElementsAttribute NS_AVAILABLE_MAC(10_10);  //(NSArray *)  - elements that share focus


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
APPKIT_EXTERN NSString *const NSAccessibilityActivationPointAttribute;           //(NSValue *)  - (pointValue)

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
APPKIT_EXTERN NSString *const NSAccessibilityContainsProtectedContentAttribute NS_AVAILABLE_MAC(10_9);   // (NSNumber *) - (boolValue) contains protected content?
APPKIT_EXTERN NSString *const NSAccessibilityAlternateUIVisibleAttribute NS_AVAILABLE_MAC(10_10);  //(NSNumber *) - (boolValue)


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
APPKIT_EXTERN NSString *const NSAccessibilitySelectedTextRangesAttribute	//(NSArray<NSValue *> *) - array of NSValue (rangeValue) ranges of selected text
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
APPKIT_EXTERN NSString *const NSAccessibilityAutocorrectedTextAttribute NS_AVAILABLE_MAC(10_7);		//(NSNumber *)	    - (boolValue)

/* Textual list attributes and constants. Examples: unordered or ordered lists in a document.
 */
APPKIT_EXTERN NSString *const NSAccessibilityListItemPrefixTextAttribute    NS_AVAILABLE_MAC(10_11);    // NSAttributedString, the prepended string of the list item. If the string is a common unicode character (e.g. a bullet •), return that unicode character. For lists with images before the text, return a reasonable label of the image.
APPKIT_EXTERN NSString *const NSAccessibilityListItemIndexTextAttribute     NS_AVAILABLE_MAC(10_11);    // NSNumber, integerValue of the line index. Each list item increments the index, even for unordered lists. The first item should have index 0.
APPKIT_EXTERN NSString *const NSAccessibilityListItemLevelTextAttribute     NS_AVAILABLE_MAC(10_11);    // NSNumber, integerValue of the indent level. Each sublist increments the level. The first item should have level 0.

/*
 About MisspelledText attributes for attribute strings:
 
 NSAccessibilityMisspelledTextAttribute was the original attribute to indicate misspelled text. In OS X 10.4, the Cocoa text system added support for NSAccessibilityMarkedMisspelledTextAttribute, which was used to indicate a word that was visibly marked as misspelled (for example, with a red squiggle underneath); the original MisspelledText attribute could also be used on text that was not visibly marked as mispelled (for example, a misspelled word that was currently being edited by the user).
 
 Typically, a screen reader only wants to vocalize what a sighted user could see, and so the MarkedMisspelledText attribute was adopted by VoiceOver to provide feedback to the user about misspelled text. In OS X 10.9, VoiceOver has entirely stopped using the original MisspelledText attribute, and now only checks for MarkedMisspelledText.
 
 When implementing accessibility for a custom text-editing engine, you should generally provide the MarkedMisspelledText attribute in order to support VoiceOver, especially in OS X 10.9 and later. You may optionally also support the MisspelledText attribute for compatibility with other accessibility clients.
 */
APPKIT_EXTERN NSString *const NSAccessibilityMisspelledTextAttribute;		//(NSNumber *)	    - (boolValue)
APPKIT_EXTERN NSString *const NSAccessibilityMarkedMisspelledTextAttribute NS_AVAILABLE_MAC(10_4);	//(NSNumber *) - (boolValue)

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
APPKIT_EXTERN NSString *const NSAccessibilityExtrasMenuBarAttribute NS_AVAILABLE_MAC(10_8);    //(id)         - UIElement for the application extras menu bar.

typedef NS_ENUM(NSInteger, NSAccessibilityOrientation) {
    NSAccessibilityOrientationUnknown = 0,
    NSAccessibilityOrientationVertical = 1,
    NSAccessibilityOrientationHorizontal = 2,
} NS_ENUM_AVAILABLE_MAC(10_10);

APPKIT_EXTERN NSString *const NSAccessibilityOrientationAttribute;	//(NSString *) - NSAccessibilityXXXOrientationValue
APPKIT_EXTERN NSString *const NSAccessibilityVerticalOrientationValue;
APPKIT_EXTERN NSString *const NSAccessibilityHorizontalOrientationValue;
APPKIT_EXTERN NSString *const NSAccessibilityUnknownOrientationValue;


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

typedef NS_ENUM(NSInteger, NSAccessibilitySortDirection) {
    NSAccessibilitySortDirectionUnknown = 0,
    NSAccessibilitySortDirectionAscending = 1,
    NSAccessibilitySortDirectionDescending = 2,
} NS_ENUM_AVAILABLE_MAC(10_10);

/* Outline attributes
 */
APPKIT_EXTERN NSString *const NSAccessibilityDisclosingAttribute;	//(NSNumber *) - (boolValue) is disclosing rows?
APPKIT_EXTERN NSString *const NSAccessibilityDisclosedRowsAttribute;	//(NSArray *)  - UIElements for disclosed rows
APPKIT_EXTERN NSString *const NSAccessibilityDisclosedByRowAttribute;	//(id)         - UIElement for disclosing row
APPKIT_EXTERN NSString *const NSAccessibilityDisclosureLevelAttribute;	//(NSNumber *) - indentation level

/* Slider attributes
 */
APPKIT_EXTERN NSString *const NSAccessibilityAllowedValuesAttribute;	//(NSArray<NSNumber *> *) - array of allowed values
APPKIT_EXTERN NSString *const NSAccessibilityLabelUIElementsAttribute;	//(NSArray *) - array of label UIElements
APPKIT_EXTERN NSString *const NSAccessibilityLabelValueAttribute;	//(NSNumber *) - value of a label UIElement

/* Matte attributes
 */
// Attributes no longer supported
APPKIT_EXTERN NSString *const NSAccessibilityMatteHoleAttribute NS_DEPRECATED_MAC(10_1, 10_10);		//(NSValue *) - (rect value) bounds of matte hole in screen coords
APPKIT_EXTERN NSString *const NSAccessibilityMatteContentUIElementAttribute NS_DEPRECATED_MAC(10_1, 10_10); //(id) - UIElement clipped by the matte

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

typedef NS_ENUM(NSInteger, NSAccessibilityRulerMarkerType) {
    NSAccessibilityRulerMarkerTypeUnknown = 0,
    NSAccessibilityRulerMarkerTypeTabStopLeft = 1,
    NSAccessibilityRulerMarkerTypeTabStopRight = 2,
    NSAccessibilityRulerMarkerTypeTabStopCenter = 3,
    NSAccessibilityRulerMarkerTypeTabStopDecimal = 4,
    NSAccessibilityRulerMarkerTypeIndentHead = 5,
    NSAccessibilityRulerMarkerTypeIndentTail = 6,
    NSAccessibilityRulerMarkerTypeIndentFirstLine = 7
} NS_ENUM_AVAILABLE_MAC(10_10);

/* Ruler unit values
 */
APPKIT_EXTERN NSString *const NSAccessibilityInchesUnitValue;
APPKIT_EXTERN NSString *const NSAccessibilityCentimetersUnitValue;
APPKIT_EXTERN NSString *const NSAccessibilityPointsUnitValue;
APPKIT_EXTERN NSString *const NSAccessibilityPicasUnitValue;
APPKIT_EXTERN NSString *const NSAccessibilityUnknownUnitValue;

typedef NS_ENUM(NSInteger, NSAccessibilityUnits) {
    NSAccessibilityUnitsUnknown = 0,
    NSAccessibilityUnitsInches = 1,
    NSAccessibilityUnitsCentimeters = 2,
    NSAccessibilityUnitsPoints = 3,
    NSAccessibilityUnitsPicas = 4
} NS_ENUM_AVAILABLE_MAC(10_10);

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

/* Actions that allow the developer to present either alternative or original UI. There may be new UI elements that appear. There may be UI elements that disappear. There may be changes to existing UI elements. Or a combination of them. Currently this is typically seen during a mouse hovering event.
 */
APPKIT_EXTERN NSString *const NSAccessibilityShowAlternateUIAction	NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString *const NSAccessibilityShowDefaultUIAction	NS_AVAILABLE_MAC(10_9);

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

/* Used when UI changes require the attention of assistive application.  Pass along a user info dictionary with the key NSAccessibilityUIElementsKey and an array of elements that have been added or changed as a result of this layout change.
 */
APPKIT_EXTERN NSString *const NSAccessibilityLayoutChangedNotification	NS_AVAILABLE_MAC(10_9);

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

/* This notification allows an application to request that an announcement be made to the user by an assistive application such as VoiceOver.  The notification requires a user info dictionary with the key NSAccessibilityAnnouncementKey and the announcement as a localized string.  In addition, the key NSAccessibilityAnnouncementPriorityKey should also be used to help an assistive application determine the importance of this announcement.  This notification should be posted for the application element.
 */
APPKIT_EXTERN NSString *const NSAccessibilityAnnouncementRequestedNotification NS_AVAILABLE_MAC(10_7);


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
APPKIT_EXTERN NSString *const NSAccessibilityToggleSubrole                      NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString *const NSAccessibilitySwitchSubrole                      NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString *const NSAccessibilityDescriptionListSubrole		NS_AVAILABLE_MAC(10_9);



/* This function allows an accessibility notification to be posted with a user info dictionary.  The user info dictionary can be nil.  Valid contents of the user info dictionary are limited to classes which can be returned to an accessibility client.  That list currently includes NSString, NSNumber, NSArray, NSValues of points, ranges, sizes, rects, and valid NSAccessibility objects.  Most accessibility notifications do not require a user info dictionary.
 */
APPKIT_EXTERN void NSAccessibilityPostNotificationWithUserInfo(id element, NSString *notification, NSDictionary *userInfo) NS_AVAILABLE_MAC(10_7);


/* Below are keys used for the user info dictionary of the NSAccessibilityPostNotificationWithUserInfo API */

/* Key used in the user info dictionary for notifications.  The value is an array of elements that is associated with the notification.  For example, a NSAccessibilityLayoutChangedNotification should include an array of elements that have been added/changed using this key.
 */
APPKIT_EXTERN NSString *const NSAccessibilityUIElementsKey		NS_AVAILABLE_MAC(10_9);

/* Key used in the user info dictionary for any relevant notification.  This gives the assistive application client an opportunity to determine how to handle the corresponding notification based on the priority.  For example, a developer should pass the priority key for NSAccessibilityAnnouncementRequestedNotification.  Then clients such as VoiceOver can decide to speak the announcement immediately or after the current speech is completed based on the priority level.  This key is required for NSAccessibilityAnnouncementRequestedNotification.  The NSAccessibilityLayoutChangedNotification is another example where priority can help assistive applications determine how to handle the UI change.
 */
APPKIT_EXTERN NSString *const NSAccessibilityPriorityKey		NS_AVAILABLE_MAC(10_9);

/* Key used in the user info dictionary sent with the NSAccessibilityAnnouncementRequestedNotification.  The value for the announcement should be a localized string.  This should generally be used in conjunction with the NSAccessibilityPriorityKey to help assistive applications determine the importance of this announcement.
 */
APPKIT_EXTERN NSString *const NSAccessibilityAnnouncementKey            NS_AVAILABLE_MAC(10_7);


/* System defined priority levels.  This priority level should be included for every NSAccessibilityAnnouncementRequestedNotification.
 */
typedef NS_ENUM(NSInteger, NSAccessibilityPriorityLevel) {
    NSAccessibilityPriorityLow = 10,
    NSAccessibilityPriorityMedium = 50,
    NSAccessibilityPriorityHigh = 90
} NS_ENUM_AVAILABLE_MAC(10_9);


/* Deprecated
 */
APPKIT_EXTERN NSString *const NSAccessibilitySortButtonRole	NS_DEPRECATED_MAC(10_4, 10_6);

NS_ASSUME_NONNULL_END
