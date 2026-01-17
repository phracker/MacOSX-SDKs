//
//  ABActionsC.h
//  AddressBook Framework
//
//  Copyright (c) 2003 Apple Computer. All rights reserved.
//

#ifndef __ABACTIONSC__
#define __ABACTIONSC__

#if defined(__cplusplus)
extern "C" {
#endif

#include <AddressBook/ABAddressBookC.h>
#include <CoreFoundation/CoreFoundation.h>

// --------------------------------------------------------------------------------
//      Action Support
// --------------------------------------------------------------------------------
// This API allows developers to populate AddressBook.app's roll-over menus with custom
// entries. Your CFBundle must implement a function named ABActionRegisterCallbacks which
// will return a pointer to an ABActionCallbacks struct. This struct should be filled out
// as follows:
//
// version: The version of this structure is 0.
//
// property: A pointer to a function that returns the AddressBook property this action applies
// to. Only items with labels may have actions at this time. (emails, phones, birthdays, etc)
//
// title: A pointer to a function which returns a copy of the title to be displayed. This function
// takes two parameters, the selected person and item identifier. The item identifier will be NULL
// for single value properties. AddressBook will release this string when it's done with it.
//
// enabled: A pointer to a function which returns YES if the action should be enabled for the
// passed ABPersonRef and item identifier. The item identifier will be NULL for single value
// properties. This field may be NULL. Actions with NULL enabled callbacks will always be enabled.
//
// selected. A pointer to a function which will be called when the user selects this action.
// It's passed an ABPersonRef and item identifier. The item identifier will be NULL for single
// value properties.
//
// Action plugins are stored in ~/Library/Address Book Plug-Ins or /Library/Address Book Plug-Ins
//
// There can be only 1 Action plugin per bundle.

typedef CFStringRef (*ABActionGetPropertyCallback) (void);
typedef CFStringRef (*ABActionCopyTitleCallback) (ABPersonRef person, CFStringRef identifier);
typedef Boolean (*ABActionEnabledCallback) (ABPersonRef person, CFStringRef identifier);
typedef void (*ABActionSelectedCallback) (ABPersonRef person, CFStringRef identifier);

typedef struct {
    CFIndex                         version;
    ABActionGetPropertyCallback     property;
    ABActionCopyTitleCallback       title;
    ABActionEnabledCallback         enabled;
    ABActionSelectedCallback        selected;
} ABActionCallbacks;

// Your CFBundle MUST include a function named ABActionRegisterCallbacks which returns a pointer
// to a filled out ABActionCallbacks struct:
//
// ABActionCallbacks* ABActionRegisterCallbacks(void);

#endif

#if defined(__cplusplus)
}
#endif

