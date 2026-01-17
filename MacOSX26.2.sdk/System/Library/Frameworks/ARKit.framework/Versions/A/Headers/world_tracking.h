#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/world_tracking.h>)
//
//  world_tracking.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef world_tracking_h
#define world_tracking_h

#import <ARKit/anchor.h>
#import <ARKit/data_provider.h>
#import <ARKit/object.h>
#import <ARKit/session.h>

#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/types.h>
#import <uuid/uuid.h>

AR_ASSUME_NONNULL_BEGIN

AR_OBJECT_DECL_SUBCLASS(ar_world_anchor, ar_trackable_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos);

AR_OBJECT_DECL(ar_world_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos);

AR_OBJECT_DECL(ar_world_tracking_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0));

AR_OBJECT_DECL_SUBCLASS(ar_world_tracking_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0));

#pragma mark - World Anchor

/**
 Returns a bool value that indicates whether the two world anchors are equal.

 @param anchor A world anchor to be compared.
 @param other_anchor The other world anchor to be compared to.

 @return YES if the world anchors are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
AR_EXTERN bool ar_world_anchor_is_equal_to_world_anchor(ar_world_anchor_t _Nullable anchor,
                                                        ar_world_anchor_t _Nullable other_anchor) AR_REFINED_FOR_SWIFT;

/**
 Create a world anchor initialized with a transform from the anchor to the origin coordinate system.

 @param origin_from_anchor_transform The origin from anchor transform.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_world_anchor_t`.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_world_anchor_t
ar_world_anchor_create_with_origin_from_anchor_transform(simd_float4x4 origin_from_anchor_transform) AR_REFINED_FOR_SWIFT;

#pragma mark - World Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 @param[in] anchor The anchor.
 @param[out] out_identifier A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_anchor_get_identifier(ar_world_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 @param anchor The anchor.

 @return The origin from anchor transform.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
AR_EXTERN simd_float4x4 ar_world_anchor_get_origin_from_anchor_transform(ar_world_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 @param anchor  The anchor.

 @return The timestamp associated with the anchor.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
AR_EXTERN CFTimeInterval ar_world_anchor_get_timestamp(ar_world_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether an anchor is tracked.

 @param anchor The anchor.

 @return `true` if the anchor is tracked, `false` otherwise.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
AR_EXTERN bool ar_world_anchor_is_tracked(ar_world_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - World Anchors Collection

/**
 Get the count of world anchors in a collection.

 @param world_anchors The collection of world anchors.

 @return The number of world anchors in the collection.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN size_t ar_world_anchors_get_count(ar_world_anchors_t world_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of world anchors.

 @param world_anchor The world anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
typedef bool (^ar_world_anchors_enumerator_t)(ar_world_anchor_t world_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of world anchors.

 @param world_anchors The collection of world anchors.
 @param world_anchors_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_anchors_enumerate_anchors(ar_world_anchors_t world_anchors,
                                                  ar_world_anchors_enumerator_t world_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of world anchors.

 @param context The application-defined context.
 @param world_anchor The world anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
typedef bool (*ar_world_anchors_enumerator_function_t)(void *_Nullable context, ar_world_anchor_t world_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of world anchors using a function.

 @param world_anchors The collection of world anchors.
 @param context The application-defined context parameter to pass to the function.
 @param world_anchors_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_anchors_enumerate_anchors_f(ar_world_anchors_t world_anchors,
                                                    void *_Nullable context,
                                                    ar_world_anchors_enumerator_function_t world_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - World Tracking Configuration

/**
 Create a world tracking configuration.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_world_tracking_configuration_t`.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_world_tracking_configuration_t ar_world_tracking_configuration_create(void) AR_REFINED_FOR_SWIFT;

#pragma mark - World Tracking Provider

/**
 Create a world tracking provider.

 @param world_tracking_configuration The configuration for world tracking.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_world_tracking_provider_t`.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_world_tracking_provider_t
ar_world_tracking_provider_create(ar_world_tracking_configuration_t world_tracking_configuration) AR_REFINED_FOR_SWIFT;

/**
 Function called when a request to copy all known world anchors has completed (successfully or not).

 @param all_anchors The nullable collection of known world anchors. Passes null if data provider is not running and for other errors.

 @note The results will be accurate at the time of callback, but not necessarily at the time of the request.
 @note The returned anchors support ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the anchors.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
typedef void (*ar_world_tracking_provider_copy_all_world_anchors_completion_function_t)(
    void *_Nullable context, ar_world_anchors_t _Nullable all_anchors) AR_REFINED_FOR_SWIFT;

/**
 Copies all known world anchors from the world tracking provider asynchronously.

 @param world_tracking_provider The world tracking provider.
 @param context The application-defined context parameter to pass to the function.
 @param copy_all_anchors_completion_handler_function The function to be called with the result of the request for all known world anchors.

 @note This is not a blocking call. It will return all anchors that have been added successfully before the completion handler is called.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_copy_all_world_anchors_f(
    ar_world_tracking_provider_t world_tracking_provider,
    void *_Nullable context,
    ar_world_tracking_provider_copy_all_world_anchors_completion_function_t _Nullable copy_all_anchors_completion_handler_function)
    AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when a request to copy all known world anchors has completed (successfully or not).

 @param all_anchors The nullable collection of known world anchors. Passes null if data provider is not running and for other errors.

 @note The results will be accurate at the time of callback, but not necessarily at the time of the request.
 @note The returned anchors support ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the anchors.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
typedef void (^ar_world_tracking_provider_copy_all_world_anchors_completion_handler_t)(ar_world_anchors_t _Nullable all_anchors) AR_REFINED_FOR_SWIFT;

/**
 Copies all known world anchors from the world tracking provider asynchronously.

 @param world_tracking_provider The world tracking provider.
 @param copy_all_anchors_completion_handler The handler to be called with the result of the request for all known world anchors.

 @note This is not a blocking call. It will return all anchors that have been added successfully before the completion handler is called.
 */
API_AVAILABLE(visionos(2.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_copy_all_world_anchors(
    ar_world_tracking_provider_t world_tracking_provider,
    ar_world_tracking_provider_copy_all_world_anchors_completion_handler_t copy_all_anchors_completion_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

#ifdef __BLOCKS__
/**
 Handler called when there are updates to world anchors. This includes updates to persisted world anchors from previous runs of the app.

 @param added_anchors The collection of world anchors that were added.
 @param updated_anchors The collection of world anchors that were updated.
 @param removed_anchors The collection of world anchors that were removed.

 @note This handler will also be called for persisted world anchors from previous runs of the app, after the world tracking provider has been started.
 World anchors persist across device restarts until they are explicitly removed. Identify the anchors you want to react to using
 `ar_anchor_get_identifier`.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
typedef void (^ar_world_tracking_anchor_update_handler_t)(ar_world_anchors_t added_anchors,
                                                          ar_world_anchors_t updated_anchors,
                                                          ar_world_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the handler for receiving world tracking anchor updates.

 @param world_tracking_provider The world tracking provider.
 @param world_tracking_updates_queue The queue on which the handler will be called. Passing NULL will default to the main queue.
 @param world_tracking_anchor_update_handler The handler to be called when new world anchor data arrives.

 @note Setting this handler will override the function set using `ar_world_tracking_provider_set_anchor_update_handler_f`.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_set_anchor_update_handler(
    ar_world_tracking_provider_t world_tracking_provider,
    dispatch_queue_t _Nullable world_tracking_updates_queue,
    ar_world_tracking_anchor_update_handler_t _Nullable world_tracking_anchor_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when there are updates to world anchors. This includes updates to persisted world anchors from previous runs of the app.

 @param context The application-defined context.
 @param added_anchors The collection of world anchors that were added.
 @param updated_anchors The collection of world anchors that were updated.
 @param removed_anchors The collection of world anchors that were removed.

 @note This function will also be called for persisted world anchors from previous runs of the app, after the world tracking provider has been
 started. World anchors persist across device restarts until they are explicitly removed. Identify the anchors you want to react to using
 `ar_anchor_get_identifier`.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
typedef void (*ar_world_tracking_anchor_update_handler_function_t)(void *_Nullable context,
                                                                   ar_world_anchors_t added_anchors,
                                                                   ar_world_anchors_t updated_anchors,
                                                                   ar_world_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Set the function for receiving world tracking anchor updates.

 @param world_tracking_provider The world tracking provider.
 @param world_tracking_updates_queue The queue on which the function will be called. Passing NULL will default to the main queue.
 @param context The application-defined context parameter to pass to the function.
 @param world_tracking_anchor_update_handler_function The function to be called when new world anchor data arrives.

 @note Setting this function will override the handler set using `ar_world_tracking_provider_set_anchor_update_handler`.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_set_anchor_update_handler_f(
    ar_world_tracking_provider_t world_tracking_provider,
    dispatch_queue_t _Nullable world_tracking_updates_queue,
    void *_Nullable context,
    ar_world_tracking_anchor_update_handler_function_t _Nullable world_tracking_anchor_update_handler_function) AR_REFINED_FOR_SWIFT;

API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
OS_ENUM(ar_world_tracking_error_code, ar_error_code_t,
    /// Error code indicating that a world anchor failed to be added.
    ar_world_tracking_error_code_add_anchor_failed = 200,
    /// Error code indicating that the maximum amount of world anchors have been added.
    ar_world_tracking_error_code_anchor_max_limit_reached = 201,
    /// Error code indicating that a world anchor failed to be removed.
    ar_world_tracking_error_code_remove_anchor_failed = 202
) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the world tracking provider.

 @return `true` if the world tracking provider is supported on this device, `false` otherwise.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN bool ar_world_tracking_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when a request to add a world anchor has completed (successfully or not).

 @param world_anchor The world anchor to be added to the world tracking provider.
 @param successful `true` if the world anchor was successfully added to the world tracking provider, `false` otherwise.
 @param error The error that occurred, if any. The returned error supports ARC. In non-ARC files, use `ar_release()` to release the error.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
typedef void (^ar_world_tracking_add_anchor_completion_handler_t)(ar_world_anchor_t world_anchor,
                                                                  bool successful,
                                                                  ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Add a world anchor to the world tracking provider. This anchor will be persisted across device restarts unless explicitly removed.

 @param world_tracking_provider The world tracking provider.
 @param world_anchor The world anchor to add.
 @param add_anchor_completion_handler The handler to be called after the request to add the world anchor to the world tracking provider completes.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void
ar_world_tracking_provider_add_anchor(ar_world_tracking_provider_t world_tracking_provider,
                                      ar_world_anchor_t world_anchor,
                                      ar_world_tracking_add_anchor_completion_handler_t add_anchor_completion_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when a request to add a world anchor has completed (successfully or not).

 @param context The application-defined context.
 @param world_anchor The world anchor to be added to the world tracking provider.
 @param successful `true` if the world anchor was successfully added to the world tracking provider, `false` otherwise.
 @param error The error that occurred, if any. The returned error supports ARC. In non-ARC files, use `ar_release()` to release the error.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
typedef void (*ar_world_tracking_add_anchor_completion_handler_function_t)(void *_Nullable context,
                                                                           ar_world_anchor_t world_anchor,
                                                                           bool successful,
                                                                           ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Add a world anchor to the world tracking provider. This anchor will be persisted across device restarts unless explicitly removed.

 @param world_tracking_provider The world tracking provider.
 @param world_anchor The world anchor to add.
 @param context The application-defined context parameter to pass to the function.
 @param add_anchor_completion_handler_function The function to be called after the request to add the world anchor to the world tracking provider
 completes.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_add_anchor_f(
    ar_world_tracking_provider_t world_tracking_provider,
    ar_world_anchor_t world_anchor,
    void *_Nullable context,
    ar_world_tracking_add_anchor_completion_handler_function_t add_anchor_completion_handler_function) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when a request to remove a world anchor has completed (successfully or not).

 @param world_anchor The world anchor to be removed from the world tracking provider.
 @param successful `true` if the world anchor was successfully removed from the world tracking provider, `false` otherwise.
 @param error The error that occurred, if any. The returned error supports ARC. In non-ARC files, use `ar_release()` to release the error.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
typedef void (^ar_world_tracking_remove_anchor_completion_handler_t)(ar_world_anchor_t world_anchor,
                                                                     bool successful,
                                                                     ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Remove a world anchor from the world tracking provider.

 @param world_tracking_provider The world tracking provider.
 @param world_anchor The world anchor to remove.
 @param remove_anchor_completion_handler The handler to be called after the request to remove the world anchor from the world tracking provider
 completes.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void
ar_world_tracking_provider_remove_anchor(ar_world_tracking_provider_t world_tracking_provider,
                                         ar_world_anchor_t world_anchor,
                                         ar_world_tracking_remove_anchor_completion_handler_t remove_anchor_completion_handler) AR_REFINED_FOR_SWIFT;

/**
 Remove a world anchor from the world tracking provider using its identifier.

 @param world_tracking_provider The world tracking provider.
 @param anchor_identifier The identifier of the world anchor to remove.
 @param remove_anchor_completion_handler The handler to be called after the request to remove the world anchor from the world tracking provider
 completes.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_remove_anchor_with_identifier(
    ar_world_tracking_provider_t world_tracking_provider,
    uuid_t _Nonnull anchor_identifier,
    ar_world_tracking_remove_anchor_completion_handler_t remove_anchor_completion_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when a request to remove a world anchor has completed (successfully or not).

 @param context The application-defined context.
 @param world_anchor The world anchor to be removed from the world tracking provider.
 @param successful `true` if the world anchor was successfully removed from the world tracking provider, `false` otherwise.
 @param error The error that occurred, if any. The returned error supports ARC. In non-ARC files, use `ar_release()` to release the error.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
typedef void (*ar_world_tracking_remove_anchor_completion_handler_function_t)(void *_Nullable context,
                                                                              ar_world_anchor_t world_anchor,
                                                                              bool successful,
                                                                              ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Remove a world anchor from the world tracking provider.

 @param world_tracking_provider The world tracking provider.
 @param world_anchor The world anchor to remove.
 @param context The application-defined context parameter to pass to the function.
 @param remove_anchor_completion_handler_function The function to be called after the request to remove the world anchor from the world tracking
 provider completes.
 */
API_AVAILABLE(visionos(1.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_remove_anchor_f(
    ar_world_tracking_provider_t world_tracking_provider,
    ar_world_anchor_t world_anchor,
    void *_Nullable context,
    ar_world_tracking_remove_anchor_completion_handler_function_t remove_anchor_completion_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Remove a world anchor from the world tracking provider using its identifier.

 @param world_tracking_provider The world tracking provider.
 @param anchor_identifier The identifier of the world anchor to remove.
 @param context The application-defined context parameter to pass to the function.
 @param remove_anchor_completion_handler_function The function to be called after the request to remove the world anchor from the world tracking
 provider completes.
 */
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_remove_anchor_with_identifier_f(
    ar_world_tracking_provider_t world_tracking_provider,
    uuid_t _Nonnull anchor_identifier,
    void *_Nullable context,
    ar_world_tracking_remove_anchor_completion_handler_function_t remove_anchor_completion_handler_function) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__

/**
 Function called when a request to remove all known world anchors has completed (successfully or not).

 @param successful `true` if all anchors were successfully removed from the world tracking provider, `false` otherwise.
 @param error The error that occurred, if any. The returned error supports ARC. In non-ARC files, use `ar_release()` to release the error.
 */
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos)
typedef void (^ar_world_tracking_remove_all_anchors_completion_handler_t)(bool successful, ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Removes all known world anchors from the world tracking provider asynchronously.

 @param world_tracking_provider The world tracking provider.
 @param remove_all_anchors_completion_handler The handler to be called after the request to remove all known world anchors from
 the world tracking provider completes.
 */
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_remove_all_anchors(
    ar_world_tracking_provider_t world_tracking_provider,
    ar_world_tracking_remove_all_anchors_completion_handler_t remove_all_anchors_completion_handler) AR_REFINED_FOR_SWIFT;

#endif

/**
 Function called when a request to remove all known world anchors has completed (successfully or not).

 @param context The application-defined context.
 @param successful `true` if all anchors were successfully removed from the world tracking provider, `false` otherwise.
 @param error The error that occurred, if any. The returned error supports ARC. In non-ARC files, use `ar_release()` to release the error.
 */
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos)
typedef void (^ar_world_tracking_remove_all_anchors_completion_handler_function_t)(void *_Nullable context,
                                                                                   bool successful,
                                                                                   ar_error_t _Nullable error) AR_REFINED_FOR_SWIFT;

/**
 Removes all known world anchors from the world tracking provider asynchronously.

 @param world_tracking_provider The world tracking provider.
 @param context The application-defined context parameter to pass to the function.
 @param remove_all_anchors_completion_handler_function The handler to be called after the request to remove all known world anchors from
 the world tracking provider completes.
 */
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macos)
AR_EXTERN void ar_world_tracking_provider_remove_all_anchors_f(
    ar_world_tracking_provider_t world_tracking_provider,
    void *_Nullable context,
    ar_world_tracking_remove_all_anchors_completion_handler_function_t remove_all_anchors_completion_handler_function) AR_REFINED_FOR_SWIFT;


#pragma mark - Device Anchor

AR_OBJECT_DECL_SUBCLASS(ar_device_anchor, ar_trackable_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macos(26.0));

/**
 Return status enum values for getting the device anchor at a specified timestamp from the world tracking provider.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
OS_ENUM(ar_device_anchor_query_status, intptr_t,
    // The device anchor at the specified timestamp was successfully obtained.
    ar_device_anchor_query_status_success = 0,
    // The device anchor at the specified timestamp failed to be obtained.
    ar_device_anchor_query_status_failure)
AR_REFINED_FOR_SWIFT;

/**
 Tracking states of a device anchor.
 */
API_AVAILABLE(visionos(2.0), macos(26.0))
OS_ENUM(ar_device_anchor_tracking_state, intptr_t,
    // The anchor is not tracked.
    ar_device_anchor_tracking_state_untracked = 0,
    // Only orientation is currently tracked.
    ar_device_anchor_tracking_state_orientation_tracked,
    // Both position and orientation are currently tracked.
    ar_device_anchor_tracking_state_tracked)
AR_REFINED_FOR_SWIFT;

/**
 Create a device anchor.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_device_anchor_t`.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_device_anchor_t ar_device_anchor_create(void) AR_REFINED_FOR_SWIFT;

#pragma mark - Device Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 @param[in] anchor The anchor.
 @param[out] out_identifier A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
 */
API_AVAILABLE(visionos(2.0), macos(26.0))
AR_EXTERN void ar_device_anchor_get_identifier(ar_device_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 @param anchor The anchor.

 @return The origin from anchor transform.
 */
API_AVAILABLE(visionos(2.0), macos(26.0))
AR_EXTERN simd_float4x4 ar_device_anchor_get_origin_from_anchor_transform(ar_device_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 @param anchor  The anchor.

 @return The timestamp associated with the anchor.
 */
API_AVAILABLE(visionos(2.0), macos(26.0))
AR_EXTERN CFTimeInterval ar_device_anchor_get_timestamp(ar_device_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether an anchor is tracked.

 @param anchor The anchor.

 @return `true` if the anchor is tracked, `false` otherwise.
 */
API_AVAILABLE(visionos(2.0), macos(26.0))
AR_EXTERN bool ar_device_anchor_is_tracked(ar_device_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the tracking state of the device anchor.

 @param anchor The anchor.

 @return Tracking state of this anchor.
 */
API_AVAILABLE(visionos(2.0), macos(26.0))

AR_EXTERN ar_device_anchor_tracking_state_t ar_device_anchor_get_tracking_state(ar_device_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - World Tracking Prediction

/**
 Query a device anchor at the given timestamp.
 The origin is a right-handed coordinate system and is defined such that X points to the right, Y points up, and Z points backward.

 Example usage:
 ```
 auto timing_info = cp_drawable_get_frame_timing(drawable);
 auto time = cp_time_to_cf_time_interval(cp_frame_timing_get_presentation_time(timing_info));
 const ar_device_anchor_query_status_t status = ar_world_tracking_provider_query_device_anchor_at_timestamp(_provider, time, &device_anchor);
 ```

 @note This API is not thread safe.
 @param[in] world_tracking_provider The world tracking provider.
 @param[in] timestamp The timestamp to get the device anchor at. The timestamp should be provided as mach absolute time in seconds.
 @param[out] device_anchor The output device anchor.

 @return An `ar_device_anchor_query_status_t` value indicating whether the device anchor was successfully retrieved at the given timestamp or not.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN ar_device_anchor_query_status_t
ar_world_tracking_provider_query_device_anchor_at_timestamp(ar_world_tracking_provider_t world_tracking_provider,
                                                            CFTimeInterval timestamp,
                                                            ar_device_anchor_t device_anchor) AR_REFINED_FOR_SWIFT AR_MT_UNSAFE;

/**
 Get the authorization type required by the world tracking provider.

 @return The required authorization type.
 */
API_AVAILABLE(visionos(1.0), macos(26.0))
AR_EXTERN ar_authorization_type_t ar_world_tracking_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

AR_ASSUME_NONNULL_END

#endif // world_tracking_h
#else
#import <ARKitCore/world_tracking.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/world_tracking.h>)