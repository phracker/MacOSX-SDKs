#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/data_provider.h>)
//
//  data_provider.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef data_provider_h
#define data_provider_h

#import <ARKit/authorization.h>
#import <ARKit/object.h>

#import <os/availability.h>

AR_ASSUME_NONNULL_BEGIN

#pragma mark - Data Provider

AR_OBJECT_DECL(ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0));

AR_OBJECT_DECL(ar_data_providers)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0));

/**
 State of a data provider.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
OS_ENUM(ar_data_provider_state, intptr_t,
        ar_data_provider_state_initialized,
        ar_data_provider_state_running,
        ar_data_provider_state_paused,
        ar_data_provider_state_stopped
) AR_REFINED_FOR_SWIFT;

/**
 Get the state of a data provider.

 @param data_provider The data provider.

 @return The state of the data provider.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))

AR_EXTERN ar_data_provider_state_t ar_data_provider_get_state(ar_data_provider_t data_provider) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by a data provider.

 @param data_provider The data provider.

 @return The authorization type required by the data provider.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN ar_authorization_type_t ar_data_provider_get_required_authorization_type(ar_data_provider_t data_provider) AR_REFINED_FOR_SWIFT;

#pragma mark - Data Providers Collection

/**
 Create an empty collection of data providers.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_data_providers_t`.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_data_providers_t ar_data_providers_create(void) AR_REFINED_FOR_SWIFT;

/**
 Create a collection of data providers populated with given data providers.

 @param data_provider The nil-terminated list of data providers to add to a newly created collection.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_data_providers_t`.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_data_providers_t ar_data_providers_create_with_data_providers(ar_data_provider_t data_provider, ...)
    NS_REQUIRES_NIL_TERMINATION AR_REFINED_FOR_SWIFT;

/**
 Add a data provider to a collection.

 @param data_providers The collection to expand.
 @param data_provider_to_add The data provider to add.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN void ar_data_providers_add_data_provider(ar_data_providers_t data_providers, ar_data_provider_t data_provider_to_add) AR_REFINED_FOR_SWIFT;

/**
 Add data providers to a collection.

 @param data_providers The collection to expand.
 @param data_providers_to_add The collection of data providers to add.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN void ar_data_providers_add_data_providers(ar_data_providers_t data_providers,
                                                    ar_data_providers_t data_providers_to_add) AR_REFINED_FOR_SWIFT;

/**
 Remove a data provider from a collection.

 @param data_providers The collection from which to remove.
 @param data_provider_to_remove The data provider to remove.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN void ar_data_providers_remove_data_provider(ar_data_providers_t data_providers,
                                                      ar_data_provider_t data_provider_to_remove) AR_REFINED_FOR_SWIFT;

/**
 Remove data providers from a collection.

 @param data_providers The collection from which to remove.
 @param data_providers_to_remove The collection of data providers to remove.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN void ar_data_providers_remove_data_providers(ar_data_providers_t data_providers,
                                                       ar_data_providers_t data_providers_to_remove) AR_REFINED_FOR_SWIFT;

/**
 Get the count of data providers in a collection.

 @param data_providers The collection of data providers.

 @return The number of data providers in the collection.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN size_t ar_data_providers_get_count(ar_data_providers_t data_providers) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of data providers.

 @param data_provider The data provider.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
typedef bool (^ar_data_providers_enumerator_t)(ar_data_provider_t data_provider) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of data providers.

 @param data_providers The collection of data providers.
 @param data_providers_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN void ar_data_providers_enumerate_data_providers(ar_data_providers_t data_providers,
                                                          ar_data_providers_enumerator_t data_providers_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of data providers.

 @param context The application-defined context.
 @param data_provider The data provider.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
typedef bool (*ar_data_providers_enumerator_function_t)(void *_Nullable context, ar_data_provider_t data_provider) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of data providers using a function.

 @param data_providers The collection of data providers.
 @param context The application-defined context parameter to pass to the function.
 @param data_providers_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN void
ar_data_providers_enumerate_data_providers_f(ar_data_providers_t data_providers,
                                             void *_Nullable context,
                                             ar_data_providers_enumerator_function_t data_providers_enumerator_function) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // data_provider_h
#else
#import <ARKitCore/data_provider.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/data_provider.h>)