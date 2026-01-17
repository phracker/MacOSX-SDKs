#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/plane_detection.h>)
//
//  plane_detection.h
//  ARKit
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef plane_detection_h
#define plane_detection_h

#import <ARKit/anchor.h>
#import <ARKit/data_provider.h>
#import <ARKit/object.h>
#import <ARKit/scene_reconstruction.h>
#import <ARKit/session.h>

#import <dispatch/dispatch.h>
#import <os/availability.h>
#import <simd/types.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL_SUBCLASS(ar_plane_anchor, ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_plane_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_plane_geometry)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_plane_extent)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_plane_detection_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL_SUBCLASS(ar_plane_detection_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

/**
 Option set describing possible orientation alignments of a detected plane.
 
 @note An `ar_plane_anchor_t` has exactly one alignment. Multiple bits may be set to receive various planes from an `ar_plane_detection_provider_t`.
 */
API_AVAILABLE(visionos(1.0))
OS_OPTIONS(ar_plane_alignment, intptr_t,
  
  /** No plane alignment. */
  ar_plane_alignment_none                              = 0,
  
  /** Planes orthogonal to the gravity vector. */
  ar_plane_alignment_horizontal                        = (1 << 0),
           
  /** Planes parallel to the gravity vector. */
  ar_plane_alignment_vertical                          = (1 << 1),
           
  /** Planes that are neither horizontal nor vertical. */
   ar_plane_alignment_slanted API_AVAILABLE(visionos(2.0)) = (1 << 2),

) AR_REFINED_FOR_SWIFT;

/**
 A value describing the classification of a plane anchor.
 */
OS_ENUM(ar_plane_classification, intptr_t,

    /** The plane classification is currently unavailable. */
    ar_plane_classification_status_not_available = 0,

    /** The classification of the plane has not yet been determined.  */
    ar_plane_classification_status_undetermined,

    /** The plane classification is not any of the known classes. */
    ar_plane_classification_status_unknown,

    /** The classification is of type wall. */
    ar_plane_classification_wall,

    /** The classification is of type floor. */
    ar_plane_classification_floor,

    /** The classification is of type ceiling. */
    ar_plane_classification_ceiling,

    /** The classification is of type table. */
    ar_plane_classification_table,
    
    /** The classification is of type seat. */
    ar_plane_classification_seat,

    /** The classification is of type window. */
    ar_plane_classification_window,

    /** The classification is of type door. */
    ar_plane_classification_door

) AR_REFINED_FOR_SWIFT
API_DEPRECATED_WITH_REPLACEMENT("ar_surface_classification_t", visionos(1.0, 26.0));


#ifdef __BLOCKS__
/**
 Handler called when there are updates to plane anchors.

 @param added_anchors The collection of anchors that were added.
 @param updated_anchors The collection of anchors that were updated.
 @param removed_anchors The collection of anchors that were removed.
 */
API_AVAILABLE(visionos(1.0))
typedef void (^ar_plane_detection_update_handler_t)(ar_plane_anchors_t added_anchors,
                                                    ar_plane_anchors_t updated_anchors,
                                                    ar_plane_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when there are updates to plane anchors.

 @param context The application-defined context.
 @param added_anchors The collection of anchors that were added.
 @param updated_anchors The collection of anchors that were updated.
 @param removed_anchors The collection of anchors that were removed.
 */
API_AVAILABLE(visionos(1.0))
typedef void (*ar_plane_detection_update_handler_function_t)(void *_Nullable context,
                                                             ar_plane_anchors_t added_anchors,
                                                             ar_plane_anchors_t updated_anchors,
                                                             ar_plane_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

#pragma mark - Plane Detection Configuration

/**
 Create a plane detection configuration.

 @note The alignment is set to `ar_plane_alignment_horizontal | ar_plane_alignment_vertical` by default.
 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_plane_detection_configuration_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_plane_detection_configuration_t ar_plane_detection_configuration_create(void) AR_REFINED_FOR_SWIFT;

/**
 Set the desired alignment of planes to detect.

 @param plane_detection_configuration The configuration for plane detection.
 @param alignment The plane alignments to detect.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_plane_detection_configuration_set_alignment(ar_plane_detection_configuration_t plane_detection_configuration,
                                                              ar_plane_alignment_t alignment) AR_REFINED_FOR_SWIFT;

#pragma mark - Plane Anchor

/**
 Returns a bool value that indicates whether the two plane anchors are equal.

 @param anchor A plane anchor to be compared.
 @param other_anchor The other plane anchor to be compared to.

 @return YES if the plane anchors are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_plane_anchor_is_equal_to_plane_anchor(ar_plane_anchor_t _Nullable anchor,
                                                        ar_plane_anchor_t _Nullable other_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the alignment of a plane anchor.

 @param plane_anchor The plane anchor.

 @return The anchor's plane alignment.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_plane_alignment_t ar_plane_anchor_get_alignment(ar_plane_anchor_t plane_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the geometry of a plane anchor.

 @param plane_anchor The plane anchor.

 @return An instance of `ar_plane_geometry_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_plane_geometry_t ar_plane_anchor_get_geometry(ar_plane_anchor_t plane_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the classification of a plane anchor.

 @param plane_anchor The plane anchor.

 @return The plane anchor's classification.
 */
AR_EXTERN ar_plane_classification_t ar_plane_anchor_get_plane_classification(ar_plane_anchor_t plane_anchor)
    API_DEPRECATED_WITH_REPLACEMENT("ar_plane_anchor_get_surface_classification", visionos(1.0, 26.0)) AR_REFINED_FOR_SWIFT;

/**
 Get the surface classification of a plane anchor.

 @param plane_anchor The plane anchor.

 @return The plane anchor's surface classification.
 */
API_AVAILABLE(visionos(26.0))
AR_EXTERN ar_surface_classification_t ar_plane_anchor_get_surface_classification(ar_plane_anchor_t plane_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Plane Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 @param[in] anchor The anchor.
 @param[out] out_identifier A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_plane_anchor_get_identifier(ar_plane_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 @param anchor The anchor.

 @return The origin from anchor transform.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_plane_anchor_get_origin_from_anchor_transform(ar_plane_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 @param anchor  The anchor.

 @return The timestamp associated with the anchor.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_plane_anchor_get_timestamp(ar_plane_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Plane Geometry

/**
 Returns a bool value that indicates whether the two plane geometries are equal.

 @param plane_geometry A plane geometry to be compared.
 @param other_plane_geometry The other plane geometry to be compared to.

 @return YES if the plane geometries are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_plane_geometry_is_equal_to_plane_geometry(ar_plane_geometry_t _Nullable plane_geometry,
                                                            ar_plane_geometry_t _Nullable other_plane_geometry) AR_REFINED_FOR_SWIFT;

/**
 Get the mesh vertices of a plane geometry.

 @param plane_geometry The plane geometry.

 @return An instance of `ar_geometry_source_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_geometry_source_t ar_plane_geometry_get_mesh_vertices(ar_plane_geometry_t plane_geometry) AR_REFINED_FOR_SWIFT;

/**
 Get the mesh faces of a plane geometry.

 @param plane_geometry The plane geometry.

 @return An instance of `ar_geometry_element_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_geometry_element_t ar_plane_geometry_get_mesh_faces(ar_plane_geometry_t plane_geometry) AR_REFINED_FOR_SWIFT;

/**
 Get the extent of a plane geometry.

 @param plane_geometry The plane geometry.

 @return An instance of `ar_plane_extent_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_plane_extent_t ar_plane_geometry_get_plane_extent(ar_plane_geometry_t plane_geometry) AR_REFINED_FOR_SWIFT;

#pragma mark - Plane Extent

/**
 Returns a bool value that indicates whether the two plane extents are equal.

 @param plane_extent A plane extent to be compared.
 @param other_plane_extent The other plane extent to be compared to.

 @return YES if the plane extents are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_plane_extent_is_equal_to_plane_extent(ar_plane_extent_t _Nullable plane_extent,
                                                        ar_plane_extent_t _Nullable other_plane_extent) AR_REFINED_FOR_SWIFT;

/**
 Get the width of a plane extent.

 @param plane_extent The plane extent.

 @return The width of the plane extent.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN float ar_plane_extent_get_width(ar_plane_extent_t plane_extent) AR_REFINED_FOR_SWIFT;

/**
 Get the height of the plane extent.

 @param plane_extent The plane extent.

 @return The height of the plane extent.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN float ar_plane_extent_get_height(ar_plane_extent_t plane_extent) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from a plane extent to the plane anchor’s coordinate system.

 @param plane_extent The plane extent.

 @return The transform from the plane extent to the plane anchor's coordinate system.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN simd_float4x4 ar_plane_extent_get_plane_anchor_from_plane_extent_transform(ar_plane_extent_t plane_extent) AR_REFINED_FOR_SWIFT;

#pragma mark - Plane Anchors Collection

/**
 Get the count of plane anchors in a collection.

 @param plane_anchors The collection of plane anchors.

 @return The number of plane anchors in the collection.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_plane_anchors_get_count(ar_plane_anchors_t plane_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of plane anchors.

 @param plane_anchor The plane anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (^ar_plane_anchors_enumerator_t)(ar_plane_anchor_t plane_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of plane anchors.

 @param plane_anchors The collection of plane anchors.
 @param plane_anchors_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_plane_anchors_enumerate_anchors(ar_plane_anchors_t plane_anchors,
                                                  ar_plane_anchors_enumerator_t plane_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of plane anchors.

 @param context The application-defined context.
 @param plane_anchor The plane anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (*ar_plane_anchors_enumerator_function_t)(void *_Nullable context, ar_plane_anchor_t plane_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of plane anchors using a function.

 @param plane_anchors The collection of plane anchors.
 @param context The application-defined context parameter to pass to the function.
 @param plane_anchors_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_plane_anchors_enumerate_anchors_f(ar_plane_anchors_t plane_anchors,
                                                    void *_Nullable context,
                                                    ar_plane_anchors_enumerator_function_t plane_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Plane Detection Provider

/**
 Create a plane detection provider.

 @param plane_detection_configuration The configuration for plane detection.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_plane_detection_provider_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_plane_detection_provider_t
ar_plane_detection_provider_create(ar_plane_detection_configuration_t plane_detection_configuration) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Set the handler for receiving plane detection updates.

 @param plane_detection_provider The plane detection provider.
 @param plane_detection_updates_queue The plane detection update queue. Passing NULL will default to the main queue.
 @param plane_detection_update_handler The plane detection update handler.

 @note Setting this handler will override the function set using `ar_plane_detection_provider_set_update_handler_f`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void
ar_plane_detection_provider_set_update_handler(ar_plane_detection_provider_t plane_detection_provider,
                                               dispatch_queue_t _Nullable plane_detection_updates_queue,
                                               ar_plane_detection_update_handler_t _Nullable plane_detection_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Set the function for receiving plane detection updates.

 @param plane_detection_provider The plane detection provider.
 @param plane_detection_updates_queue The plane detection update queue. Passing NULL will default to the main queue.
 @param context The application-defined context parameter to pass to the function.
 @param plane_detection_update_handler_function The plane detection update handler function.

 @note Setting this function will override the handler set using `ar_plane_detection_provider_set_update_handler`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_plane_detection_provider_set_update_handler_f(
    ar_plane_detection_provider_t plane_detection_provider,
    dispatch_queue_t _Nullable plane_detection_updates_queue,
    void *_Nullable context,
    ar_plane_detection_update_handler_function_t _Nullable plane_detection_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Copy all plane anchors.

 @param plane_detection_provider The plane detection provider.

 @return The collection of all plane anchors. This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the
 object.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_plane_anchors_t
ar_plane_detection_provider_copy_all_plane_anchors(ar_plane_detection_provider_t plane_detection_provider) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the plane detection provider.

 @return `true` if the plane detection provider is supported on this device, `false` otherwise.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN bool ar_plane_detection_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the plane detection provider.

 @return The required authorization type.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_authorization_type_t ar_plane_detection_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // plane_detection_h
#else
#import <ARKitCore/plane_detection.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/plane_detection.h>)