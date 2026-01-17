//
//  layer_renderer_capabilities.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_layer_renderer_capabilities_h
#define cp_layer_renderer_capabilities_h

CP_NONNULL_EXTERN_C_BEGIN

/// A type that stores the supported configurations for a layer.
CP_OBJECT_DECL(cp_layer_renderer_capabilities, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Returns a Boolean value that indicates whether the layer supports
/// variable rasterization rates.
///
/// - Parameters:
///   - layer_capabilities: The system-provided layer capabilities type.
/// - Returns: `true` if the layer supports variable rasterization rates or
/// `false` if you must render the entire layer at the same resolution.
///
/// Foveation support lets you reduce the amount of high-resolution drawing
/// you do. When foveation support is available, you can render content in
/// someone’s peripheral vision at a lower resolution than content under
/// their direct gaze.
bool
cp_layer_renderer_capabilities_supports_foveation(cp_layer_renderer_capabilities_t layer_capabilities)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// The options to provide when calling ``cp_layer_renderer_capabilities_supported_color_formats`` and
/// ``cp_layer_renderer_capabilities_supported_color_formats_count``
typedef CF_OPTIONS(uint32_t, cp_supported_color_formats_options) {
    cp_supported_color_formats_options_none                          = 0,
    cp_supported_color_formats_options_progressive_immersion_enabled = 1 << 0,
} CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the number of color formats the specified layer supports.
///
/// - Parameters:
///    - layer_capabilities: The layer capabilities to query.
///    - options: The options to consider when creating the list of supported
///   color formats.
/// - Returns: The number of color formats the layer supports.
///
/// To iterate over the color formats, use the ``cp_layer_renderer_capabilities_supported_color_format``
/// function.
size_t
cp_layer_renderer_capabilities_supported_color_formats_count_with_options(cp_layer_renderer_capabilities_t layer_capabilities,
                                                                          cp_supported_color_formats_options options)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the number of color formats the specified layer supports.
///
/// - Parameters:
///    - layer_capabilities: The layer capabilities to query.
///   color formats.
/// - Returns: The number of color formats the layer supports.
///
/// To iterate over the color formats, use the ``cp_layer_renderer_capabilities_supported_color_format``
/// function.
size_t
cp_layer_renderer_capabilities_supported_color_formats_count(cp_layer_renderer_capabilities_t layer_capabilities)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(macosx, ios)
API_DEPRECATED("Use cp_layer_renderer_capabilities_supported_color_formats_count_with_options instead.", visionos(1.0, 26.0));

#ifdef __OBJC__

/// Returns the color format at the specified index in the layer capabilities.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
///   - options: The options to consider when creating the list of supported
///   color formats.
///   - index: A zero-based index into the list of color formats.
/// - Returns: The color format at the specified index.
///
/// Use this function to determine the pixel arrangements and characteristics
/// you can apply to the layer.
MTLPixelFormat
cp_layer_renderer_capabilities_supported_color_format_with_options(cp_layer_renderer_capabilities_t layer_capabilities,
                                                                   cp_supported_color_formats_options options,
                                                                   size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the color format at the specified index in the layer capabilities.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
///   - index: A zero-based index into the list of color formats.
/// - Returns: The color format at the specified index.
///
/// Use this function to determine the pixel arrangements and characteristics
/// you can apply to the layer.
MTLPixelFormat
cp_layer_renderer_capabilities_supported_color_format(cp_layer_renderer_capabilities_t layer_capabilities,
                                                      size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0)) API_UNAVAILABLE(macosx, ios)
API_DEPRECATED("Use cp_layer_renderer_capabilities_supported_color_format_with_options instead.", visionos(1.0, 26.0));

#endif

/// Returns the number of depth formats the specified layer supports.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
/// - Returns: The number of depth formats the layer supports.
///
/// To iterate over the depth formats, use the ``cp_layer_renderer_capabilities_supported_depth_format``
/// function.
size_t
cp_layer_renderer_capabilities_supported_depth_formats_count(cp_layer_renderer_capabilities_t layer_capabilities)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

#ifdef __OBJC__

/// Returns the depth format at the specified index in the layer capabilities.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
///   - index: A zero-based index into the list of depth formats.
/// - Returns: The pixel format at the specified index.
///
/// Use this function to determine what depth texture formats the layer
/// supports.
MTLPixelFormat
cp_layer_renderer_capabilities_supported_depth_format(cp_layer_renderer_capabilities_t layer_capabilities,
                                                      size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

#endif

/// Returns the number of tracking areas formats the specified layer supports.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
/// - Returns: The number of tracking areas formats the layer supports.
///
/// To iterate over the index formats, use the ``cp_layer_renderer_capabilities_supported_tracking_areas_format``
/// function.
size_t
cp_layer_renderer_capabilities_supported_tracking_areas_formats_count(cp_layer_renderer_capabilities_t layer_capabilities)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

#ifdef __OBJC__

/// Returns the tracking areas format at the specified index in the layer capabilities.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
///   - index: A zero-based index into the list of index formats.
/// - Returns: The pixel format at the specified index.
///
/// Use this function to determine what tracking areas texture formats the layer
/// supports.
MTLPixelFormat
cp_layer_renderer_capabilities_supported_tracking_areas_format(cp_layer_renderer_capabilities_t layer_capabilities,
 size_t index)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

#endif // __OBJC__

/// The options to provide when calling ``cp_layer_renderer_capabilities_supported_layout`` and
/// ``cp_layer_renderer_capabilities_supported_layouts_count``
typedef CF_OPTIONS(uint32_t, cp_supported_layouts_options) {
    cp_supported_layouts_options_none                           = 0,
    cp_supported_layouts_options_foveation_enabled              = 1 << 0,
    cp_supported_layouts_options_progressive_immersion_enabled
    API_AVAILABLE(visionos(26.0), macosx(26.0))                  = 1 << 1,
} CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the number of layouts the specified layer supports.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
///   - options: The options to consider when creating the list of supported
///   layouts.
/// - Returns: The number of layouts the layer supports.
///
/// To iterate over the layouts, use the ``cp_layer_renderer_capabilities_supported_layout``
/// function.
size_t
cp_layer_renderer_capabilities_supported_layouts_count(cp_layer_renderer_capabilities_t layer_capabilities,
                                                       cp_supported_layouts_options options)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the layout at the specified index in the layer capabilities.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
///   - options: The options to consider when creating the list of supported
///   layouts.
///   - index: A zero-based index into the list of layouts. This value must
///   be less than the value the ``cp_layer_renderer_capabilities_supported_layouts_count``
///   function returns for the same value of the `foveation_enabled` parameter.
/// - Returns: The layer layout at the specified index.
///
/// Use this function to determine what texture layouts the layer supports.
cp_layer_renderer_layout
cp_layer_renderer_capabilities_supported_layout(cp_layer_renderer_capabilities_t layer_capabilities,
                                                cp_supported_layouts_options options,
                                                size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the minimum distance in meters to the near projection plane
/// that the layer supports.
///
/// The compositor uses the near and far projection planes to compute the
/// perspective projection matrix and to clip content that is not between
/// the near and far planes. Use this method to retrieve the
/// minimum distance to the near plane that the layer allows. When you
/// configure your layer, you can specify a different minimum distance,
/// but that value must be greater than or equal to the distance this
/// method returns.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
/// - Returns: The minimum allowed distance in meters from the camera
/// origin to the near projection plane.
float
cp_layer_renderer_capabilities_supported_minimum_near_plane_distance(cp_layer_renderer_capabilities_t layer_capabilities)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the number of stencil formats the specified layer supports.
///
/// - Parameters:
///    - layer_capabilities: The layer capabilities to query.
/// - Returns: The number of stencil formats the layer supports.
///
/// To iterate over the stencil formats, use the ``cp_layer_renderer_capabilities_drawable_render_context_supported_stencil_format``
/// function.
size_t
cp_layer_renderer_capabilities_drawable_render_context_supported_stencil_formats_count(cp_layer_renderer_capabilities_t layer_capabilities)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

#ifdef __OBJC__

/// Returns the stencil format at the specified index in the layer capabilities.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
///   - index: A zero-based index into the list of stencil formats.
/// - Returns: The stencil format at the specified index.
///
/// Use this function to determine the pixel arrangements and characteristics
/// you can apply to the layer.
MTLPixelFormat
cp_layer_renderer_capabilities_drawable_render_context_supported_stencil_format(cp_layer_renderer_capabilities_t layer_capabilities,
                                                                                size_t index)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

#endif

/// Returns default render quality for drawing on this platform.
///
/// This should be used as a base value for the platform quality
/// for drawing.
///
/// @see ``cp_layer_renderer_configuration_set_max_render_quality``
/// for usage.
///
/// - Parameters:
///   - layer_capabilities: The layer capabilities to query.
/// - Returns: The default render quality allowed for drawing.
cp_render_quality_t
cp_layer_renderer_capabilities_get_default_render_quality(cp_layer_renderer_capabilities_t layer_capabilities)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

CP_NONNULL_EXTERN_C_END

#endif /* cp_layer_renderer_capabilities_h */
