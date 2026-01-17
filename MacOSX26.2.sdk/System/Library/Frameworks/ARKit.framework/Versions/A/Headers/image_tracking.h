#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/image_tracking.h>)
//
//  image_tracking.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef image_tracking_h
#define image_tracking_h

#import <ARKit/anchor.h>
#import <ARKit/data_provider.h>
#import <ARKit/object.h>
#import <ARKit/session.h>

#import <CoreVideo/CVPixelBuffer.h>
#import <ImageIO/CGImageProperties.h>
#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/simd.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL_SUBCLASS(ar_image_anchor, ar_trackable_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_image_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_reference_image)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_reference_images)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_image_tracking_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL_SUBCLASS(ar_image_tracking_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

#pragma mark - Image Anchor

/**
 Returns a bool value that indicates whether the two image anchors are equal.

 @param anchor A image anchor to be compared.
 @param other_anchor The other image anchor to be compared to.

 @return YES if the image anchors are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_image_anchor_is_equal_to_image_anchor(ar_image_anchor_t _Nullable anchor,
                                                        ar_image_anchor_t _Nullable other_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the estimated scale factor from an image anchor.

 @param image_anchor The image anchor.

 @return The factor between estimated physical size and provided size.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN float ar_image_anchor_get_estimated_scale_factor(ar_image_anchor_t image_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the underlying tracked reference image from an image anchor.

 @param image_anchor The image anchor to get the reference image from.

 @note This type supports ARC.
 @return An instance of `ar_reference_image_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_reference_image_t ar_image_anchor_get_reference_image(ar_image_anchor_t image_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Image Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 @param[in] anchor The anchor.
 @param[out] out_identifier A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_image_anchor_get_identifier(ar_image_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 @param anchor The anchor.

 @return The origin from anchor transform.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_image_anchor_get_origin_from_anchor_transform(ar_image_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 @param anchor  The anchor.

 @return The timestamp associated with the anchor.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_image_anchor_get_timestamp(ar_image_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether an anchor is tracked.

 @param anchor The anchor.

 @return `true` if the anchor is tracked, `false` otherwise.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_image_anchor_is_tracked(ar_image_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Image Anchors Collection

/**
 Get the count of image anchors in a collection.

 @param image_anchors The collection of image anchors.

 @return The number of image anchors in the collection.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_image_anchors_get_count(ar_image_anchors_t image_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of image anchors.

 @param image_anchor The image anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (^ar_image_anchors_enumerator_t)(ar_image_anchor_t image_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of image anchors.

 @param image_anchors The collection of image anchors.
 @param image_anchors_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_image_anchors_enumerate_anchors(ar_image_anchors_t image_anchors,
                                                  ar_image_anchors_enumerator_t image_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of image anchors.

 @param context The application-defined context.
 @param image_anchor The image anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (*ar_image_anchors_enumerator_function_t)(void *_Nullable context, ar_image_anchor_t image_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of image anchors using a function.

 @param image_anchors The collection of image anchors.
 @param context The application-defined context parameter to pass to the function.
 @param image_anchors_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_image_anchors_enumerate_anchors_f(ar_image_anchors_t image_anchors,
                                                    void *_Nullable context,
                                                    ar_image_anchors_enumerator_function_t image_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Reference Image

/**
 Create a reference image from a `CVPixelBufferRef`.

 @param pixelBuffer The reference image as  `CVPixelBuffer`.
 @param orientation The image orientation.
 @param physicalWidth The width of the physical object, in meters.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_reference_image_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_reference_image_t ar_reference_image_create_from_pixel_buffer(CVPixelBufferRef pixelBuffer,
                                                                                                      CGImagePropertyOrientation orientation,
                                                                                                      float physicalWidth) AR_REFINED_FOR_SWIFT;

/**
 Create a reference image from a `CGImageRef`.

 @param image The reference image as `CGImageRef`.
 @param orientation The image orientation.
 @param physicalWidth The width of the physical object, in meters.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_reference_image_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_reference_image_t ar_reference_image_create_from_cgimage(CGImageRef image,
                                                                                                 CGImagePropertyOrientation orientation,
                                                                                                 float physicalWidth) AR_REFINED_FOR_SWIFT;

/**
 Returns a bool value that indicates whether the two reference images are equal.

 @param reference_image A reference image to be compared.
 @param other_reference_image The other reference image to be compared to.

 @return YES if the reference images are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_reference_image_is_equal_to_reference_image(ar_reference_image_t _Nullable reference_image,
                                                              ar_reference_image_t _Nullable other_reference_image) AR_REFINED_FOR_SWIFT;

/**
 Set a reference image's name.

 @param reference_image The reference image.
 @param name The name to identify the reference image with, or NULL to reset the name.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_reference_image_set_name(ar_reference_image_t reference_image, const char *_Nullable name) AR_REFINED_FOR_SWIFT;

/**
 Get a reference image's name.

 @param reference_image The reference image.

 @note The returned value will have the same lifetime as the input `ar_reference_image_t`.
 @return The name of the reference image, or NULL if no name is set.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN const char *_Nullable ar_reference_image_get_name(ar_reference_image_t reference_image) AR_REFINED_FOR_SWIFT;

/**
 Get a reference image's resource group name.

 @param reference_image The reference image.

 @note The returned value will have the same lifetime as the input `ar_reference_image_t`.
 @return The resource group name of the reference image, or NULL if it is not set. It will only be set if the reference image was loaded from a
 resource group.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN const char *_Nullable ar_reference_image_get_resource_group_name(ar_reference_image_t reference_image) AR_REFINED_FOR_SWIFT;

/**
 Get the width of a reference image, in meters.

 @param reference_image The reference image.

 @return The physical width of the reference image, in meters.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN float ar_reference_image_get_physical_width(ar_reference_image_t reference_image) AR_REFINED_FOR_SWIFT;

/**
 Get the height of a reference image, in meters.

 @param reference_image The reference image.

 @return The physical height of the image, in meters.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN float ar_reference_image_get_physical_height(ar_reference_image_t reference_image) AR_REFINED_FOR_SWIFT;

#pragma mark - Reference Images Collection

/**
 Create an empty collection of reference images.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_reference_images_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_reference_images_t ar_reference_images_create(void) AR_REFINED_FOR_SWIFT;

/**
 Load reference images from a bundle into a new collection.

 @param group_name The group to load images from.
 @param bundle The bundle to load. If NULL, the main bundle will be loaded.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_reference_images_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_reference_images_t
ar_reference_images_load_reference_images_in_group(const char *group_name, CFBundleRef _Nullable bundle) AR_REFINED_FOR_SWIFT;

/**
 Add a reference image to a collection.

 @discussion The image must be unique. A duplicate of any existing image in the collection will not be added.

 @param reference_images The collection of reference images to expand.
 @param image_to_add The reference image to add.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_reference_images_add_image(ar_reference_images_t reference_images, ar_reference_image_t image_to_add) AR_REFINED_FOR_SWIFT;

/**
 Add reference images to a collection.

 @discussion The images must be unique. Duplicates of any existing image in the collection will not be added.

 @param reference_images The collection of reference images to expand.
 @param images_to_add The collection of reference images to add.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_reference_images_add_images(ar_reference_images_t reference_images, ar_reference_images_t images_to_add) AR_REFINED_FOR_SWIFT;

/**
 Get the count of reference images in the collection.

 @param reference_images The collection of reference images.

 @return The number of reference images in the collection.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_reference_images_get_count(ar_reference_images_t reference_images) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of reference images.

 @param reference_image The reference image.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (^ar_reference_images_enumerator_t)(ar_reference_image_t reference_image) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of reference images.

 @param reference_images The collection of reference images.
 @param reference_images_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_reference_images_enumerate_images(ar_reference_images_t reference_images,
                                                    ar_reference_images_enumerator_t reference_images_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of reference images.

 @param context The application-defined context.
 @param reference_image The reference image.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (*ar_reference_images_enumerator_function_t)(void *_Nullable context, ar_reference_image_t reference_image) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of reference images using a function.

 @param reference_images The collection of reference images.
 @param context The application-defined context parameter to pass to the function.
 @param reference_images_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void
ar_reference_images_enumerate_images_f(ar_reference_images_t reference_images,
                                       void *_Nullable context,
                                       ar_reference_images_enumerator_function_t reference_images_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Image Tracking Configuration

/**
 Create an image tracking configuration.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_image_tracking_configuration_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_image_tracking_configuration_t ar_image_tracking_configuration_create(void) AR_REFINED_FOR_SWIFT;

/**
 Add reference images to the set of images to be tracked. The image tracking configuration can run without any reference images, but will not detect
 anything.

 @param image_tracking_configuration The configuration for image tracking.
 @param reference_images The reference images to add.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_image_tracking_configuration_add_reference_images(ar_image_tracking_configuration_t image_tracking_configuration,
                                                                    ar_reference_images_t reference_images) AR_REFINED_FOR_SWIFT;

#pragma mark - Image Tracking Provider

/**
 Create an image tracking provider.

 @param image_tracking_configuration The configuration for image tracking.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_image_tracking_provider_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_image_tracking_provider_t
ar_image_tracking_provider_create(ar_image_tracking_configuration_t image_tracking_configuration) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when there are updates to image anchors.

 @param added_anchors The collection of anchors that were added.
 @param updated_anchors The collection of anchors that were updated.
 @param removed_anchors The collection of anchors that were removed.
 */
API_AVAILABLE(visionos(1.0))
typedef void (^ar_image_tracking_update_handler_t)(ar_image_anchors_t added_anchors,
                                                   ar_image_anchors_t updated_anchors,
                                                   ar_image_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving image tracking updates.

 @param image_tracking_provider The image tracking provider.
 @param image_tracking_updates_queue The queue on which the handler will be called. Passing NULL will default to the main queue.
 @param image_tracking_update_handler The handler to be called when new image tracking data arrives.

 @note Setting this handler will override the function set using `ar_image_tracking_provider_set_update_handler_f`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void
ar_image_tracking_provider_set_update_handler(ar_image_tracking_provider_t image_tracking_provider,
                                              dispatch_queue_t _Nullable image_tracking_updates_queue,
                                              ar_image_tracking_update_handler_t _Nullable image_tracking_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when there are updates to image anchors.

 @param context The application-defined context.
 @param added_anchors The collection of anchors that were added.
 @param updated_anchors The collection of anchors that were updated.
 @param removed_anchors The collection of anchors that were removed.
 */
API_AVAILABLE(visionos(1.0))
typedef void (*ar_image_tracking_update_handler_function_t)(void *_Nullable context,
                                                            ar_image_anchors_t added_anchors,
                                                            ar_image_anchors_t updated_anchors,
                                                            ar_image_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving image tracking updates.

 @param image_tracking_provider The image tracking provider.
 @param image_tracking_updates_queue The queue on which the function will be called. Passing NULL will default to the main queue.
 @param context The application-defined context parameter to pass to the function.
 @param image_tracking_update_handler_function The function to be called when new image tracking data arrives.

 @note Setting this function will override the handler set using `ar_image_tracking_provider_set_update_handler`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_image_tracking_provider_set_update_handler_f(
    ar_image_tracking_provider_t image_tracking_provider,
    dispatch_queue_t _Nullable image_tracking_updates_queue,
    void *_Nullable context,
    ar_image_tracking_update_handler_function_t _Nullable image_tracking_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Copy all image anchors.

 @param image_tracking_provider The image tracking provider.

 @return The collection of all image anchors. This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the
 object.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_image_anchors_t
ar_image_tracking_provider_copy_all_image_anchors(ar_image_tracking_provider_t image_tracking_provider) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the image tracking provider.

 @return `true` if the image tracking provider is supported on this device, `false` otherwise.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN bool ar_image_tracking_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the image tracking provider.

 @return The required authorization type.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_authorization_type_t ar_image_tracking_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // image_tracking_h
#else
#import <ARKitCore/image_tracking.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/image_tracking.h>)