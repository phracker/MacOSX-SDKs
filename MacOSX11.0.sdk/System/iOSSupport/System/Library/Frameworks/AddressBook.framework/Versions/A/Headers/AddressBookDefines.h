//
//  AddressBookDefines.h
//  AddressBook
//
//  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
//

#ifndef AddressBook_AddressBookDefines_h
#define AddressBook_AddressBookDefines_h

#ifdef __cplusplus
    #define AB_EXTERN extern "C" __attribute__((visibility ("default")))
#else
    #define AB_EXTERN extern __attribute__((visibility ("default")))
#endif

#ifdef AB_IGNORE_DEPRECATION
    #define AB_DEPRECATED(msg)
#else
    #include <Availability.h>
    #define AB_DEPRECATED(msg) __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_NA, __MAC_NA, __IPHONE_2_0, __IPHONE_9_0, msg)
#endif

#endif
