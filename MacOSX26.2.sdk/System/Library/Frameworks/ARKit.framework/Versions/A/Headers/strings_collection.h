#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/strings_collection.h>)
//
//  strings_collection.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef strings_h
#define strings_h

#import <ARKit/object.h>

#import <os/availability.h>

AR_ASSUME_NONNULL_BEGIN

#pragma mark - Strings Collection

AR_OBJECT_DECL(ar_strings)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macos(26.0));

API_UNAVAILABLE_BEGIN(macos);

/**
 Returns the number of strings in this collection.

 @param strings The strings collection.

 @return Count of strings in the collection.
 */
API_AVAILABLE(visionos(26.0))
AR_EXTERN size_t ar_strings_get_count(ar_strings_t strings) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Handler for enumerating a collection of strings.

 @param string An UTF-8 encoded string representation.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(26.0))
typedef bool (^ar_strings_enumerator_t)(const char *string) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of strings.

 @param strings Strings collection.
 @param strings_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_strings_enumerate_strings(ar_strings_t strings, ar_strings_enumerator_t strings_enumerator) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function for enumerating a collection of strings.

 @param context The application-defined context.
 @param string An UTF-8 encoded string representation.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(26.0))
typedef bool (*ar_strings_enumerator_function_t)(void *_Nullable context, const char *string) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of strings using a function.

 @param strings Strings collection.
 @param context The application-defined context parameter to pass to the function.
 @param strings_enumerator_function The enumerator handler.
 */
API_AVAILABLE(visionos(26.0))
AR_EXTERN void ar_strings_enumerate_strings_f(ar_strings_t strings,
                                              void *_Nullable context,
                                              ar_strings_enumerator_function_t strings_enumerator_function) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // strings_h
#else
#import <ARKitCore/strings_collection.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/strings_collection.h>)