#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/environment_light_estimation.h>)
//
//  environment_light_estimation.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef environment_light_estimation_h
#define environment_light_estimation_h

#ifdef __OBJC__
#import <Metal/Metal.h>
#endif // __OBJC__

#import <ARKit/anchor.h>
#import <ARKit/data_provider.h>
#import <ARKit/object.h>
#import <ARKit/session.h>

#import <dispatch/dispatch.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL_SUBCLASS(ar_environment_probe_anchor, ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

AR_OBJECT_DECL(ar_environment_probe_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

AR_OBJECT_DECL(ar_environment_light_estimation_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

AR_OBJECT_DECL_SUBCLASS(ar_environment_light_estimation_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

#pragma mark - Environment Probe Anchor

/**
 Returns a bool value that indicates whether the two environment probe anchors are equal.

 @param environment_probe_anchor A environment probe anchor to be compared.
 @param other_environment_probe_anchor The other environment probe anchor to be compared to.

 @return YES if the environment probe anchors are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_environment_probe_anchor_is_equal_to_environment_probe_anchor(
    ar_environment_probe_anchor_t _Nullable environment_probe_anchor,
    ar_environment_probe_anchor_t _Nullable other_environment_probe_anchor) AR_REFINED_FOR_SWIFT;

#ifdef __OBJC__
/**
 Get the environment texture of an environment probe anchor.

 @param environment_probe An environment probe anchor.

 @discussion The texture is provided as a cube using MTLTextureTypeCube,
             containing rgb floating point linear high-dynamic range values in P3 color space.
 @note Textures could be nil if the person is not in a well-lit environment. The lifetime of this texture is tied to the lifetime of the
 `ar_environment_probe_anchor_t`.
 @return Returns a MTLTextureTypeCube.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN id<MTLTexture> _Nullable ar_environment_probe_anchor_get_environment_texture(ar_environment_probe_anchor_t environment_probe)
    AR_REFINED_FOR_SWIFT;
#endif // __OBJC__

/**
 Get the camera scale reference of an environment probe anchor.

 @param environment_probe An environment probe anchor.

 @return Returns the camera scale reference of a pixel with rgb value [1,1,1] in the environment texture.

 @discussion The environment texture stores floating point linear high-dynamic range rgb values in P3 color space.
 In order to have a consistent brightness between texture updates, the cameraScaleReference allows you to translate the local brightness from the
 current environment texture to the absolute brightness range from the camera.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN float ar_environment_probe_anchor_get_camera_scale_reference(ar_environment_probe_anchor_t environment_probe) AR_REFINED_FOR_SWIFT;

#pragma mark - Environment Probe Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 @param[in] anchor The anchor.
 @param[out] out_identifier A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_environment_probe_anchor_get_identifier(ar_environment_probe_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 @param anchor The anchor.

 @return The origin from anchor transform.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_environment_probe_anchor_get_origin_from_anchor_transform(ar_environment_probe_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 @param anchor  The anchor.

 @return The timestamp associated with the anchor.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_environment_probe_anchor_get_timestamp(ar_environment_probe_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Environment Probe Anchors Collection

/**
 Get the count of environment probe anchors in the collection.

 @param environment_probe_anchors The collection of environment probe anchors.

 @return The number of environment probe anchors in the collection.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_environment_probe_anchors_get_count(ar_environment_probe_anchors_t environment_probe_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of environment probe anchors.

 @param environment_probe_anchor The environment probe anchor.

 @return Return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_environment_probe_anchors_enumerator_t)(ar_environment_probe_anchor_t environment_probe_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of environment probe anchors.

 @param environment_probe_anchors The collection of environment probe anchors.
 @param environment_probe_anchors_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_environment_probe_anchors_enumerate_anchors(ar_environment_probe_anchors_t environment_probe_anchors,
                                               ar_environment_probe_anchors_enumerator_t environment_probe_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of environment probe anchors.

 @param context The application-defined context.
 @param environment_probe_anchor The environment probe anchor.

 @return Return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_environment_probe_anchors_enumerator_function_t)(void *_Nullable context,
                                                                   ar_environment_probe_anchor_t environment_probe_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of environment probe anchors.

 @param environment_probe_anchors The collection of environment probe anchors.
 @param context The application-defined context parameter to pass to the function.
 @param environment_probe_anchors_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_environment_probe_anchors_enumerate_anchors_f(
    ar_environment_probe_anchors_t environment_probe_anchors,
    void *_Nullable context,
    ar_environment_probe_anchors_enumerator_function_t environment_probe_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Environment Light Estimation Configuration

/**
 Create an environment light estimation configuration.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_environment_light_estimation_configuration_t`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_environment_light_estimation_configuration_t ar_environment_light_estimation_configuration_create(void)
    AR_REFINED_FOR_SWIFT;

#pragma mark - Environment Light Estimation Provider

#ifdef __BLOCKS__
/**
 Handler triggered when there are updates to environment probe anchors.

 @param added_anchors Collection of anchors that are added.
 @param updated_anchors Collection of anchors that are updated.
 @param removed_anchors Collection of anchors that are removed.
 */
API_AVAILABLE(visionos(2.0))
typedef void (^ar_environment_light_estimation_update_handler_t)(ar_environment_probe_anchors_t added_anchors,
                                                                 ar_environment_probe_anchors_t updated_anchors,
                                                                 ar_environment_probe_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function to be called when there are updates to environment probe anchors.

 @param context The application-defined context.
 @param added_anchors Collection of anchors that are added.
 @param updated_anchors Collection of anchors that are updated.
 @param removed_anchors Collection of anchors that are removed.
 */
API_AVAILABLE(visionos(2.0))
typedef void (*ar_environment_light_estimation_update_handler_function_t)(void *_Nullable context,
                                                                          ar_environment_probe_anchors_t added_anchors,
                                                                          ar_environment_probe_anchors_t updated_anchors,
                                                                          ar_environment_probe_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Create an environment light estimation provider.

 @param environment_light_estimation_configuration Environment light estimation configuration.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_environment_light_estimation_provider_t`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_environment_light_estimation_provider_t ar_environment_light_estimation_provider_create(
    ar_environment_light_estimation_configuration_t environment_light_estimation_configuration) AR_REFINED_FOR_SWIFT;

/**
 Determines whether this device supports the environment light estimation provider.

 @return Returns `true` if the environment light estimation provider is supported on this device, `false` otherwise.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_environment_light_estimation_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Set the handler for receiving environment light estimation updates.

 @param environment_light_estimation_provider Environment light estimation provider.
 @param environment_light_estimation_anchor_updates_queue Queue on which the handler will be executed,
 sending NULL will default to the main queue.
 @param environment_light_estimation_update_handler Handler to be triggered when new data
 arrives.

 @note Setting this function will override the handler set using `ar_environment_light_estimation_provider_set_probe_update_handler_f`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_environment_light_estimation_provider_set_update_handler(
    ar_environment_light_estimation_provider_t environment_light_estimation_provider,
    dispatch_queue_t _Nullable environment_light_estimation_anchor_updates_queue,
    ar_environment_light_estimation_update_handler_t _Nullable environment_light_estimation_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Set the function for receiving environment light estimation updates.

 @param environment_light_estimation_provider Environment light estimation provider.
 @param environment_light_estimation_anchor_updates_queue Queue on which the function will be called. Passing NULL will default to the main queue.
 @param context The application-defined context parameter to pass to the function.
 @param environment_light_estimation_update_handler_function The function to be called when new data arrives.

 @note Setting this function will override the handler set using `ar_environment_light_estimation_provider_set_probe_update_handler`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_environment_light_estimation_provider_set_update_handler_f(
    ar_environment_light_estimation_provider_t environment_light_estimation_provider,
    dispatch_queue_t _Nullable environment_light_estimation_anchor_updates_queue,
    void *_Nullable context,
    ar_environment_light_estimation_update_handler_function_t _Nullable environment_light_estimation_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the environment light estimation provider.

 @return Authorization type.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_authorization_type_t ar_environment_light_estimation_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // environment_light_estimation_h
#else
#import <ARKitCore/environment_light_estimation.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/environment_light_estimation.h>)