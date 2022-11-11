//
//  ContactsDefines.h
//  Contacts
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define CONTACTS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define CONTACTS_EXTERN extern __attribute__((visibility ("default")))
#endif
