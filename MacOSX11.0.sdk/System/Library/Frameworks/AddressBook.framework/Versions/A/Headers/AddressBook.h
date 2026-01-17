//
//  AddressBook.h
//  AddressBook Framework
//
//  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
//

#if __OBJC__

#if defined(__cplusplus)
extern "C" {
#endif

    #import <AddressBook/ABTypedefs.h>
    #import <AddressBook/ABGlobals.h>
    #import <AddressBook/ABAddressBook.h>
    #import <AddressBook/ABRecord.h>
    #import <AddressBook/ABGroup.h>
    #import <AddressBook/ABPerson.h>
    #import <AddressBook/ABImageLoading.h>
    #import <AddressBook/ABSearchElement.h>
    #import <AddressBook/ABMultiValue.h>
#if defined(__cplusplus)
}
#endif
#else
    #include <AddressBook/ABTypedefs.h>
    #include <AddressBook/ABGlobalsC.h>
    #include <AddressBook/ABAddressBookC.h>
#endif

