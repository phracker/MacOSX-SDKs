//
//  ABPersonView.h
//  AddressBook Framework
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7

#import <AddressBook/ABPerson.h>

// ================================================================================
//	interface ABPersonView
// ================================================================================
// ABPersonView provides a view for displaying and editing ABPerson objects in your
// user interface.


@interface ABPersonView : NSView {
@private
	ABAddressBook *_addressBook;
	ABPerson *_person;
	id _delegate;
	NSView *_view;
	id _container;
	id   _reserved1;
	id   _reserved2;
	id   _reserved3;
}

@property (assign) BOOL editing;
// A Boolean value that determines whether the receiver is in editing mode.
// When YES, ABPersonView includes additional controls to manipulate person properties.

@property (readwrite, retain) ABPerson *person;
// An ABPerson record for display.
// Raises if person originates from ABAddressBook's +sharedAddressBook.
// Person must be exist in an ABAddressBook created and manipulated on the main thread only.
// When person is nil, displays an empty selection state. 

@end

#endif