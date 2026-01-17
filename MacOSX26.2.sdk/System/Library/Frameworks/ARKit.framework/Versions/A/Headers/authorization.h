#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/authorization.h>)
//
//  authorization.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef authorization_h
#define authorization_h

#import <ARKit/object.h>

AR_ASSUME_NONNULL_BEGIN

#pragma mark - Authorization Result

/**
 Status of an authorization for ARKit data.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
OS_ENUM(ar_authorization_status, intptr_t,
        // The user has not yet granted permission.
        ar_authorization_status_not_determined,
        // The user has explicitly granted permission.
        ar_authorization_status_allowed,
        // The user has explicitly denied permission.
        ar_authorization_status_denied)
AR_REFINED_FOR_SWIFT;

/**
 Types of authorization for ARKit data.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
OS_OPTIONS(ar_authorization_type, uintptr_t,
           ar_authorization_type_none = 0,
           /**
            Authorization type used when requesting hand tracking.
            @see `ar_hand_tracking_provider_t`
            */
           ar_authorization_type_hand_tracking = (1 << 0),
           /** Authorization type used when requesting:
                - Image tracking
                    @see `ar_image_tracking_provider_t`
                - Plane detection
                    @see `ar_plane_detection_provider_t`
                - Scene reconstruction
                    @see `ar_scene_reconstruction_provider_t`
            */
           ar_authorization_type_world_sensing = (1 << 1),
           /** Authorization type used when requesting:
                - Camera access
                    @see `ar_camera_frame_provider_t`
            */
           ar_authorization_type_camera_access API_AVAILABLE(visionos(2.0)) = (1 << 3),

           )
AR_REFINED_FOR_SWIFT;

AR_OBJECT_DECL(ar_authorization_result)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0));

/**
 Get the authorization type associated with an authorization result.

 @param authorization_result The authorization result.

 @return The authorization type.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN ar_authorization_type_t ar_authorization_result_get_authorization_type(ar_authorization_result_t authorization_result) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization status associated with an authorization result.

 @param authorization_result The authorization result.

 @return The authorization status.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN ar_authorization_status_t ar_authorization_result_get_status(ar_authorization_result_t authorization_result) AR_REFINED_FOR_SWIFT;

#pragma mark - Authorization Results

AR_OBJECT_DECL(ar_authorization_results)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0));

/**
 Get the count of authorization results in a collection.

 @param authorization_results The collection of authorization results.

 @return The number of authorization results in the collection.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN size_t ar_authorization_results_get_count(ar_authorization_results_t authorization_results) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of authorization results.

 @param authorization_result The authorization result.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
typedef bool (^ar_authorization_results_enumerator_t)(ar_authorization_result_t authorization_result) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of authorization results.

 @param authorization_results The collection of authorization results.
 @param authorization_results_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN void
ar_authorization_results_enumerate_results(ar_authorization_results_t authorization_results,
                                           ar_authorization_results_enumerator_t authorization_results_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of authorization results.

 @param context The application-defined context.
 @param authorization_result The authorization result.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
typedef bool (*ar_authorization_results_enumerator_function_t)(void *_Nullable context,
                                                               ar_authorization_result_t authorization_result) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of authorization results using a function.

 @param authorization_results The collection of authorization results.
 @param context The application-defined context parameter to pass to the function.
 @param authorization_results_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN void ar_authorization_results_enumerate_results_f(ar_authorization_results_t authorization_results,
                                                            void *_Nullable context,
                                                            ar_authorization_results_enumerator_function_t authorization_results_enumerator_function)
    AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // authorization_h
#else
#import <ARKitCore/authorization.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/authorization.h>)