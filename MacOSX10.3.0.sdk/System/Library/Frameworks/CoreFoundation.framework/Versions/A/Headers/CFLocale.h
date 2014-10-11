/*	CFLocale.h
	Copyright (c) 2002-2003, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFLOCALE__)
#define __COREFOUNDATION_CFLOCALE__ 1

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

#include <CoreFoundation/CFBase.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef const struct __CFLocale *CFLocaleRef;

CF_EXPORT
CFTypeID CFLocaleGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

CF_EXPORT
CFLocaleRef CFLocaleGetSystem(void) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Returns the "root", canonical locale.  Contains fixed "backstop" settings.

CF_EXPORT
CFLocaleRef CFLocaleCopyCurrent(void) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Returns the logical "user" locale for the current user.
	// [This is Copy in the sense that you get a retain you have to release,
	// but we may return the same cached object over and over.]  Settings
	// you get from this locale do not change under you as CFPreferences
	// are changed (for safety and correctness).  Generally you would not
	// grab this and hold onto it forever, but use it to do the operations
	// you need to do at the moment, then throw it away.  (The non-changing
	// ensures that all the results of your operations are consistent.)

CF_EXPORT
CFStringRef CFLocaleCreateCanonicalLocaleIdentifierFromString(CFAllocatorRef allocator, CFStringRef localeIdentifier) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Map an arbitrary locale identification string (something close at
	// least) to the canonical identifier.

CF_EXPORT
CFStringRef CFLocaleCreateCanonicalLocaleIdentifierFromScriptManagerCodes(CFAllocatorRef allocator, LangCode lcode, RegionCode rcode) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Map a Mac OS LangCode and RegionCode to the canonical locale identifier.

CF_EXPORT
CFLocaleRef CFLocaleCreate(CFAllocatorRef allocator, CFStringRef localeIdentifier) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Returns a CFLocaleRef for the locale named by the "arbitrary" locale identifier.

CF_EXPORT
CFLocaleRef CFLocaleCreateCopy(CFAllocatorRef allocator, CFLocaleRef locale) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Having gotten a CFLocale from somebody, code should make a copy
	// if it is going to use it for several operations
	// or hold onto it.  In the future, there may be mutable locales.

CF_EXPORT
CFStringRef CFLocaleGetIdentifier(CFLocaleRef locale) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Returns the locale's identifier.  This may not be the same string
	// that the locale was created with (CFLocale may canonicalize it).

CF_EXPORT
CFTypeRef CFLocaleGetValue(CFLocaleRef locale, CFStringRef key) AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
	// Returns the value for the given key.  This is how settings and state
	// are accessed via a CFLocale.  Values might be of any CF type.


// Locale Keys
CF_EXPORT const CFStringRef kCFLocaleMeasurementSystem AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; // "Metric" or "U.S."
CF_EXPORT const CFStringRef kCFLocaleDecimalSeparator AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
CF_EXPORT const CFStringRef kCFLocaleGroupingSeparator AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
CF_EXPORT const CFStringRef kCFLocaleCurrencySymbol AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;
CF_EXPORT const CFStringRef kCFLocaleCurrencyCode AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER; // ISO 3-letter currency code


#if defined(__cplusplus)
}
#endif

#endif

#endif /* ! __COREFOUNDATION_CFLOCALE__ */

