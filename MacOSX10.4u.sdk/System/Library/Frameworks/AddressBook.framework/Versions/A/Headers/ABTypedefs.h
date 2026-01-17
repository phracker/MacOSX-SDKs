/*
 *  ABTypedefs.h
 *  AddressBook Framework
 *
 *  Copyright (c) 2002-2003 Apple Computer. All rights reserved.
 *
 */

#ifndef __ABTYPEDEFS__
#define __ABTYPEDEFS__

// ================================================================
//      Property Type
// ================================================================

#define kABMultiValueMask        0x100

typedef enum _ABPropertyType {
    kABErrorInProperty           = 0x0,
    kABStringProperty            = 0x1,
    kABIntegerProperty           = 0x2,
    kABRealProperty              = 0x3,
    kABDateProperty              = 0x4,
    kABArrayProperty             = 0x5,
    kABDictionaryProperty        = 0x6,
    kABDataProperty              = 0x7,
    kABMultiStringProperty       = kABMultiValueMask | kABStringProperty,
    kABMultiIntegerProperty      = kABMultiValueMask | kABIntegerProperty,
    kABMultiRealProperty         = kABMultiValueMask | kABRealProperty,
    kABMultiDateProperty         = kABMultiValueMask | kABDateProperty,
    kABMultiArrayProperty        = kABMultiValueMask | kABArrayProperty,
    kABMultiDictionaryProperty   = kABMultiValueMask | kABDictionaryProperty,
    kABMultiDataProperty         = kABMultiValueMask | kABDataProperty
} ABPropertyType;

// ================================================================
//      Search APIs
// ================================================================

typedef enum _ABSearchComparison {
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
} ABSearchComparison;

typedef enum _ABSearchConjunction {
        kABSearchAnd,
        kABSearchOr
} ABSearchConjunction;

#endif
