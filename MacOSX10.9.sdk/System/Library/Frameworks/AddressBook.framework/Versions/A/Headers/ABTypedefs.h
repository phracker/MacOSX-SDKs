/*
 *  ABTypedefs.h
 *  AddressBook Framework
 *
 *  Copyright (c) 2003-2007 Apple Inc.  All rights reserved.
 *
 */

#ifndef __ABTYPEDEFS__
#define __ABTYPEDEFS__

#include <CoreFoundation/CoreFoundation.h>

// These typedefs are CFIndexes rather then NSIntegers because
// they're used in the C API as well as the Obj-C one.

// ================================================================
//      Property Type
// ================================================================

#define kABMultiValueMask        0x100

enum _ABPropertyType {
    kABErrorInProperty           = 0x0,
    kABStringProperty            = 0x1,
    kABIntegerProperty           = 0x2,
    kABRealProperty              = 0x3,
    kABDateProperty              = 0x4,
    kABArrayProperty             = 0x5,
    kABDictionaryProperty        = 0x6,
    kABDataProperty              = 0x7,
#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED
	kABDateComponentsProperty    = 0x8,
#endif
    kABMultiStringProperty       = kABMultiValueMask | kABStringProperty,
    kABMultiIntegerProperty      = kABMultiValueMask | kABIntegerProperty,
    kABMultiRealProperty         = kABMultiValueMask | kABRealProperty,
    kABMultiDateProperty         = kABMultiValueMask | kABDateProperty,
    kABMultiArrayProperty        = kABMultiValueMask | kABArrayProperty,
    kABMultiDictionaryProperty   = kABMultiValueMask | kABDictionaryProperty,
    kABMultiDataProperty         = kABMultiValueMask | kABDataProperty,
#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED
	kABMultiDateComponentsProperty = kABMultiValueMask | kABDateComponentsProperty
#endif
};
typedef CFIndex ABPropertyType;

// ================================================================
//      Search APIs
// ================================================================

enum _ABSearchComparison {
        kABEqual,
        kABNotEqual,
        kABLessThan,
        kABLessThanOrEqual,
        kABGreaterThan,
        kABGreaterThanOrEqual,

        kABEqualCaseInsensitive,
        kABContainsSubString,
        kABContainsSubStringCaseInsensitive,
        kABPrefixMatch,
        kABPrefixMatchCaseInsensitive,
#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED
        kABBitsInBitFieldMatch,
#endif
#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED
        kABDoesNotContainSubString,
        kABDoesNotContainSubStringCaseInsensitive,
        kABNotEqualCaseInsensitive,
        kABSuffixMatch,
        kABSuffixMatchCaseInsensitive,
        kABWithinIntervalAroundToday,
        kABWithinIntervalAroundTodayYearless,
        kABNotWithinIntervalAroundToday,
        kABNotWithinIntervalAroundTodayYearless,
        kABWithinIntervalFromToday,
        kABWithinIntervalFromTodayYearless,
        kABNotWithinIntervalFromToday,
        kABNotWithinIntervalFromTodayYearless
#endif
};
typedef CFIndex ABSearchComparison;

enum _ABSearchConjunction {
        kABSearchAnd,
        kABSearchOr
};
typedef CFIndex ABSearchConjunction;


#endif
