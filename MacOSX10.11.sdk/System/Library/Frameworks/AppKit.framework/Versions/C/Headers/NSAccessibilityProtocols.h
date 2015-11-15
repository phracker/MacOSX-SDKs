/*
 NSAccessibilityProtocols.h
 Application Kit
 Copyright (c) 2013-2015, Apple Inc.
 All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <AppKit/NSAccessibilityConstants.h>


NS_ASSUME_NONNULL_BEGIN

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityElement <NSObject>
@required
- (NSRect)accessibilityFrame;
- (nullable id)accessibilityParent;

@optional
- (BOOL)isAccessibilityFocused;
- (NSString *)accessibilityIdentifier;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityGroup <NSAccessibilityElement>
@end

#pragma mark Buttons

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityButton <NSAccessibilityElement>
@required
- (nullable NSString *)accessibilityLabel;
- (BOOL)accessibilityPerformPress;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilitySwitch <NSAccessibilityButton>
// Post NSAccessibilityValueChangedNotification when the value changes

@required
- (nullable NSString *)accessibilityValue;

@optional
- (BOOL)accessibilityPerformIncrement;
- (BOOL)accessibilityPerformDecrement;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityRadioButton <NSAccessibilityButton>
// NSAccessibilityValueChangedNotification should be posted whenever accessibilityValue changes

@required
// Return @YES if selected, or @NO if not selected
- (nullable NSNumber *)accessibilityValue;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityCheckBox <NSAccessibilityButton>
// NSAccessibilityValueChangedNotification should be posted whenever accessibilityValue changes

@required
// Return @YES if checked, or @NO if unchecked
- (nullable NSNumber *)accessibilityValue;
@end

#pragma mark Text
NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityStaticText <NSAccessibilityElement>
@required
- (nullable NSString *)accessibilityValue;

@optional
- (nullable NSAttributedString *)accessibilityAttributedStringForRange:(NSRange)range;
- (NSRange)accessibilityVisibleCharacterRange;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityNavigableStaticText <NSAccessibilityStaticText>
@required
- (nullable NSString *)accessibilityStringForRange:(NSRange)range;
- (NSInteger)accessibilityLineForIndex:(NSInteger)index;
- (NSRange)accessibilityRangeForLine:(NSInteger)lineNumber;

// Frame is in screen coordinates. See NSAccessibilityFrameInView()
- (NSRect)accessibilityFrameForRange:(NSRange)range;
@end

#pragma mark Miscellaneous
NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityProgressIndicator <NSAccessibilityGroup>
@required
- (nullable NSNumber *)accessibilityValue;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityStepper <NSAccessibilityElement>
@required
- (nullable NSString *)accessibilityLabel;
- (BOOL)accessibilityPerformIncrement;
- (BOOL)accessibilityPerformDecrement;
@optional
// Value is a NSString or a NSNumber
- (nullable id)accessibilityValue;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilitySlider <NSAccessibilityElement>
@required
- (nullable NSString *)accessibilityLabel;
// Value is a NSString or a NSNumber
- (nullable id)accessibilityValue;
- (BOOL)accessibilityPerformIncrement;
- (BOOL)accessibilityPerformDecrement;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityImage <NSAccessibilityElement>
@required
- (nullable NSString *)accessibilityLabel;
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityContainsTransientUI <NSAccessibilityElement>
@required
- (BOOL)accessibilityPerformShowAlternateUI;
- (BOOL)accessibilityPerformShowDefaultUI;
- (BOOL)isAccessibilityAlternateUIVisible;
@end

@protocol NSAccessibilityRow;

#pragma mark Tables, Lists, Outlines
NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityTable <NSAccessibilityGroup>
@required
- (nullable NSString *)accessibilityLabel;

// An array of accessibility row elements
- (nullable NSArray<id<NSAccessibilityRow>> *)accessibilityRows;

@optional
// For tables that have a selection
// Make sure to post a selected-rows-changed notification when appropriate
// NSAccessibilityPostNotification(table, NSAccessibilitySelectedRowsChangedNotification);
- (nullable NSArray<id<NSAccessibilityRow>> *)accessibilitySelectedRows;
- (void)setAccessibilitySelectedRows:(NSArray<id<NSAccessibilityRow>> *)selectedRows;

// Advanced table accessibility
- (nullable NSArray<id<NSAccessibilityRow>> *)accessibilityVisibleRows;
- (nullable NSArray *)accessibilityColumns;
- (nullable NSArray *)accessibilityVisibleColumns;
- (nullable NSArray *)accessibilitySelectedColumns;
- (nullable NSString *)accessibilityHeaderGroup;
- (nullable NSArray *)accessibilitySelectedCells;
- (nullable NSArray *)accessibilityVisibleCells;
- (nullable NSArray *)accessibilityRowHeaderUIElements;
- (nullable NSArray *)accessibilityColumnHeaderUIElements;

@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityOutline <NSAccessibilityTable>
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityList <NSAccessibilityTable>
@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityRow <NSAccessibilityGroup>
@required
- (NSInteger)accessibilityIndex;

@optional
- (NSInteger)accessibilityDisclosureLevel;
@end

#pragma mark Layout Area (Canvas)
NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityLayoutArea <NSAccessibilityGroup>
@required
- (NSString *)accessibilityLabel;
// All of the layoutItem children
- (nullable NSArray *)accessibilityChildren;

// Selected layoutItem children
- (nullable NSArray *)accessibilitySelectedChildren;

// The focused layoutItem
- (id)accessibilityFocusedUIElement;

@end

NS_PROTOCOL_REQUIRES_EXPLICIT_IMPLEMENTATION
@protocol NSAccessibilityLayoutItem <NSAccessibilityGroup>

@optional
// For layout items that can be moved
- (void)setAccessibilityFrame:(NSRect)frame;

@end


// The complete accessibility protocol
@protocol NSAccessibility <NSObject>
@required

#pragma mark General
// Return YES if the UIElement should be exposed
@property (getter = isAccessibilityElement) BOOL accessibilityElement NS_AVAILABLE_MAC(10_10);

// The frame of the UIElement in screen coordinates. See NSAccessibilityFrameInView()
// Invokes when clients request NSAccessibilitySizeAttribute or NSAccessibilityPositionAttribute
@property NSRect accessibilityFrame NS_AVAILABLE_MAC(10_10);

// Returns YES if the element is focused (generally, accessibilityFocused is equivilent to the
// UIElement with the focus ring or selection)
// Invokes when clients request NSAccessibilityFocusedAttribute
@property (getter = isAccessibilityFocused) BOOL accessibilityFocused NS_AVAILABLE_MAC(10_10);

// Activation point for the UIElement, in screen coordinates. See NSAccessibilityPointInView()
@property NSPoint accessibilityActivationPoint NS_AVAILABLE_MAC(10_10);

// UIElement for the containing top level element
// Invokes when clients request NSAccessibilityTopLevelUIElementAttribute
@property (nullable, weak) id accessibilityTopLevelUIElement NS_AVAILABLE_MAC(10_10);

// URL of the UIElement
// Invokes when clients request NSAccessibilityURLAttribute
@property (nullable, copy) NSURL *accessibilityURL NS_AVAILABLE_MAC(10_10);

// Value of the UIElement
// Invokes when clients request NSAccessibilityValueAttribute
@property (nullable, strong) id accessibilityValue NS_AVAILABLE_MAC(10_10);

// Human-readable description of value
// Invokes when clients request NSAccessibilityValueDescriptionAttribute
@property (nullable, copy) NSString *accessibilityValueDescription NS_AVAILABLE_MAC(10_10);

// Array of child UIElement which are visible
// Invokes when clients request NSAccessibilityVisibleChildrenAttribute
@property (nullable, copy) NSArray *accessibilityVisibleChildren NS_AVAILABLE_MAC(10_10);

// Sub-role, non - localized (e.g. NSAccessibilityCloseButtonSubrole)
// Invokes when clients request NSAccessibilitySubroleAttribute
@property (nullable, copy) NSString *accessibilitySubrole NS_AVAILABLE_MAC(10_10);

// Visible text on the UIElement
// Invokes when clients request NSAccessibilityTitleAttribute
@property (nullable, copy) NSString *accessibilityTitle NS_AVAILABLE_MAC(10_10);

// UIElement for the title
// Invokes when clients request NSAccessibilityTitleUIElementAttribute
@property (nullable, weak) id accessibilityTitleUIElement NS_AVAILABLE_MAC(10_10);

// Next content UIElement
// Invokes when clients request NSAccessibilityNextContentsAttribute
@property (nullable, copy) NSArray *accessibilityNextContents NS_AVAILABLE_MAC(10_10);

// UIElement orientation
// Invokes when clients request NSAccessibilityOrientationAttribute
@property NSAccessibilityOrientation accessibilityOrientation NS_AVAILABLE_MAC(10_10);

// UIElement for overflow
// Invokes when clients request NSAccessibilityOverflowButtonAttribute
@property (nullable, strong) id accessibilityOverflowButton NS_AVAILABLE_MAC(10_10);

// Element containing this UIElement
// Invokes when clients request NSAccessibilityParentAttribute
@property (nullable, weak) id accessibilityParent NS_AVAILABLE_MAC(10_10);

// Placeholder value of a control such as a text field
// Invokes when clients request NSAccessibilityPlaceholderValueAttribute
@property (nullable, copy) NSString *accessibilityPlaceholderValue NS_AVAILABLE_MAC(10_10);

// Previous content UIElement.
// Invokes when clients request NSAccessibilityPreviousContentsAttribute
@property (nullable, copy) NSArray *accessibilityPreviousContents NS_AVAILABLE_MAC(10_10);

// Role, non - localized (e.g. NSAccessibilityRadioButtonRole)
// Invokes when clients request NSAccessibilityRoleAttribute
@property (nullable, copy) NSString *accessibilityRole NS_AVAILABLE_MAC(10_10);

// Human readable role description (e.g. "radio button");
// Invokes when clients request NSAccessibilityRoleDescriptionAttribute
@property (nullable, copy) NSString *accessibilityRoleDescription NS_AVAILABLE_MAC(10_10);

// UIElement for search field search button
// Invokes when clients request NSAccessibilitySearchButtonAttribute
@property (nullable, strong) id accessibilitySearchButton NS_AVAILABLE_MAC(10_10);

// UIElement for search field menu
// Invokes when clients request NSAccessibilitySearchMenuAttribute
@property (nullable, strong) id accessibilitySearchMenu NS_AVAILABLE_MAC(10_10);

// Returns YES if the UIElement is selected
// Invokes when clients request NSAccessibilitySelectedAttribute
@property (getter = isAccessibilitySelected) BOOL accessibilitySelected NS_AVAILABLE_MAC(10_10);

// Array of selected child UIElements
// Invokes when clients request NSAccessibilitySelectedChildrenAttribute
@property (nullable, copy) NSArray *accessibilitySelectedChildren NS_AVAILABLE_MAC(10_10);

// Array of UIElements that this titles
// Invokes when clients request NSAccessibilityServesAsTitleForUIElementsAttribute
@property (nullable, copy) NSArray *accessibilityServesAsTitleForUIElements NS_AVAILABLE_MAC(10_10);

// Menu being displayed for the UIElement
// Invokes when clients request NSAccessibilityShownMenuAttribute
@property (nullable, strong) id accessibilityShownMenu NS_AVAILABLE_MAC(10_10);

// The UIElement's minimum value
// Invokes when clients request NSAccessibilityMinValueAttribute
@property (nullable, strong) id accessibilityMinValue NS_AVAILABLE_MAC(10_10);

// The UIElement's maximum value
// Invokes when clients request NSAccessibilityMaxValueAttribute
@property (nullable, strong) id accessibilityMaxValue NS_AVAILABLE_MAC(10_10);

// Corresponding UIElements
// Invokes when clients request NSAccessibilityLinkedUIElementsAttribute
@property (nullable, copy) NSArray *accessibilityLinkedUIElements NS_AVAILABLE_MAC(10_10);

// UIElement for the containing window
// Invokes when clients request NSAccessibilityWindowAttribute
@property (nullable, weak) id accessibilityWindow NS_AVAILABLE_MAC(10_10);

// Unique identifier for the UIElement
// Invokes when clients request NSAccessibilityIdentifierAttribute
@property (nullable, copy) NSString *accessibilityIdentifier NS_AVAILABLE_MAC(10_10);

// Instance description (e.g. a tool tip)
// Invokes when clients request NSAccessibilityHelpAttribute
@property (nullable, copy) NSString *accessibilityHelp NS_AVAILABLE_MAC(10_10);

// Filename of the underlying asset
// Invokes when clients request NSAccessibilityFilenameAttribute
@property (nullable, copy) NSString *accessibilityFilename NS_AVAILABLE_MAC(10_10);

// Returns YES if the UIElement is expanded
// Invokes when clients request NSAccessibilityExpandedAttribute
@property (getter = isAccessibilityExpanded) BOOL accessibilityExpanded NS_AVAILABLE_MAC(10_10);

// Returns YES if the UIElement has been edited
// Invokes when clients request NSAccessibilityEditedAttribute
@property (getter = isAccessibilityEdited) BOOL accessibilityEdited NS_AVAILABLE_MAC(10_10);

// Returns YES if the element responds to user events
// Invokes when clients request NSAccessibilityEnabledAttribute
@property (getter = isAccessibilityEnabled) BOOL accessibilityEnabled NS_AVAILABLE_MAC(10_10);

// Array of UIElements that represent children of the current UIElement
// Invokes when clients request NSAccessibilityChildrenAttribute
@property (nullable, copy) NSArray *accessibilityChildren NS_AVAILABLE_MAC(10_10);

// UIElement for search field clear button
// Invokes when clients request NSAccessibilityClearButtonAttribute
@property (nullable, strong) id accessibilityClearButton NS_AVAILABLE_MAC(10_10);

// UIElement for cancel button
// Invokes when clients request NSAccessibilityCancelButtonAttribute
@property (nullable, strong) id accessibilityCancelButton NS_AVAILABLE_MAC(10_10);

// Returns YES if the UIElement contains protected content
// Invokes when clients request NSAccessibilityContainsProtectedContentAttribute
@property (getter = isAccessibilityProtectedContent) BOOL accessibilityProtectedContent NS_AVAILABLE_MAC(10_10);

// Array of primary content elements
// Invokes when clients request NSAccessibilityContentsAttribute
@property (nullable, copy) NSArray *accessibilityContents NS_AVAILABLE_MAC(10_10);

// Description of UIElement
// Invokes when clients request NSAccessibilityDescriptionAttribute
@property (nullable, copy) NSString *accessibilityLabel NS_AVAILABLE_MAC(10_10);

// Returns YES if the element is has been triggered to display alternate UIs
// Invokes when clients request NSAccessibilityAlternateUIVisibleAttribute
@property (getter = isAccessibilityAlternateUIVisible) BOOL accessibilityAlternateUIVisible NS_AVAILABLE_MAC(10_10);

// Array of elements with which this element shares keyboard focus
// Invokes when clients request NSAccessibilitySharedFocusElementsAttribute
@property (nullable, copy) NSArray *accessibilitySharedFocusElements NS_AVAILABLE_MAC(10_10);

#pragma mark Application

// Returns YES if the element is focused (generally, accessibilityFocused is equivalent to the
// to the UIElement with the focus ring or selection)
// Invokes when clients request NSAccessibilityFocusedUIElementAttribute
@property (nullable, strong) id accessibilityApplicationFocusedUIElement NS_AVAILABLE_MAC(10_10);

// UIElement for the main window.
// Invokes when clients request NSAccessibilityMainWindowAttribute
@property (nullable, strong) id accessibilityMainWindow NS_AVAILABLE_MAC(10_10);

// Returns YES if the app hidden
// Invokes when clients request NSAccessibilityHiddenAttribute
@property (getter = isAccessibilityHidden) BOOL accessibilityHidden NS_AVAILABLE_MAC(10_10);

// Returns YES if the app is active
// Invokes when clients request NSAccessibilityFrontmostAttribute
@property (getter = isAccessibilityFrontmost) BOOL accessibilityFrontmost NS_AVAILABLE_MAC(10_10);

// UIElement for the key window.
// Invokes when clients request NSAccessibilityFocusedWindowAttribute
@property (nullable, strong) id accessibilityFocusedWindow NS_AVAILABLE_MAC(10_10);

// Array of UIElements for the windows
// Invokes when clients request NSAccessibilityWindowsAttribute
@property (nullable, copy) NSArray *accessibilityWindows NS_AVAILABLE_MAC(10_10);

// UIElement for the application extras menu bar.
// Invokes when clients request NSAccessibilityExtrasMenuBarAttribute
@property (nullable, weak) id accessibilityExtrasMenuBar NS_AVAILABLE_MAC(10_10);

// UIElement for the menu bar
// Invokes when clients request NSAccessibilityMenuBarAttribute
@property (nullable, weak) id accessibilityMenuBar NS_AVAILABLE_MAC(10_10);

#pragma mark Browser
// Array of UIElements for titles
// Invokes when clients request NSAccessibilityColumnTitlesAttribute
@property (nullable, copy) NSArray *accessibilityColumnTitles NS_AVAILABLE_MAC(10_10);

#pragma mark Grid
// Returns a BOOL indicating whether the children are ordered row major, or column major.
// Invokes when clients request NSAccessibilityOrderedByRowAttribute
@property (getter = isAccessibilityOrderedByRow) BOOL accessibilityOrderedByRow NS_AVAILABLE_MAC(10_10);

#pragma mark Layout area
// Horizontal units
// Invokes when clients request NSAccessibilityHorizontalUnitsAttribute
@property NSAccessibilityUnits accessibilityHorizontalUnits NS_AVAILABLE_MAC(10_10);

// Vertical units
// Invokes when clients request NSAccessibilityVerticalUnitsAttribute
@property NSAccessibilityUnits accessibilityVerticalUnits NS_AVAILABLE_MAC(10_10);

// Human-readable description of the horizontal units
// Invokes when clients request NSAccessibilityHorizontalUnitDescriptionAttribute
@property (nullable, copy) NSString *accessibilityHorizontalUnitDescription NS_AVAILABLE_MAC(10_10);

// Human-readable description of the vertical units
// Invokes when clients request NSAccessibilityVerticalUnitDescriptionAttribute
@property (nullable, copy) NSString *accessibilityVerticalUnitDescription NS_AVAILABLE_MAC(10_10);

// Layout point from screen point
// Invokes when clients request NSAccessibilityLayoutPointForScreenPointParameterizedAttribute
- (NSPoint)accessibilityLayoutPointForScreenPoint:(NSPoint)point NS_AVAILABLE_MAC(10_10);

// Layout size from screen size
// Invokes when clients request NSAccessibilityLayoutSizeForScreenSizeParameterizedAttribute
- (NSSize)accessibilityLayoutSizeForScreenSize:(NSSize)size NS_AVAILABLE_MAC(10_10);

// Screen point from layout point
// Invokes when clients request NSAccessibilityScreenPointForLayoutPointParameterizedAttribute
- (NSPoint)accessibilityScreenPointForLayoutPoint:(NSPoint)point NS_AVAILABLE_MAC(10_10);

// Screen size from layout size
// Invokes when clients request NSAccessibilityScreenSizeForLayoutSizeParameterizedAttribute
- (NSSize)accessibilityScreenSizeForLayoutSize:(NSSize)size NS_AVAILABLE_MAC(10_10);

#pragma mark Layout item
// UIElements for handles
// Invokes when clients request NSAccessibilityHandlesAttribute
@property (nullable, copy) NSArray *accessibilityHandles NS_AVAILABLE_MAC(10_10);

#pragma mark Level indicator
// Warning value of a level indicator, typically a number
// Invokes when clients request NSAccessibilityWarningValueAttribute
@property (nullable, strong) id accessibilityWarningValue NS_AVAILABLE_MAC(10_10);

// Critical value of a level indicator, typically a number
// Invokes when clients request NSAccessibilityCriticalValueAttribute
@property (nullable, strong) id accessibilityCriticalValue NS_AVAILABLE_MAC(10_10);

#pragma mark Outline
// Returns true if sub-rows are visible
// Invokes when clients request NSAccessibilityDisclosingAttribute
@property (getter = isAccessibilityDisclosed) BOOL accessibilityDisclosed NS_AVAILABLE_MAC(10_10);

// UIElement for disclosing row
// Invokes when clients request NSAccessibilityDisclosedByRowAttribute
@property (nullable, weak) id accessibilityDisclosedByRow NS_AVAILABLE_MAC(10_10);

// Array of UIElements for disclosed rows of the current ruw (ie, sub-rows)
// Invokes when clients request NSAccessibilityDisclosedRowsAttribute
@property (nullable, strong) id accessibilityDisclosedRows NS_AVAILABLE_MAC(10_10);

// Indentation level
// Invokes when clients request NSAccessibilityDisclosureLevelAttribute
@property NSInteger accessibilityDisclosureLevel NS_AVAILABLE_MAC(10_10);

#pragma mark Ruler
// Invokes when clients request NSAccessibilityMarkerUIElementsAttribute
@property (nullable, copy) NSArray *accessibilityMarkerUIElements NS_AVAILABLE_MAC(10_10);

// Invokes when clients request NSAccessibilityMarkerValuesAttribute
@property (nullable, strong) id accessibilityMarkerValues NS_AVAILABLE_MAC(10_10);

// Invokes when clients request NSAccessibilityMarkerGroupUIElementAttribute
@property (nullable, strong) id accessibilityMarkerGroupUIElement NS_AVAILABLE_MAC(10_10);

// Ruler units
// Invokes when clients request NSAccessibilityUnitsAttribute
@property NSAccessibilityUnits accessibilityUnits NS_AVAILABLE_MAC(10_10);

// Human-readable description of the ruler units
// Invokes when clients request NSAccessibilityUnitDescriptionAttribute
@property (nullable, copy) NSString *accessibilityUnitDescription NS_AVAILABLE_MAC(10_10);

// Marker type
// Invokes when clients request NSAccessibilityMarkerTypeAttribute
@property NSAccessibilityRulerMarkerType accessibilityRulerMarkerType NS_AVAILABLE_MAC(10_10);

// Human-readable description of the marker type
// Invokes when clients request NSAccessibilityMarkerTypeDescriptionAttribute
@property (nullable, copy) NSString *accessibilityMarkerTypeDescription NS_AVAILABLE_MAC(10_10);

#pragma mark Scrollable region
// UIElement for the horizontal scroller
// Invokes when clients request NSAccessibilityHorizontalScrollBarAttribute
@property (nullable, strong) id accessibilityHorizontalScrollBar NS_AVAILABLE_MAC(10_10);

// UIElement for the vertical scroller
// Invokes when clients request NSAccessibilityVerticalScrollBarAttribute
@property (nullable, strong) id accessibilityVerticalScrollBar NS_AVAILABLE_MAC(10_10);

#pragma mark Slider
// Array of allowed values
// Invokes when clients request NSAccessibilityAllowedValuesAttribute
@property (nullable, copy) NSArray<NSNumber *> *accessibilityAllowedValues NS_AVAILABLE_MAC(10_10);

// Array of label UIElements
// Invokes when clients request NSAccessibilityLabelUIElementsAttribute
@property (nullable, copy) NSArray *accessibilityLabelUIElements NS_AVAILABLE_MAC(10_10);

// Value of a label UIElement
// Invokes when clients request NSAccessibilityLabelValueAttribute
@property float accessibilityLabelValue NS_AVAILABLE_MAC(10_10);

#pragma mark Splitter
// UIElements for splitters
// Invokes when clients request NSAccessibilitySplittersAttribute
@property (nullable, copy) NSArray *accessibilitySplitters NS_AVAILABLE_MAC(10_10);

#pragma mark Stepper
// UIElement for the decrement button
// Invokes when clients request NSAccessibilityDecrementButtonAttribute
@property (nullable, strong) id accessibilityDecrementButton NS_AVAILABLE_MAC(10_10);

// UIElement for the increment button
// Invokes when clients request NSAccessibilityIncrementButtonAttribute
@property (nullable, strong) id accessibilityIncrementButton NS_AVAILABLE_MAC(10_10);

#pragma mark Tab view
// UIElements for tabs
// Invokes when clients request NSAccessibilityTabsAttribute
@property (nullable, copy) NSArray *accessibilityTabs NS_AVAILABLE_MAC(10_10);

#pragma mark Table/Outline
// UIElement for header
// Invokes when clients request NSAccessibilityHeaderAttribute
@property (nullable, strong) id accessibilityHeader NS_AVAILABLE_MAC(10_10);

// Number of columns
// Invokes when clients request NSAccessibilityColumnCountAttribute
@property NSInteger accessibilityColumnCount NS_AVAILABLE_MAC(10_10);

// Number of rows
// Invokes when clients request NSAccessibilityRowCountAttribute
@property NSInteger accessibilityRowCount NS_AVAILABLE_MAC(10_10);

// Index of the current UIElement (row index for a row, column index for a column)
// Invokes when clients request NSAccessibilityIndexAttribute
@property NSInteger accessibilityIndex NS_AVAILABLE_MAC(10_10);

// Array of UIElements for columns
// Invokes when clients request NSAccessibilityColumnsAttribute
@property (nullable, copy) NSArray *accessibilityColumns NS_AVAILABLE_MAC(10_10);

// Array of UIElements for rows
// Invokes when clients request NSAccessibilityRowsAttribute
@property (nullable, copy) NSArray *accessibilityRows NS_AVAILABLE_MAC(10_10);

// Array of UIElements for visible rows
// Invokes when clients request NSAccessibilityVisibleRowsAttribute
@property (nullable, copy) NSArray *accessibilityVisibleRows NS_AVAILABLE_MAC(10_10);

// Array of UIElements for selected rows
// Invokes when clients request NSAccessibilitySelectedRowsAttribute
@property (nullable, copy) NSArray *accessibilitySelectedRows NS_AVAILABLE_MAC(10_10);

// Array of UIElements for visible columns
// Invokes when clients request NSAccessibilityVisibleColumnsAttribute
@property (nullable, copy) NSArray *accessibilityVisibleColumns NS_AVAILABLE_MAC(10_10);

// Array of UIElements for selected columns
// Invokes when clients request NSAccessibilitySelectedColumnsAttribute
@property (nullable, copy) NSArray *accessibilitySelectedColumns NS_AVAILABLE_MAC(10_10);

// Sort direction
// Invokes when clients request NSAccessibilitySortDirectionAttribute
@property NSAccessibilitySortDirection accessibilitySortDirection NS_AVAILABLE_MAC(10_10);

#pragma mark Table (cell based)
// Array of UIElements for row headers
// Invokes when clients request NSAccessibilityRowHeaderUIElementsAttribute
@property (nullable, copy) NSArray *accessibilityRowHeaderUIElements NS_AVAILABLE_MAC(10_10);

// Array of UIElements for selected cells
// Invokes when clients request NSAccessibilitySelectedCellsAttribute
@property (nullable, copy) NSArray *accessibilitySelectedCells NS_AVAILABLE_MAC(10_10);

// Array of UIElements for visible cells
// Invokes when clients request NSAccessibilityVisibleCellsAttribute
@property (nullable, copy) NSArray *accessibilityVisibleCells NS_AVAILABLE_MAC(10_10);

// Array of UIElements for column headers
// Invokes when clients request NSAccessibilityColumnHeaderUIElementsAttribute
@property (nullable, copy) NSArray *accessibilityColumnHeaderUIElements NS_AVAILABLE_MAC(10_10);

// UIElement for cell at specified row and column
// Invokes when clients request NSAccessibilityCellForColumnAndRowParameterizedAttribute
- (nullable id)accessibilityCellForColumn:(NSInteger)column row:(NSInteger)row NS_AVAILABLE_MAC(10_10);

#pragma mark Table cell
// Cell location and row span
// Invokes when clients request NSAccessibilityRowIndexRangeAttribute
@property NSRange accessibilityRowIndexRange NS_AVAILABLE_MAC(10_10);

// Cell location and column span
// Invokes when clients request NSAccessibilityColumnIndexRangeAttribute
@property NSRange accessibilityColumnIndexRange NS_AVAILABLE_MAC(10_10);

#pragma mark Text
// Line number containing caret
// Invokes when clients request NSAccessibilityInsertionPointLineNumberAttribute
@property NSInteger accessibilityInsertionPointLineNumber NS_AVAILABLE_MAC(10_10);

// Part of shared text in this view
// Invokes when clients request NSAccessibilitySharedCharacterRangeAttribute
@property NSRange accessibilitySharedCharacterRange NS_AVAILABLE_MAC(10_10);

// Text views sharing text
// Invokes when clients request NSAccessibilitySharedTextUIElementsAttribute
@property (nullable, copy) NSArray *accessibilitySharedTextUIElements NS_AVAILABLE_MAC(10_10);

// Range of visible text
// Invokes when clients request NSAccessibilityVisibleCharacterRangeAttribute
@property NSRange accessibilityVisibleCharacterRange NS_AVAILABLE_MAC(10_10);

// Number of characters
// Invokes when clients request NSAccessibilityNumberOfCharactersAttribute
@property NSInteger accessibilityNumberOfCharacters NS_AVAILABLE_MAC(10_10);

// String of selected text
// Invokes when clients request NSAccessibilitySelectedTextAttribute
@property (nullable, copy) NSString *accessibilitySelectedText NS_AVAILABLE_MAC(10_10);

// Range of selected text
// Invokes when clients request NSAccessibilitySelectedTextRangeAttribute
@property NSRange accessibilitySelectedTextRange NS_AVAILABLE_MAC(10_10);

// Array of NSValue (rangeValue) ranges of selected text
// Invokes when clients request NSAccessibilitySelectedTextRangesAttribute
@property (nullable, copy) NSArray<NSValue *> *accessibilitySelectedTextRanges NS_AVAILABLE_MAC(10_10);

// Attributed string for a provided range.
// does _not_ use attributes from Appkit/AttributedString.h
// Invokes when clients request NSAccessibilityAttributedStringForRangeParameterizedAttribute
- (nullable NSAttributedString *)accessibilityAttributedStringForRange:(NSRange)range NS_AVAILABLE_MAC(10_10);

// Range for the provided line number
// Invokes when clients request NSAccessibilityRangeForLineParameterizedAttribute
- (NSRange)accessibilityRangeForLine:(NSInteger)line NS_AVAILABLE_MAC(10_10);

// String for the provided range
// Invokes when clients request NSAccessibilityStringForRangeParameterizedAttribute
- (nullable NSString *)accessibilityStringForRange:(NSRange)range NS_AVAILABLE_MAC(10_10);

// Composed character range for the character at the provided point
// Invokes when clients request NSAccessibilityRangeForPositionParameterizedAttribute
- (NSRange)accessibilityRangeForPosition:(NSPoint)point NS_AVAILABLE_MAC(10_10);

// Composed character range for the provided index
// Invokes when clients request NSAccessibilityRangeForIndexParameterizedAttribute
- (NSRange)accessibilityRangeForIndex:(NSInteger)index NS_AVAILABLE_MAC(10_10);

// Frame of text in the provided range (in screen coordinates.) See NSAccessibilityFrameInView()
// Invokes when clients request NSAccessibilityBoundsForRangeParameterizedAttribute
- (NSRect)accessibilityFrameForRange:(NSRange)range NS_AVAILABLE_MAC(10_10);

// RTF data for text in the provided range
// Invokes when clients request NSAccessibilityRTFForRangeParameterizedAttribute
- (nullable NSData *)accessibilityRTFForRange:(NSRange)range NS_AVAILABLE_MAC(10_10);

// Extent of style run at the provided index
// Invokes when clients request NSAccessibilityStyleRangeForIndexParameterizedAttribute
- (NSRange)accessibilityStyleRangeForIndex:(NSInteger)index NS_AVAILABLE_MAC(10_10);

// Line number for character index
// Invokes when clients request NSAccessibilityLineForIndexParameterizedAttribute
- (NSInteger)accessibilityLineForIndex:(NSInteger)index NS_AVAILABLE_MAC(10_10);

#pragma mark Window
// UIElement for toolbar box (or nil)
// Invokes when clients request NSAccessibilityToolbarButtonAttribute
@property (nullable, strong) id accessibilityToolbarButton NS_AVAILABLE_MAC(10_10);

// Is the window modal
// Invokes when clients request NSAccessibilityModalAttribute
@property (getter = isAccessibilityModal) BOOL accessibilityModal NS_AVAILABLE_MAC(10_10);

// UIElement for title's icon (or nil)
// Invokes when clients request NSAccessibilityProxyAttribute
@property (nullable, strong) id accessibilityProxy NS_AVAILABLE_MAC(10_10);

// Returns YES if this is it the main window
// Invokes when clients request NSAccessibilityMainAttribute
@property (getter = isAccessibilityMain) BOOL accessibilityMain NS_AVAILABLE_MAC(10_10);

// UIElement for full screen button
// Invokes when clients request NSAccessibilityFullScreenButtonAttribute
@property (nullable, strong) id accessibilityFullScreenButton NS_AVAILABLE_MAC(10_10);

// UIElement for grow box
// Invokes when clients request NSAccessibilityGrowAreaAttribute
@property (nullable, strong) id accessibilityGrowArea NS_AVAILABLE_MAC(10_10);

// URL for open document
// Invokes when clients request NSAccessibilityDocumentAttribute
@property (nullable, copy) NSString *accessibilityDocument NS_AVAILABLE_MAC(10_10);

// UIElement for default button
// Invokes when clients request NSAccessibilityDefaultButtonAttribute
@property (nullable, strong) id accessibilityDefaultButton NS_AVAILABLE_MAC(10_10);

// UIElement for close button
// Invokes when clients request NSAccessibilityCloseButtonAttribute
@property (nullable, strong) id accessibilityCloseButton NS_AVAILABLE_MAC(10_10);

// UIElement for zoom button
// Invokes when clients request NSAccessibilityZoomButtonAttribute
@property (nullable, strong) id accessibilityZoomButton NS_AVAILABLE_MAC(10_10);

// UIElement for minimize button
// Invokes when clients request NSAccessibilityMinimizeButtonAttribute
@property (nullable, strong) id accessibilityMinimizeButton NS_AVAILABLE_MAC(10_10);

// Returns YES if the window minimized
// Invokes when clients request NSAccessibilityMinimizedAttribute
@property (getter = isAccessibilityMinimized) BOOL accessibilityMinimized NS_AVAILABLE_MAC(10_10);

#pragma mark Actions
// Invokes when clients perform NSAccessibilityCancelAction
- (BOOL)accessibilityPerformCancel NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityConfirmAction
- (BOOL)accessibilityPerformConfirm NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityDecrementAction
- (BOOL)accessibilityPerformDecrement NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityDeleteAction
- (BOOL)accessibilityPerformDelete NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityIncrementAction
- (BOOL)accessibilityPerformIncrement NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityPickAction
- (BOOL)accessibilityPerformPick NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityPressAction
- (BOOL)accessibilityPerformPress NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityRaiseAction
- (BOOL)accessibilityPerformRaise NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityShowAlternateUIAction
- (BOOL)accessibilityPerformShowAlternateUI NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityShowDefaultUIAction
- (BOOL)accessibilityPerformShowDefaultUI NS_AVAILABLE_MAC(10_10);

// Invokes when clients perform NSAccessibilityShowMenuAction
- (BOOL)accessibilityPerformShowMenu NS_AVAILABLE_MAC(10_10);

#pragma mark Allowed Selectors
// Returns YES if accessibility clients should be able to invoke the provided selector
- (BOOL)isAccessibilitySelectorAllowed:(SEL)selector NS_AVAILABLE_MAC(10_10);

@end

NS_ASSUME_NONNULL_END
