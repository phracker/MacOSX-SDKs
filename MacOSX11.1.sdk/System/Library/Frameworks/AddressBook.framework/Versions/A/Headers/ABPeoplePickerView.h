//
//  ABPeoplePickerView.h
//  AddressBook Framework
//
//  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
//

#ifndef __ABPEOPLEPICKERVIEW__
#define __ABPEOPLEPICKERVIEW__

#import <Cocoa/Cocoa.h>

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED

typedef enum {
    ABNoValueSelection       = 0,
    ABSingleValueSelection   = 1,
    ABMultipleValueSelection = 2
} ABPeoplePickerSelectionBehavior;

@class ABRecord, ABPerson, ABGroup;

API_AVAILABLE(macos(10.3))
API_UNAVAILABLE(macCatalyst)
@interface ABPeoplePickerView : NSView {
@private
    id _reserved1 __unused;
    id _reserved2 __unused;
    id _reserved3 __unused;
    id _reserved4 __unused;
    id _reserved5 __unused;
    SEL    _reserved6 __unused;
    SEL    _reserved7 __unused;
    id _reserved8 __unused;
    id _reserved9 __unused;
    id _reserved10 __unused;
}

/*
 * Look and Feel
 */

// The accessory view is placed to the left of the search field. Setting to nil removes the view.
@property (nonatomic, retain) IBOutlet NSView* accessoryView;

// Modifies the selection behavior. Defaults to ABSingleValueSelection.
//
// ABNoValueSelection will not allow the user to select individual values.
// ABSingleValueSelection will allow the user to choose a single value for a person.
// ABMultipleValueSelection will allow the user to choose multiple values for a person.
@property (nonatomic, assign) ABPeoplePickerSelectionBehavior valueSelectionBehavior;

// Allow the user to select entire groups in the group column. If false, at least one
// person in the group will be selected. Defaults to NO.
@property (nonatomic, assign) BOOL allowsGroupSelection;

// Allow the user to select more than one group/record/value at a time. Defaults to NO.
@property (nonatomic, assign) BOOL allowsMultipleSelection;


/*
 * Value column
 */

// These methods control what data (if any) is shown in the values column. The column won't display
// if no properties are added. A popup button in the column header will be used if more than one property
// is added. Titles for built in properties will localized automatically.
- (void)addProperty:(NSString *)property;
- (void)removeProperty:(NSString *)property;
- (NSArray *)properties;

// Localized titles for third party properties should be set with these methods.
- (void)setColumnTitle:(NSString *)title forProperty:(NSString *)property;
- (NSString *)columnTitleForProperty:(NSString *)property;

// Display one of the properties added above.
@property (nonatomic, retain) NSString* displayedProperty;

/*
 * Persistence
 */

// Saves column positions and filter selection.
@property (nonatomic, retain) NSString* autosaveName;

/*
 * Selection
 */

// Returns group column selection as an array of ABGroup objects. An empty array will be
// returned if the All group is selected.
@property (readonly) NSArray* selectedGroups;

// Returns names column selection as an array of ABGroup or ABPerson objects. When unified contacts are selected,
// returns every ABPerson that owns a selected value.
@property (readonly) NSArray* selectedRecords;

// This method returns an array of selected multi-value identifiers. Returns nil if the displayed
// property is a single value type.
- (NSArray *)selectedIdentifiersForPerson:(ABPerson*)person;

// Select group/name/value programatically.
- (void)selectGroup:(ABGroup *)group byExtendingSelection:(BOOL)extend;
- (void)selectRecord:(ABRecord *)record byExtendingSelection:(BOOL)extend;
// Individual values contained within an multi-value property can be selected with this method.
- (void)selectIdentifier:(NSString *)identifier forPerson:(ABPerson *)person byExtendingSelection:(BOOL)extend;

// Remove selection
- (void)deselectGroup:(ABGroup *)group;
- (void)deselectRecord:(ABRecord *)record;
- (void)deselectIdentifier:(NSString *)identifier forPerson:(ABPerson *)person;

- (void)deselectAll:(id)sender;

/*
 * Actions
 */

// Clear the search field and reset the list of displayed names.
- (void)clearSearchField:(id)sender;

// Set target for various double click actions
@property (nonatomic, assign) id target;

// Provide an action to be invoked when the user double clicks on an item in the group column.
@property (nonatomic, assign) SEL groupDoubleAction;

// Provide an action to be invoked when the user double clicks on an item in the names column.
@property (nonatomic, assign) SEL nameDoubleAction;

@end

extern NSString * const ABPeoplePickerGroupSelectionDidChangeNotification    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern NSString * const ABPeoplePickerNameSelectionDidChangeNotification     AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern NSString * const ABPeoplePickerValueSelectionDidChangeNotification    AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern NSString * const ABPeoplePickerDisplayedPropertyDidChangeNotification AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

@interface ABPeoplePickerView (ABPeoplePickerConvenience)
// Returns an array of all items selected in the values column.
- (NSArray *)selectedValues;

// Launch AddressBook and edit the current selection
- (void)editInAddressBook:(id)sender;
- (void)selectInAddressBook:(id)sender;

@end

#endif

#endif // __ABPEOPLEPICKERVIEW__
