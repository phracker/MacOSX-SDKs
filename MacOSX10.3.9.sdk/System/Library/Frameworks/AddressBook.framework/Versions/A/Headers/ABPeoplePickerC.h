//
//  ABPeoplePickerC.h
//  AddressBook Framework
//
//  Copyright (c) 2003 Apple Computer. All rights reserved.
//

#ifndef __PEOPLEPICKERC__
#define __PEOPLEPICKERC__

#if defined(__cplusplus)
extern "C" {
#endif

#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/ABAddressBookC.h>
#include <Carbon/Carbon.h>

typedef struct OpaqueABPicker*  ABPickerRef;

/*
 * Picker creation and manipulation
 */

// Creates an ABPickerRef. Release with CFRelease(). The window is created hidden. Call
// ABPickerSetVisibility() to show it.
extern ABPickerRef ABPickerCreate(void) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

// Change the structural frame of the window.
extern void ABPickerSetFrame(ABPickerRef inPicker, const HIRect *inFrame) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern void ABPickerGetFrame(ABPickerRef inPicker, HIRect *outFrame) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern void ABPickerSetVisibility(ABPickerRef inPicker, bool visible) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern bool ABPickerIsVisible(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * Look and Feel
 */

enum
{
    // Choose the selection behavior for the value column. If multiple behaviors are selected,
    // the most restrictive behavior will be used. Defaults to kABPickerSingleValueSelection set
    // to TRUE.
    kABPickerSingleValueSelection   = 1 << 0, // Allow user to choose a single value for a person.
    kABPickerMultipleValueSelection = 1 << 1, // Allow user to choose multiple values for a person.

    // Allow the user to select entire groups in the group column. If false, at least one
    // person in the group will be selected. Defaults to FALSE.
    kABPickerAllowGroupSelection    = 1 << 2,

    // Allow the user to select more than one group/record at a time. Defaults to TRUE.
    kABPickerAllowMultipleSelection = 1 << 3
};

typedef OptionBits ABPickerAttributes;

extern ABPickerAttributes ABPickerGetAttributes(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern void ABPickerChangeAttributes(ABPickerRef inPicker, ABPickerAttributes inAttributesToSet, ABPickerAttributes inAttributesToClear) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * Value column
 */

    // These methods control what data (if any) is shown in the values column. The column will only
    // display if an AB property is added. A popup button in the column header will be used if more
    // than one property is added. Titles for built in properties will localized automatically. A
    // list of AB properties can be found in <AddressBook/ABGlobals.h>.
extern void ABPickerAddProperty(ABPickerRef inPicker, CFStringRef inProperty) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern void ABPickerRemoveProperty(ABPickerRef inPicker, CFStringRef inProperty) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Returns an array of AB Properties as CFStringRefs.
extern CFArrayRef ABPickerCopyProperties(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // Localized titles for third party properties should be set with these methods.
extern void ABPickerSetColumnTitle(ABPickerRef inPicker, CFStringRef inTitle, CFStringRef inProperty) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern CFStringRef ABPickerCopyColumnTitle(ABPickerRef inPicker, CFStringRef inProperty) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // Display one of the properties added above in the values column.
extern void ABPickerSetDisplayedProperty(ABPickerRef inPicker, CFStringRef inProperty) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern CFStringRef ABPickerCopyDisplayedProperty(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * Selection
 */

    // Returns group column selection as an array of ABGroupRef objects.
extern CFArrayRef ABPickerCopySelectedGroups(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // Returns names column selection as an array of ABGroupRef or ABPersonRef objects.
extern CFArrayRef ABPickerCopySelectedRecords(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // This method returns an array of selected multi-value identifiers. Returns nil if the displayed
    // property is a single value type.
extern CFArrayRef ABPickerCopySelectedIdentifiers(ABPickerRef inPicker, ABPersonRef inPerson) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // Returns an array containing CFStringRefs for each item selected in the values column.
extern CFArrayRef ABPickerCopySelectedValues(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // Select group/name/value programatically.
extern void ABPickerSelectGroup(ABPickerRef inPicker, ABGroupRef inGroup, bool inExtendSelection) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern void ABPickerSelectRecord(ABPickerRef inPicker, ABRecordRef inRecord, bool inExtendSelection) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
    // Individual values contained within an multi-value property can be selected with this method.
extern void ABPickerSelectIdentifier(ABPickerRef inPicker, ABPersonRef inPerson, CFStringRef inIdentifier, bool inExtendSelection) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // Remove selection
extern void ABPickerDeselectGroup(ABPickerRef inPicker, ABGroupRef inGroup) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern void ABPickerDeselectRecord(ABPickerRef inPicker, ABRecordRef inRecord) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern void ABPickerDeselectIdentifier(ABPickerRef inPicker, ABPersonRef inPerson, CFStringRef inIdentifier) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

extern void ABPickerDeselectAll(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/*
 * Events and Actions
 *
 * Your delegate will be notified when the user changes the selection or displayed property of the picker.
 * Picker events have an event class of kEventClassABPeoplePicker and one of the kinds listed below. Picker
 * events contain an event parameter which contains the ABPickerRef. To obtain this:
 *
 * GetEventParameter(inEvent, kEventParamABPickerRef,
 *                   typeCFTypeRef, NULL, sizeof(ABPickerRef),
 *                   NULL, &outPickerRef);
 *
 */

enum {
    // Carbon Event class for People Picker
    kEventClassABPeoplePicker = 'abpp'
};

enum {
    // Carbon Event kinds for People Picker
    kEventABPeoplePickerGroupSelectionChanged     = 1,
    kEventABPeoplePickerNameSelectionChanged      = 2,
    kEventABPeoplePickerValueSelectionChanged     = 3,
    kEventABPeoplePickerDisplayedPropertyChanged  = 4,

    kEventABPeoplePickerGroupDoubleClicked        = 5,
    kEventABPeoplePickerNameDoubleClicked         = 6
};

enum {
    // Carbon Event parameter name
    kEventParamABPickerRef	=  'abpp'
};

    // Set the event handler for People Picker events.
extern void ABPickerSetDelegate(ABPickerRef inPicker, HIObjectRef inDelegate) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern HIObjectRef ABPickerGetDelegate(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // Clear the search field and reset the list of displayed names.
extern void ABPickerClearSearchField(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

    // Launch AddressBook and edit the current selection
extern void ABPickerEditInAddressBook(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
extern void ABPickerSelectInAddressBook(ABPickerRef inPicker) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

#if defined(__cplusplus)
}
#endif

#endif

