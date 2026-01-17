#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/stereo_properties.h>)
//
//  stereo_properties.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef stereo_properties_h
#define stereo_properties_h

#import <ARKit/data_provider.h>
#import <ARKit/object.h>
#import <ARKit/session.h>

#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL(ar_stereo_properties_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.4));

AR_OBJECT_DECL_SUBCLASS(ar_stereo_properties_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.4));

AR_OBJECT_DECL(ar_viewpoint_properties)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.4));

#pragma mark - Viewpoint Properties

/**
 Create an `ar_viewpoint_properties_t`.

 @return A new `ar_viewpoint_properties_t`.
 */
API_AVAILABLE(visionos(2.4))
AR_EXTERN ar_viewpoint_properties_t ar_viewpoint_properties_create(void) AR_REFINED_FOR_SWIFT;

/**
 Get the transformation matrix that converts from the left viewpoint to the device’s coordinate space.

 @param viewpoint_properties The viewpoint properties.

 @return The transform from the left viewpoint to the device origin.
 */
API_AVAILABLE(visionos(2.4))
AR_EXTERN simd_float4x4 ar_viewpoint_properties_get_device_from_left_viewpoint_transform(ar_viewpoint_properties_t viewpoint_properties)
    AR_REFINED_FOR_SWIFT;

/**
 Get the transformation matrix that converts from the right viewpoint to the device’s coordinate space.

 @param viewpoint_properties The viewpoint properties.

 @return The transform from the right viewpoint to the device origin.
 */
API_AVAILABLE(visionos(2.4))
AR_EXTERN simd_float4x4 ar_viewpoint_properties_get_device_from_right_viewpoint_transform(ar_viewpoint_properties_t viewpoint_properties)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Stereo Properties Configuration

/**
 Create a stereo properties configuration object.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_stereo_properties_configuration_t`.
 */
API_AVAILABLE(visionos(2.4))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_stereo_properties_configuration_t ar_stereo_properties_configuration_create(void) AR_REFINED_FOR_SWIFT;

#pragma mark - Stereo Properties Provider

/**
 Create a stereo properties provider.

 @param configuration The configuration for the stereo properties provider.
 @see `ar_session_t` to run this provider.
 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_stereo_properties_provider_t`.
 */
API_AVAILABLE(visionos(2.4))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_stereo_properties_provider_t
ar_stereo_properties_provider_create(ar_stereo_properties_configuration_t configuration) AR_REFINED_FOR_SWIFT;

/**
 Determines whether this device supports the stereo properties provider.

 @return Returns `true` if the stereo properties provider is supported on this device, `false` otherwise.
 */
API_AVAILABLE(visionos(2.4))
AR_EXTERN bool ar_stereo_properties_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the stereo properties provider.

 @return Authorization type.
 */
API_AVAILABLE(visionos(2.4))
AR_EXTERN ar_authorization_type_t ar_stereo_properties_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

/**
 Returns the latest viewpoint properties.

 @param stereo_properties_provider The stereo properties provider.
 @param[out] viewpoint_properties The viewpoint properties to fill out.
 @returns True, if the viewpoint properties were updated.
 */
API_AVAILABLE(visionos(2.4))
AR_EXTERN bool ar_stereo_properties_provider_get_viewpoint_properties(ar_stereo_properties_provider_t stereo_properties_provider,
                                                                      ar_viewpoint_properties_t viewpoint_properties) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // stereo_properties_h
#else
#import <ARKitCore/stereo_properties.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/stereo_properties.h>)