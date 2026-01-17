//
//  layer_renderer_properties.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_layer_renderer_properties_h
#define cp_layer_renderer_properties_h

CP_NONNULL_EXTERN_C_BEGIN

/*!
 * MARK: Texture Topology
 */

/// An opaque type that specifies the configuration of one of the layer’s
/// drawable textures.
///
/// For direct-to-screen drawing, you specify how you want Compositor to
/// configure the required textures when you configure your layer. For a
/// device with multiple displays, Compositor can configure the textures
/// in different ways. For example, it can create a separate texture for
/// each display, or it can combine the images from multiple displays into
/// a single texture. A texture topology type contains the details of one
/// of the textures Compositor creates for your app.
CP_STRUCT_REF(cp_texture_topology, TextureTopology, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Returns the number of items in the texture array.
///
/// - Parameters:
///    - texture_topology: A texture configuration you obtained from the
///    layer's properties. Fetch this value using the
///    ``cp_layer_renderer_properties_get_texture_topology`` function.
/// - Returns: The number of separate items in the texture array.
///
/// Array-based texture types such as
/// <doc://com.apple.documentation/documentation/metal/mtltexturetype/type2darray>
/// manage one or more images of the same size. This function returns the
/// number of separate images the texture manages. Other array types store
/// only one image.
uint64_t
cp_texture_topology_get_array_length(cp_texture_topology_t texture_topology)
CF_SWIFT_NAME(getter:cp_texture_topology_t.arrayLength(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

#ifdef __OBJC__
/// Returns the type value that specifies how the underlying texture
/// organizes its views.
///
/// - Parameters:
///   - texture_topology: The texture topology to query. Get the texture
///   topology from the layer properties using the
///   ``cp_layer_renderer_properties_get_texture_topology`` function.
/// - Returns: A Metal value that indicates the arrangement of views
/// within the texture.
///
/// A texture might store the content of one view or multiple views. For
/// example, a single texture might store one or both views for the left
/// and right eyes of a head-mounted display. The texture type indicates
/// this content organization strategy.
MTLTextureType
cp_texture_topology_get_texture_type(cp_texture_topology_t texture_topology)
CF_SWIFT_NAME(getter:cp_texture_topology_t.textureType(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));
#endif

/*!
 * MARK: Layer Properties
 */

/// An opaque type that describes the organization of the layer's textures
/// and the relationships between those textures and the views you use
/// for drawing.
///
/// You might use the layer's properties to configure other parts of
/// your app. For example, use them to configure your app's render pipeline.
///
/// You can obtain layer properties directly from your layer. If you don't
/// yet have the layer type, you can create an equivalent set of properties
/// using the ``cp_layer_renderer_properties_create_using_configuration`` function.
CP_OBJECT_DECL(cp_layer_renderer_properties, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Creates a new opaque type to store layer-related properties.
///
/// - Parameters:
///    - configuration: An opaque type that contains the layer’s
///    configuration details. Compositor uses this information to
///    configure the properties an equivalent layer would use.
///    - error: A pointer to an error object. On success, the function sets
///    this value to `nil`. If an error occurs, this function sets the value
///    of the pointer to an error object with details about the problem.
///    The caller is responsible for releasing the returned error object.
/// - Returns: A new layer properties type with details about how the layer
/// configures its topologies and texture maps. The function returns `nil`
/// if an error occurs.
///
/// Call this function to create a set of layer properties when you don't
/// yet have a ``cp_layer_renderer_t`` type. This function generates an equivalent
/// set of properties for the configuration you provide. You can use those
/// properties to configure other parts of your app before the layer becomes
/// available. For example, you might use the information to configure portions
/// of your app's render pipeline.
cp_layer_renderer_properties_t _Nullable
cp_layer_renderer_properties_create_using_configuration(cp_layer_renderer_configuration_t configuration,
                                                        CFErrorRef * __nullable error)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0))
OS_OBJECT_RETURNS_RETAINED;

/// Returns the number of texture topologies available for you to inspect.
///
/// - Parameters:
///    - layer_properties: The layer properties to query.
/// - Returns: The number of texture topologies present in the layer.
///
/// The layer’s configuration determines the total number of available
/// topologies, and each topology contains details about one texture you
/// use for rendering. Fetch the topology details using the
/// ``cp_layer_renderer_properties_get_texture_topology`` function.
size_t
cp_layer_renderer_properties_get_texture_topology_count(cp_layer_renderer_properties_t layer_properties)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Retrieves the texture topology at the specified index in the
/// layer's properties.
///
/// - Parameters:
///    - layer_properties: The layer properties to query.
///    - index: The index into the array of texture configurations.
///    This value must be less than the value returned by the
///    ``cp_layer_renderer_properties_get_texture_topology`` function.
/// - Returns: An opaque type that contains details about the specific
/// texture.
///
/// Retrieve the topology type and use accessor functions to get details
/// of that topology, including its type and array length.
/// Use that information to allocate the resources you need to manage
/// your content.
cp_texture_topology_t
cp_layer_renderer_properties_get_texture_topology(cp_layer_renderer_properties_t layer_properties,
                                         size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the number of views that will need to be rendered.
///
/// - Parameters:
///    - layer_properties: The layer properties to query.
/// - Returns: The total number of views that need to be support on the drawables.
///
/// Should use ``cp_frame_get_drawable_target_view_count`` when
/// performing frustum culling to determine how many views specific views each
/// drawable target has.
///
/// Should use ``cp_drawable_get_view_count`` when drawing to
/// determine how many views the specific frame has.
size_t
cp_layer_renderer_properties_get_view_count(cp_layer_renderer_properties_t layer_properties)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the max render value for tracking areas' render values.
///
/// - Parameters:
///    - layer_properties: The layer properties to query.
/// - Returns: The max render value for the tracking areas render values.
///
/// The layer’s configuration determines the total number of available
/// tracking areas. This will be the max render value available, based on
/// ``cp_layer_renderer_configuration_get_tracking_areas_format`` function.
cp_tracking_area_render_value
cp_layer_renderer_properties_get_tracking_areas_max_value(cp_layer_renderer_properties_t properties)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));

CP_NONNULL_EXTERN_C_END

#endif /* cp_layer_renderer_properties_h */

