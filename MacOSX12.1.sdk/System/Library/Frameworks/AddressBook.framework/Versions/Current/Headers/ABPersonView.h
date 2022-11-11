//
//  ABPersonView.h
//  AddressBook Framework
//
//  Copyright 2009-2014 Apple, Inc. All rights reserved.
//

#ifndef __ABPERSONVIEW__
#define __ABPERSONVIEW__

#import <Cocoa/Cocoa.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

#import <AddressBook/ABPerson.h>

// ================================================================================
//	interface ABPersonView
// ================================================================================
// ABPersonView provides a view for displaying and editing ABPerson objects in your
// user interface.

API_AVAILABLE(macos(10.7))
API_UNAVAILABLE(macCatalyst)
@interface ABPersonView : NSView

@property (assign) BOOL editing;
// A Boolean value that determines whether the receiver is in editing mode.
// When YES, ABPersonView includes additional controls to manipulate person properties.

@property (readwrite, retain) ABPerson *person;
// An ABPerson record for display.
// Raises if person originates from ABAddressBook's +sharedAddressBook.
// Person must be exist in an ABAddressBook created and manipulated on the main thread only.
// When person is nil, displays an empty selection state. 

@property (assign) BOOL shouldShowLinkedPeople AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;
// Indicates whether the view should include information for linked contacts in addition to the set contact.
// If YES, information is included from linked contacts. If NO, only the information on this person is shown.

@end

#endif

#endif // __ABPERSONVIEW__
