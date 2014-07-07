//
//  AddressBook.h
//  AddressBook Framework
//
//  Copyright (c) 2002-2003 Apple Computer. All rights reserved.
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

