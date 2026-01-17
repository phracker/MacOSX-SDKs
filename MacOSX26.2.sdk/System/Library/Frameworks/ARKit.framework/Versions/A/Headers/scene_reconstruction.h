#if (defined(USE_ARKIT_PUBLIC_HEADERS) && USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/scene_reconstruction.h>)
//
//  scene_reconstruction.h
//  ARKitCore
//
//  Copyright © 2025 Apple Inc. All rights reserved.
//

#ifndef scene_reconstruction_h
#define scene_reconstruction_h

#ifdef __OBJC__
#import <Metal/Metal.h>
#endif // __OBJC__

#import <ARKit/anchor.h>
#import <ARKit/data_provider.h>
#import <ARKit/object.h>
#import <ARKit/session.h>

#import <os/availability.h>
#import <simd/simd.h>

AR_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(macos);

AR_OBJECT_DECL_SUBCLASS(ar_mesh_anchor, ar_anchor)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_mesh_geometry)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_mesh_geometries)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(2.0));

AR_OBJECT_DECL(ar_geometry_source)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_geometry_element)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_mesh_anchors)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL(ar_scene_reconstruction_configuration)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

AR_OBJECT_DECL_SUBCLASS(ar_scene_reconstruction_provider, ar_data_provider)
AR_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0));

#pragma mark - Geometry Element

/**
 A value describing the primitive type of an `ar_geometry_element_t`.
 */
API_AVAILABLE(visionos(1.0))
OS_ENUM(ar_geometry_primitive_type, intptr_t,

        /** A primitive type representing a line. */
        ar_geometry_primitive_type_line = 0,

        /** A primitive type representing a triangle. */
        ar_geometry_primitive_type_triangle
) AR_REFINED_FOR_SWIFT;

/**
 A value describing the classification of a mesh face of an `ar_mesh_geometry_t`.
 */
OS_ENUM(ar_mesh_classification, intptr_t,
        ar_mesh_classification_none = 0,
        ar_mesh_classification_wall,
        ar_mesh_classification_floor,
        ar_mesh_classification_ceiling,
        ar_mesh_classification_table,
        ar_mesh_classification_seat,
        ar_mesh_classification_window,
        ar_mesh_classification_door,
        ar_mesh_classification_stairs,
        ar_mesh_classification_bed,
        ar_mesh_classification_cabinet,
        ar_mesh_classification_home_appliance,
        ar_mesh_classification_tv,
        ar_mesh_classification_plant
) AR_REFINED_FOR_SWIFT
API_DEPRECATED_WITH_REPLACEMENT("ar_surface_classification_t", visionos(1.0, 26.0));

/**
 A value describing the classification of a surface.
 */
API_AVAILABLE(visionos(26.0))
OS_ENUM(ar_surface_classification, intptr_t,
        ar_surface_classification_none = 0,
        ar_surface_classification_wall,
        ar_surface_classification_floor,
        ar_surface_classification_ceiling,
        ar_surface_classification_table,
        ar_surface_classification_seat,
        ar_surface_classification_window,
        ar_surface_classification_door,
        ar_surface_classification_stairs,
        ar_surface_classification_bed,
        ar_surface_classification_cabinet,
        ar_surface_classification_home_appliance,
        ar_surface_classification_tv,
        ar_surface_classification_plant
) AR_REFINED_FOR_SWIFT;


/**
 Returns a bool value that indicates whether the two geometry elements are equal.

 @param geometry_element A geometry element to be compared.
 @param other_geometry_element The other geometry element to be compared to.

 @return YES if the geometry elements are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_geometry_element_is_equal_to_geometry_element(ar_geometry_element_t _Nullable geometry_element,
                                                                ar_geometry_element_t _Nullable other_geometry_element) AR_REFINED_FOR_SWIFT;

#ifdef __OBJC__
/**
 Get a Metal buffer containing index data that defines a geometry element.

 @param geometry_element The geometry element.

 @return A Metal buffer.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN id<MTLBuffer> ar_geometry_element_get_buffer(ar_geometry_element_t geometry_element) AR_REFINED_FOR_SWIFT;
#endif // __OBJC__

/**
 Get the count of primitives in a geometry element.

 @param geometry_element The geometry element.

 @return The number of primitives in the geometry element.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_geometry_element_get_count(ar_geometry_element_t geometry_element) AR_REFINED_FOR_SWIFT;

/**
 Get the number of bytes per index value in a geometry element.

 @param geometry_element The geometry element.

 @return The bytes per index value.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_geometry_element_get_bytes_per_index(ar_geometry_element_t geometry_element) AR_REFINED_FOR_SWIFT;

/**
 Get the index count per primitive of a geometry element.

 @see `ar_geometry_primitive_type_t`
 @discussion This is based on the primitive type. For `ar_geometry_primitive_type_triangle` the value is 3.

 @param geometry_element The geometry element.

 @return The number of indices for each of the geometry element's primitives.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_geometry_element_get_index_count_per_primitive(ar_geometry_element_t geometry_element) AR_REFINED_FOR_SWIFT;

/**
 Get the primitive type of a geometry element.

 @param geometry_element The geometry element.

 @return The geometry element's primitive type.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_geometry_primitive_type_t ar_geometry_element_get_primitive_type(ar_geometry_element_t geometry_element) AR_REFINED_FOR_SWIFT;

#pragma mark - Geometry Source

/**
 Returns a bool value that indicates whether the two geometry sources are equal.

 @param geometry_source A geometry source to be compared.
 @param other_geometry_source The other geometry source to be compared to.

 @return YES if the geometry sources are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_geometry_source_is_equal_to_geometry_source(ar_geometry_source_t _Nullable geometry_source,
                                                              ar_geometry_source_t _Nullable other_geometry_source) AR_REFINED_FOR_SWIFT;

#ifdef __OBJC__
/**
 Get a Metal buffer containing per-vector data for a geometry source.

 @param geometry_source The geometry source.

 @return A Metal buffer containing per-vector data.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN id<MTLBuffer> ar_geometry_source_get_buffer(ar_geometry_source_t geometry_source) AR_REFINED_FOR_SWIFT;
#endif // __OBJC__

/**
 Get the count of vectors in a geometry source.

 @param geometry_source The geometry source.

 @return The number of vectors in the geometry source.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_geometry_source_get_count(ar_geometry_source_t geometry_source) AR_REFINED_FOR_SWIFT;

#ifdef __OBJC__
/**
 Get the type of per-vector data in a geometry source.

 @param geometry_source The geometry source.

 @return The format of the vertex data.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN MTLVertexFormat ar_geometry_source_get_format(ar_geometry_source_t geometry_source) AR_REFINED_FOR_SWIFT;
#endif // __OBJC__

/**
 Get the count of scalar components in each vector of a geometry source.

 @param geometry_source The geometry source.

 @return The number of scalar components in each vector of the geometry source.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_geometry_source_get_components_per_vector(ar_geometry_source_t geometry_source) AR_REFINED_FOR_SWIFT;

/**
 Get the offset (in bytes) from the beginning of a geometry source's Metal buffer.

 @param geometry_source The geometry source.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_geometry_source_get_offset(ar_geometry_source_t geometry_source) AR_REFINED_FOR_SWIFT;

/**
 Get the number of bytes from a vector to the next one in a geometry source's Metal buffer.

 @param geometry_source The geometry source.

 @return The stride between vectors, in bytes.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_geometry_source_get_stride(ar_geometry_source_t geometry_source) AR_REFINED_FOR_SWIFT;

#pragma mark - Mesh Geometry

/**
 Returns a bool value that indicates whether the two mesh geometries are equal.

 @param mesh_geometry A mesh geometry to be compared.
 @param other_mesh_geometry The other mesh geometry to be compared to.

 @return YES if the mesh geometries are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_mesh_geometry_is_equal_to_mesh_geometry(ar_mesh_geometry_t _Nullable mesh_geometry,
                                                          ar_mesh_geometry_t _Nullable other_mesh_geometry) AR_REFINED_FOR_SWIFT;

/**
 Get the vertices of a mesh geometry.

 @param mesh_geometry The mesh geometry.

 @return An instance of `ar_geometry_source_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_geometry_source_t ar_mesh_geometry_get_vertices(ar_mesh_geometry_t mesh_geometry) AR_REFINED_FOR_SWIFT;

/**
 Get the normals of a mesh geometry.

 @param mesh_geometry The mesh geometry.

 @return An instance of `ar_geometry_source_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_geometry_source_t ar_mesh_geometry_get_normals(ar_mesh_geometry_t mesh_geometry) AR_REFINED_FOR_SWIFT;

/**
 Get the faces of a mesh geometry.

 @param mesh_geometry The mesh geometry.

 @return An instance of `ar_geometry_element_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_geometry_element_t ar_mesh_geometry_get_faces(ar_mesh_geometry_t mesh_geometry) AR_REFINED_FOR_SWIFT;

/**
 Get the classification for each face of a mesh geometry.

 @param mesh_geometry The mesh geometry.

 @return An instance of `ar_geometry_source_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_geometry_source_t _Nullable ar_mesh_geometry_get_classification(ar_mesh_geometry_t mesh_geometry) AR_REFINED_FOR_SWIFT;

#pragma mark - Mesh Geometry Collection

/**
 Get the count of mesh geometries in a collection.

 @param mesh_geometries The collection of mesh geometries.

 @return The number of mesh geometries in the collection.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN size_t ar_mesh_geometries_get_count(ar_mesh_geometries_t mesh_geometries) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of mesh geometries.

 @param mesh_geometry The mesh geometry.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(2.0))
typedef bool (^ar_mesh_geometries_enumerator_t)(ar_mesh_geometry_t mesh_geometry) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of mesh geometries.

 @param mesh_geometries The collection of mesh geometries.
 @param mesh_geometries_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_mesh_geometries_enumerate_geometries(ar_mesh_geometries_t mesh_geometries,
                                                       ar_mesh_geometries_enumerator_t mesh_geometries_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of mesh geometries.

 @param context The application-defined context.
 @param mesh_geometry The mesh geometry.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(2.0))
typedef bool (*ar_mesh_geometries_enumerator_function_t)(void *_Nullable context, ar_mesh_geometry_t mesh_geometry) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of mesh geometries using a function.

 @param mesh_geometries The collection of mesh geometries.
 @param context The application-defined context parameter to pass to the function.
 @param mesh_geometries_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void
ar_mesh_geometries_enumerate_geometries_f(ar_mesh_geometries_t mesh_geometries,
                                          void *_Nullable context,
                                          ar_mesh_geometries_enumerator_function_t mesh_geometries_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Mesh Anchor

/**
 Returns a bool value that indicates whether the two mesh anchors are equal.

 @param mesh_anchor A mesh anchor to be compared.
 @param other_mesh_anchor The other mesh anchor to be compared to.

 @return YES if the mesh anchors are equal, otherwise NO.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN bool ar_mesh_anchor_is_equal_to_mesh_anchor(ar_mesh_anchor_t _Nullable mesh_anchor,
                                                      ar_mesh_anchor_t _Nullable other_mesh_anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the geometry of the mesh in a mesh anchor's coordinate system.

 @param mesh_anchor The mesh anchor.

 @return An instance of `ar_mesh_geometry_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_mesh_geometry_t ar_mesh_anchor_get_geometry(ar_mesh_anchor_t mesh_anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Mesh Anchor (ar_anchor convenience getters)

/**
 Get the identifier of an anchor.

 @param[in] anchor The anchor.
 @param[out] out_identifier A pointer to a UUID to fill out with the anchor identifier. Must be non-null.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN void ar_mesh_anchor_get_identifier(ar_mesh_anchor_t anchor, uuid_t _Nonnull out_identifier) AR_REFINED_FOR_SWIFT;

/**
 Get the transform from an anchor to the origin coordinate system.

 @param anchor The anchor.

 @return The origin from anchor transform.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN simd_float4x4 ar_mesh_anchor_get_origin_from_anchor_transform(ar_mesh_anchor_t anchor) AR_REFINED_FOR_SWIFT;

/**
 Get the timestamp corresponding to an anchor.

 @param anchor  The anchor.

 @return The timestamp associated with the anchor.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN CFTimeInterval ar_mesh_anchor_get_timestamp(ar_mesh_anchor_t anchor) AR_REFINED_FOR_SWIFT;

#pragma mark - Mesh Anchors Collection

/**
 Get the count of mesh anchors in a collection.

 @param mesh_anchors The collection of mesh anchors.

 @return The number of mesh anchors in the collection.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN size_t ar_mesh_anchors_get_count(ar_mesh_anchors_t mesh_anchors) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler for enumerating a collection of mesh anchors.

 @param mesh_anchor The mesh anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (^ar_mesh_anchors_enumerator_t)(ar_mesh_anchor_t mesh_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of mesh anchors.

 @param mesh_anchors The collection of mesh anchors.
 @param mesh_anchors_enumerator The enumerator handler.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_mesh_anchors_enumerate_anchors(ar_mesh_anchors_t mesh_anchors,
                                                 ar_mesh_anchors_enumerator_t mesh_anchors_enumerator) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function for enumerating a collection of mesh anchors.

 @param context The application-defined context.
 @param mesh_anchor The mesh anchor.

 @return `true` to continue enumerating, or `false` to stop enumerating.
 */
API_AVAILABLE(visionos(1.0))
typedef bool (*ar_mesh_anchors_enumerator_function_t)(void *_Nullable context, ar_mesh_anchor_t mesh_anchor) AR_REFINED_FOR_SWIFT;

/**
 Enumerate a collection of mesh anchors using a function.

 @param mesh_anchors The collection of mesh anchors.
 @param context The application-defined context parameter to pass to the function.
 @param mesh_anchors_enumerator_function The enumerator function.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_mesh_anchors_enumerate_anchors_f(ar_mesh_anchors_t mesh_anchors,
                                                   void *_Nullable context,
                                                   ar_mesh_anchors_enumerator_function_t mesh_anchors_enumerator_function) AR_REFINED_FOR_SWIFT;

#pragma mark - Scene Reconstruction Configuration

API_AVAILABLE(visionos(1.0))
OS_OPTIONS(ar_scene_reconstruction_mode,
           uint64_t,
           /** Scene reconstruction default mode. Generates a mesh of the world. */
           ar_scene_reconstruction_mode_default = 0,

           /** Scene reconstruction classification mode. Generates a mesh of the world, along with a classification for each face. */
           ar_scene_reconstruction_mode_classification = 1 << 0)
AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Handler called when there are updates to mesh anchors.

 @param added_anchors The collection of anchors that were added.
 @param updated_anchors The collection of anchors that were updated.
 @param removed_anchors The collection of anchors that were removed.
 */
API_AVAILABLE(visionos(1.0))
typedef void (^ar_scene_reconstruction_update_handler_t)(ar_mesh_anchors_t added_anchors,
                                                         ar_mesh_anchors_t updated_anchors,
                                                         ar_mesh_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Function called when there are updates to mesh anchors.

 @param context The application-defined context.
 @param added_anchors The collection of anchors that were added.
 @param updated_anchors The collection of anchors that were updated.
 @param removed_anchors The collection of anchors that were removed.
 */
API_AVAILABLE(visionos(1.0))
typedef void (*ar_scene_reconstruction_update_handler_function_t)(void *_Nullable context,
                                                                  ar_mesh_anchors_t added_anchors,
                                                                  ar_mesh_anchors_t updated_anchors,
                                                                  ar_mesh_anchors_t removed_anchors) AR_REFINED_FOR_SWIFT;

/**
 Create a scene reconstruction configuration.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_scene_reconstruction_configuration_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_scene_reconstruction_configuration_t ar_scene_reconstruction_configuration_create(void) AR_REFINED_FOR_SWIFT;

/**
 Get the scene reconstruction mode.

 @param scene_reconstruction_configuration The configuration for scene reconstruction.

 @return The scene reconstruction mode for the configuration.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_scene_reconstruction_mode_t ar_scene_reconstruction_configuration_get_scene_reconstruction_mode(
    ar_scene_reconstruction_configuration_t scene_reconstruction_configuration) AR_REFINED_FOR_SWIFT;

/**
 Set the scene reconstruction mode.

 @param scene_reconstruction_configuration The configuration for scene reconstruction.
 @param scene_reconstruction_mode The scene reconstruction mode to set.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void
ar_scene_reconstruction_configuration_set_scene_reconstruction_mode(ar_scene_reconstruction_configuration_t scene_reconstruction_configuration,
                                                                    ar_scene_reconstruction_mode_t scene_reconstruction_mode) AR_REFINED_FOR_SWIFT;

#pragma mark - Scene Reconstruction Provider

/**
 Create a scene reconstruction provider.

 @param scene_reconstruction_configuration The configuration for scene reconstruction.

 @note This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the object.
 @return An instance of `ar_scene_reconstruction_provider_t`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_scene_reconstruction_provider_t
ar_scene_reconstruction_provider_create(ar_scene_reconstruction_configuration_t scene_reconstruction_configuration) AR_REFINED_FOR_SWIFT;

#ifdef __BLOCKS__
/**
 Set the handler for receiving scene reconstruction updates.

 @param scene_reconstruction_provider The scene reconstruction provider.
 @param scene_reconstruction_updates_queue The queue on which the handler will be executed. Passing NULL will default to the main queue.
 @param scene_reconstruction_update_handler The handler to be called when new scene reconstruction data arrives.

 @note Setting this handler will override the function set using `ar_scene_reconstruction_provider_set_update_handler_f`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_scene_reconstruction_provider_set_update_handler(
    ar_scene_reconstruction_provider_t scene_reconstruction_provider,
    dispatch_queue_t _Nullable scene_reconstruction_updates_queue,
    ar_scene_reconstruction_update_handler_t _Nullable scene_reconstruction_update_handler) AR_REFINED_FOR_SWIFT;
#endif // __BLOCKS__

/**
 Set the function for receiving scene reconstruction updates.

 @param scene_reconstruction_provider The scene reconstruction provider.
 @param scene_reconstruction_updates_queue The queue on which the function will be called. Passing NULL will default to the main queue.
 @param context The application-defined context parameter to pass to the function.
 @param scene_reconstruction_update_handler_function The function to be called when new scene reconstruction data arrives.

 @note Setting this function will override the handler set using `ar_scene_reconstruction_provider_set_update_handler`.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN void ar_scene_reconstruction_provider_set_update_handler_f(
    ar_scene_reconstruction_provider_t scene_reconstruction_provider,
    dispatch_queue_t _Nullable scene_reconstruction_updates_queue,
    void *_Nullable context,
    ar_scene_reconstruction_update_handler_function_t _Nullable scene_reconstruction_update_handler_function) AR_REFINED_FOR_SWIFT;

/**
 Copy all mesh anchors.

 @param scene_reconstruction_provider The scene reconstruction provider.

 @return The collection of all mesh anchors. This type supports ARC. In non-ARC files, use `ar_retain()` and `ar_release()` to retain and release the
 object.
 */
API_AVAILABLE(visionos(2.0))
AR_EXTERN AR_OBJECT_RETURNS_RETAINED ar_mesh_anchors_t
ar_scene_reconstruction_provider_copy_all_mesh_anchors(ar_scene_reconstruction_provider_t scene_reconstruction_provider) AR_REFINED_FOR_SWIFT;

/**
 Determine whether this device supports the scene reconstruction provider.

 @return `true` if the scene reconstruction provider is supported on this device, `false` otherwise.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN bool ar_scene_reconstruction_provider_is_supported(void) AR_REFINED_FOR_SWIFT;

/**
 Get the authorization type required by the scene reconstruction provider.

 @return The required authorization type.
 */
API_AVAILABLE(visionos(1.0))
AR_EXTERN ar_authorization_type_t ar_scene_reconstruction_provider_get_required_authorization_type(void) AR_REFINED_FOR_SWIFT;

API_UNAVAILABLE_END; // macos

AR_ASSUME_NONNULL_END

#endif // scene_reconstruction_h
#else
#import <ARKitCore/scene_reconstruction.h> 
#endif // #if (defined(USE_ARKIT_PUBLIC_HEADERS) \&\& USE_ARKIT_PUBLIC_HEADERS) || !__has_include(<ARKitCore/scene_reconstruction.h>)