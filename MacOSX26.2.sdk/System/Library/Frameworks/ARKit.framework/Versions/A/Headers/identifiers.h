#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/identifiers.h>)
//
//  identifiers.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef identifiers_h
#define identifiers_h

#import <ARKit/object.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL(ar_identifiers)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

#pragma mark - Identifiers Collection

/**
 Returns a bool value that indicates whether the two collections of identifiers are equal.

 @param identifiers A collection of identifiers to be compared.
 @param other_identifiers The other collection of identifiers to be compared to.

 @return YES if the collections of identifiers are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_identifiers_is_equal_to_identifiers(ar_identifiers_t _Nullable identifiers,
                                                      ar_identifiers_t _Nullable other_identifiers) AR_REFINED_FOR_SWIFT;

/**
 Get the count of identifiers in a collection.

 @param identifiers The collection of identifiers.

 @return The number of identifiers in the collection.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_identifiers_get_count(ar_identifiers_t identifiers) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of identifiers.

 @param identifier The identifier.

 @note The `identifier` will have the same lifetime as the scope of the enumerator.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_identifiers_enumerator_t)(uuid_t _Nonnull identifier) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of identifiers.

 @param identifiers The collection of identifiers.
 @param identifiers_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_identifiers_enumerate_identifiers(ar_identifiers_t identifiers,
                                                    ar_identifiers_enumerator_t identifiers_enumerator) AR_REFINED_FOR_SWIFT;

#endif // __BLOCKS__

/**
 Function for enumerating a collection of identifiers.

 @param context The application-defined context.
 @param identifier The identifier.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_identifiers_enumerator_function_t)(void *_Nullable context, uuid_t _Nonnull identifier) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of identifiers using a function.

 @param identifiers The collection of identifiers.
 @param context The application-defined context parameter to pass to the function.
 @param identifiers_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_identifiers_enumerate_identifiers_f(ar_identifiers_t identifiers,
                                                      void *_Nullable context,
                                                      ar_identifiers_enumerator_function_t identifiers_enumerator_function) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif /* identifiers_h */
#else
#import <ARKitCore/identifiers.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/identifiers.h>)