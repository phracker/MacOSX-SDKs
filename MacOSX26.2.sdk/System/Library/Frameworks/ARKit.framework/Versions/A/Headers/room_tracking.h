#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/room_tracking.h>)
//
//  room_tracking.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef room_tracking_h
#define room_tracking_h

#import <ARKit/anchor.h>
#import <ARKit/data_provider.h>
#import <ARKit/identifiers.h>
#import <ARKit/object.h>
#import <ARKit/scene_reconstruction.h>

#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL_SUBCLASS(ar_room_anchor, ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

AR_OBJECT_DECL(ar_room_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

AR_OBJECT_DECL(ar_room_tracking_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

AR_OBJECT_DECL_SUBCLASS(ar_room_tracking_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

#pragma mark - Room Anchor

/**
 Returns a bool value that indicates whether the two room anchors are equal.

 @param room_anchor A room anchor to be compared.
 @param other_room_anchor The other room anchor to be compared to.

 @return YES if the room anchors are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_room_anchor_is_equal_to_room_anchor(ar_room_anchor_t _Nullable room_anchor,
                                                      ar_room_anchor_t _Nullable other_room_anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine if the room anchor represents the current room the person is in.

 @param room_anchor The room anchor.

 @return `true` if the person is in the given room, `false` otherwise.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_room_anchor_is_current_room(ar_room_anchor_t room_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get a mesh representation of the room.

 @param room_anchor The room anchor.

 @return A mesh geometry that represents the geometry of the room.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_mesh_geometry_t ar_room_anchor_get_geometry(ar_room_anchor_t room_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get disjoint mesh geometries of a given classification.

 @param room_anchor The room anchor.
 @param classification Classification of the mesh geometry.

 @note Only `ar_mesh_classification_wall` and `ar_mesh_classification_floor` is supported.

 @return A collection of mesh geometries where each geometry represents a disjoint mesh of type `classification`.
 */
AR_EXTERN ar_mesh_geometries_t ar_room_anchor_get_mesh_geometries_for_classification(ar_room_anchor_t room_anchor,
                                                                                     ar_mesh_classification_t classification)
    API_DEPRECATED_WITH_REPLACEMENT("ar_room_anchor_get_mesh_geometries_for_surface_classification", visionos(2.0, 26.0)) AR_REFINED_FOR_SWIFT;

/**
 Get disjoint mesh geometries of a given surface classification.

 @param room_anchor The room anchor.
 @param classification Classification of the surface.

 @note Only `ar_surface_classification_wall` and `ar_surface_classification_floor` are supported.

 @return A collection of mesh geometries where each geometry represents a disjoint mesh of type `classification`.
 */
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_mesh_geometries_t ar_room_anchor_get_mesh_geometries_for_surface_classification(
    ar_room_anchor_t room_anchor, ar_surface_classification_t classification) AR_REFINED_FOR_SWIFT;

/**
 Determine if the room contains the given point.

 @param room_anchor The room anchor.
 @param point The point to query in the application's coordinate space.

 @return Returns `true` if `room_anchor` contains `point`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_room_anchor_contains_point(ar_room_anchor_t room_anchor, simd_float3 point) AR_REFINED_FOR_SWIFT;

#pragma mark - Room Anchor (ar_anchor convenience getters)

/**
 Get the identifier of a room anchor.

 @param[in] room_anchor The room anchor.
 @param[out] out_identifier A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_room_anchor_get_identifier(ar_room_anchor_t room_anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from a room anchor to the origin coordinate system.

 @param room_anchor The room anchor.

 @return The origin from room anchor transform.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_room_anchor_get_origin_from_anchor_transform(ar_room_anchor_t room_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to when the room anchor was updated.

 @param room_anchor  The room anchor.

 @return The timestamp associated with the room anchor.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_room_anchor_get_timestamp(ar_room_anchor_t room_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Room Anchors Collection

/**
 Get the count of room anchors in a collection.

 @param room_anchors The collection of room anchors.

 @return The number of room anchors in the collection.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_room_anchors_get_count(ar_room_anchors_t room_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of room anchors.

 @param room_anchor The room anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_room_anchors_enumerator_t)(ar_room_anchor_t room_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of room anchors.

 @param room_anchors The collection of room anchors.
 @param room_anchors_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_room_anchors_enumerate_anchors(ar_room_anchors_t room_anchors,
                                                 ar_room_anchors_enumerator_t room_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of room anchors.

 @param context The application-defined context.
 @param room_anchor The room anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_room_anchors_enumerator_function_t)(void *_Nullable context, ar_room_anchor_t room_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of room anchors using a function.

 @param room_anchors The collection of room anchors.
 @param context The application-defined context parameter to pass to the function.
 @param room_anchors_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_room_anchors_enumerate_anchors_f(ar_room_anchors_t room_anchors,
                                                   void *_Nullable context,
                                                   ar_room_anchors_enumerator_function_t room_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Room Tracking Configuration

#ifdef __BLOCKS__
/**
 Handler called when there are updates to room anchors.

 @param added_anchors The collection of anchors that were added.
 @param updated_anchors The collection of anchors that were updated.
 @param removed_anchors The collection of anchors that were removed.
 */
API_AVAILABLE(visionos(2.0))
typedef void (^ar_room_tracking_update_handler_t)(ar_room_anchors_t added_anchors,
                                                  ar_room_anchors_t updated_anchors,
                                                  ar_room_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when there are updates to room anchors.

 @param context The application-defined context.
 @param added_anchors The collection of anchors that were added.
 @param updated_anchors The collection of anchors that were updated.
 @param removed_anchors The collection of anchors that were removed.
 */
API_AVAILABLE(visionos(2.0))
typedef void (*ar_room_tracking_update_handler_function_t)(void *_Nullable context,
                                                           ar_room_anchors_t added_anchors,
                                                           ar_room_anchors_t updated_anchors,
                                                           ar_room_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

#pragma mark - Room Tracking Configuration

/**
 Create a room tracking configuration.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_room_tracking_configuration_t`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_room_tracking_configuration_t ar_room_tracking_configuration_create(void) AR_REFINED_FOR_SWIFT;

/**
 Create a room tracking provider.

 @param room_tracking_configuration The configuration for room tracking.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_room_tracking_provider_t`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_room_tracking_provider_t
ar_room_tracking_provider_create(ar_room_tracking_configuration_t room_tracking_configuration) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Set the handler for receiving room tracking updates.

 @param room_tracking_provider The room tracking provider.
 @param room_tracking_updates_queue The room tracking update queue. Passing NULL will default to the main queue.
 @param room_tracking_update_handler The room tracking update handler.

 @note Setting this handler will override the function set using `ar_room_tracking_provider_set_update_handler_f`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_room_tracking_provider_set_update_handler(ar_room_tracking_provider_t room_tracking_provider,
                                             dispatch_queue_t _Nullable room_tracking_updates_queue,
                                             ar_room_tracking_update_handler_t _Nullable room_tracking_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Set the function for receiving room tracking updates.

 @param room_tracking_provider The room tracking provider.
 @param room_tracking_updates_queue The room tracking update queue. Passing NULL will default to the main queue.
 @param context The application-defined context parameter to pass to the function.
 @param room_tracking_update_handler_function The room tracking update handler function.

 @note Setting this function will override the handler set using `ar_room_tracking_provider_set_update_handler`.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_room_tracking_provider_set_update_handler_f(
    ar_room_tracking_provider_t room_tracking_provider,
    dispatch_queue_t _Nullable room_tracking_updates_queue,
    void *_Nullable context,
    ar_room_tracking_update_handler_function_t _Nullable room_tracking_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Copy the room anchor that the person is currently inside.

 @param room_tracking_provider The room tracking provider.

 @return The room anchor that represents the room the person is in and NULL if no room is currently being tracked as current. This type supports ARC.
 In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_room_anchor_t _Nullable ar_room_tracking_provider_copy_current_room_anchor(
    ar_room_tracking_provider_t room_tracking_provider) AR_REFINED_FOR_SWIFT;

/**
 Copy all room anchors.

 @param room_tracking_provider The room tracking provider.

 @return The collection of all room anchors. This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the
 object.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_room_anchors_t
ar_room_tracking_provider_copy_all_room_anchors(ar_room_tracking_provider_t room_tracking_provider) AR_REFINED_FOR_SWIFT;

/**
 Get the identifiers of all plane anchors in a room anchor.

 @param room_anchor The room anchor.

 @return The identifiers of planes in the room anchor.
 @see ar_plane_detection_provider_t
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_identifiers_t ar_room_anchor_get_plane_anchor_identifiers(ar_room_anchor_t room_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the identifiers of all scene reconstruction mesh anchors in a room anchor.

 @param room_anchor The room anchor.

 @return The identifiers of meshes in the room anchor.
 @see ar_scene_reconstruction_provider_t
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_identifiers_t ar_room_anchor_get_mesh_anchor_identifiers(ar_room_anchor_t room_anchor) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the room tracking provider.

 @return `true` if the room tracking provider is supported on this device, `false` otherwise.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_room_tracking_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the room tracking provider.

 @return The required authorization type.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN ar_authorization_type_t ar_room_tracking_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif /* room_tracking_h */
#else
#import <ARKitCore/room_tracking.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/room_tracking.h>)