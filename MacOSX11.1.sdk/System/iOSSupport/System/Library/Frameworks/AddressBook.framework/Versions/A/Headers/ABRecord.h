/*
 *  ABRecord.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *  An ABRecord corresponds to a persistent item, currently either
 *  a contact or a group. Records have a unique persistent integer
 *  ID and a collection of properties with integer keys.
 *
 */

#ifndef __ABRecord__
#define __ABRecord__

#include <AddressBook/AddressBookDefines.h>
#include <CoreFoundation/CoreFoundation.h>
        
typedef CFTypeRef ABRecordRef AB_DEPRECATED("use CNContact, CNGroup, or CNContainer");

typedef int32_t ABRecordID AB_DEPRECATED("use CN object's identifier");
typedef int32_t ABPropertyID AB_DEPRECATED("");

typedef uint32_t ABRecordType AB_DEPRECATED("");
enum {
    kABPersonType = 0,
    kABGroupType  = 1,
    kABSourceType = 2
};

#define kABMultiValueMask (1 << 8) // deprecated
#define kABRecordInvalidID -1 // deprecated
#define kABPropertyInvalidID -1 // deprecated

typedef uint32_t ABPropertyType AB_DEPRECATED("");
enum {
    kABInvalidPropertyType         = 0x0,                                           // deprecated
    kABStringPropertyType          = 0x1,                                           // deprecated
    kABIntegerPropertyType         = 0x2,                                           // deprecated
    kABRealPropertyType            = 0x3,                                           // deprecated
    kABDateTimePropertyType        = 0x4,                                           // deprecated
    kABDictionaryPropertyType      = 0x5,                                           // deprecated
    kABMultiStringPropertyType     = kABMultiValueMask | kABStringPropertyType,     // deprecated
    kABMultiIntegerPropertyType    = kABMultiValueMask | kABIntegerPropertyType,    // deprecated
    kABMultiRealPropertyType       = kABMultiValueMask | kABRealPropertyType,       // deprecated
    kABMultiDateTimePropertyType   = kABMultiValueMask | kABDateTimePropertyType,   // deprecated
    kABMultiDictionaryPropertyType = kABMultiValueMask | kABDictionaryPropertyType, // deprecated
};

AB_EXTERN ABRecordID ABRecordGetRecordID(ABRecordRef record) AB_DEPRECATED("use CN object's identifier");
AB_EXTERN ABRecordType ABRecordGetRecordType(ABRecordRef record) AB_DEPRECATED("");

AB_EXTERN CFTypeRef ABRecordCopyValue(ABRecordRef record, ABPropertyID property) AB_DEPRECATED("use CN object's properties");
AB_EXTERN bool ABRecordSetValue(ABRecordRef record, ABPropertyID property, CFTypeRef value, CFErrorRef* error) AB_DEPRECATED("use CN mutable object's properties");
AB_EXTERN bool ABRecordRemoveValue(ABRecordRef record, ABPropertyID property, CFErrorRef* error) AB_DEPRECATED("use CN mutable object's properties, setting to @"", @[], or nil");
    
AB_EXTERN CFStringRef ABRecordCopyCompositeName(ABRecordRef record) AB_DEPRECATED("use CNContactFormatter or CN object's name");

#endif

