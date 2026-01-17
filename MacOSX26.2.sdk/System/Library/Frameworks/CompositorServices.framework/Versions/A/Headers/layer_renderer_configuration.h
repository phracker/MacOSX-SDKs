//
//  layer_renderer_configuration.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_layer_renderer_configuration_h
#define cp_layer_renderer_configuration_h

CP_NONNULL_EXTERN_C_BEGIN

/// An opaque type that stores the settings to apply to a Compositor layer renderer.
///
/// You don’t create this type directly. If your ``CompositorLayer`` uses a custom
/// ``CompositorLayerConfiguration``, the compositor layer creates an instance of this type and
/// passes it to the provider’s
/// ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
/// function. Use that instance to modify the default configuration settings
/// for your layer.
CP_OBJECT_DECL(cp_layer_renderer_configuration, API_AVAILABLE(visionos(1.0), macosx(26.0)));

#ifdef __OBJC__

/// Returns the pixel format to use for the layer’s color textures.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///     method of your configuration provider.
/// - Returns: The pixel format to use for the layer’s color textures.
///
/// The compositor creates the color textures using the pixel format
/// information you provide.
MTLPixelFormat
cp_layer_renderer_configuration_get_color_format(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Sets the pixel format for the layer’s color textures to the specified
/// value.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - color_format: The pixel format to apply to the layer’s color textures.
///
/// Use this function to modify the configuration details for your layer. Call the
/// ``cp_layer_renderer_capabilities_supported_color_format`` function to determine which
/// pixel formats the layer’s color textures support.
void
cp_layer_renderer_configuration_set_color_format(cp_layer_renderer_configuration_t configuration,
                                                 MTLPixelFormat color_format)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the texture usage value to apply to the layer’s color textures.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///     method of your configuration provider.
/// - Returns: The Metal texture usage value to apply to the layer’s color
/// textures.
///
/// Metal optimizes texture-related operations based on the texture's usage value.
/// The usage value can be a combination of options. For example, a texture
/// might be readable and writable. For more information, see
/// <doc://com.apple.documentation/documentation/metal/mtltextureusage>.
MTLTextureUsage
cp_layer_renderer_configuration_get_color_usage(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Sets the texture usage for the layer’s color textures to the specified
/// value.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - color_usage: The usage value to apply to the layer’s color textures.
///
/// Use this function to modify the configuration details for your layer. Metal
/// optimizes texture-related operations based on the texture's usage value.
/// The usage value can be a combination of options. For example, a texture
/// might be readable and writable. For more information, see
/// <doc://com.apple.documentation/documentation/metal/mtltextureusage>.
void
cp_layer_renderer_configuration_set_color_usage(cp_layer_renderer_configuration_t configuration,
                                                MTLTextureUsage color_usage)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the pixel format to apply to the layer’s tracking areas textures.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: The pixel format to apply to the layer’s tracking areas textures.
///
/// The compositor creates the tracking areas textures using the pixel format
/// information you provide.
MTLPixelFormat
cp_layer_renderer_configuration_get_tracking_areas_format(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Sets the pixel format for the layer’s tracking areas textures to the specified
/// value.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - tracking_areas_format: The pixel format to apply to the layer’s tracking areas textures.
///
/// Use this function to modify the configuration details for your layer. Call the
/// ``cp_layer_renderer_capabilities_supported_tracking_areas_format`` function to determine which
/// pixel formats the layer’s tracking areas textures supports.
void
cp_layer_renderer_configuration_set_tracking_areas_format(cp_layer_renderer_configuration_t configuration,
                                                          MTLPixelFormat tracking_areas_format)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the texture usage value to apply to the layer’s tracking areas textures.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: The Metal texture usage value to apply to the layer’s tracking areas textures.
///
/// Metal optimizes texture-related operations based on the texture's usage value.
/// The usage value can be a combination of options. For example, a texture
/// might be readable and writable. For more information, see
/// <doc://com.apple.documentation/documentation/metal/mtltextureusage>.
MTLTextureUsage
cp_layer_renderer_configuration_get_tracking_areas_usage(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Sets the texture usage for the layer’s tracking areas textures to the specified
/// value.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - tracking_areas_usage: The usage value to apply to the layer’s
///    tracking areas textures.
///
/// Use this function to modify the configuration details for your layer.
void
cp_layer_renderer_configuration_set_tracking_areas_usage(cp_layer_renderer_configuration_t configuration,
                                                         MTLTextureUsage tracking_areas_usage)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the pixel format to apply to the layer’s depth textures.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: The pixel format to apply to the layer’s depth textures.
///
/// The compositor creates the depth textures using the pixel format
/// information you provide.
MTLPixelFormat
cp_layer_renderer_configuration_get_depth_format(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Sets the pixel format for the layer’s depth textures to the specified
/// value.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - color_format: The pixel format to apply to the layer’s depth textures.
///
/// Use this function to modify the configuration details for your layer. Call the
/// ``cp_layer_renderer_capabilities_supported_depth_format`` function to determine which
/// pixel formats the layer’s depth textures supports.
void
cp_layer_renderer_configuration_set_depth_format(cp_layer_renderer_configuration_t configuration,
                                                 MTLPixelFormat depth_format)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the texture usage value to apply to the layer’s depth textures.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: The Metal texture usage value to apply to the layer’s depth textures.
///
/// Metal optimizes texture-related operations based on the texture's usage value.
/// The usage value can be a combination of options. For example, a texture
/// might be readable and writable. For more information, see
/// <doc://com.apple.documentation/documentation/metal/mtltextureusage>.
MTLTextureUsage
cp_layer_renderer_configuration_get_depth_usage(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Sets the texture usage for the layer’s depth textures to the specified
/// value.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - depth_usage: The usage value to apply to the layer’s depth
///    textures.
///
/// Use this function to modify the configuration details for your layer.
void
cp_layer_renderer_configuration_set_depth_usage(cp_layer_renderer_configuration_t configuration,
                                                MTLTextureUsage depth_usage)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

#endif

/// Returns a Boolean value that indicates whether the layer supports
/// variable rasterization rates.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: `true` if the layer supports variable rasterization rates,
/// or `false` if it doesn’t.
///
/// Foveation support lets you reduce the amount of high-resolution drawing
/// you do. When foveation is enabled, the drawable resource for each frame
/// reduces the size of the texture you use for rendering. The drawable also
/// provides rasterization rate maps that specify the amount of rasterization
/// to apply to different parts of the texture. When rendering your scene,
/// the GPU generates fewer pixels in areas with low rasterization
/// rates, and then scales up those areas before displaying them onscreen.
bool
cp_layer_renderer_configuration_get_foveation_enabled(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Changes the setting that indicates whether the layer supports variable
/// rasterization rates.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - foveation_enabled: `true` to enable variable rasterization rates in
///    the layer, or `false` to render everything at the same resolution.
///
/// Foveation support lets you reduce the amount of high-resolution drawing
/// you do. If you enable foveation, the drawable resource for each frame
/// reduces the size of the texture you use for rendering. The drawable also
/// provides rasterization rate maps that specify the amount of rasterization
/// to apply to different parts of the texture. When rendering your scene,
/// the GPU generates fewer pixels in areas with low rasterization
/// rates, and then scales up those areas before displaying them onscreen.
void
cp_layer_renderer_configuration_set_foveation_enabled(cp_layer_renderer_configuration_t configuration,
                                                      bool foveation_enabled)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns a Boolean value that indicates whether the layer provides
/// flipped variable rasterization rate maps in addition to the regular maps.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: `true` if the layer generates flipped variable rasterization rate maps,
/// or `false` if it doesn’t.
///
/// Flipped is defined as +Y = up for clip/normalized device coordinates (flipped from Metal convention).
/// Generating flipped rasterization rate maps requires the configuration to have foveation enabled.
/// Can only be used for intermediatry render passes, the final render pass of the drawable cannot
/// be flipped and must use +Y = down for clip/normalized device coordinates (Metal conventions).
/// Generating flipped maps will bring additional computational cost to your render loop, regardless
/// of if the map is accessed/used.
///
/// When `true` the `cp_drawable_t` will provide flipped variable rasterization rate maps via the
/// `cp_drawable_get_flipped_rasterization_rate_map` function.
bool
cp_layer_renderer_configuration_get_generate_flipped_rasterization_rate_maps(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Changes the setting that indicates whether the layer provides
/// flipped variable rasterization rate maps in addition to the regular maps.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - generate_flipped_rasterization_rate_maps: `true` to generate flipped variable rasterization rate maps in
///    the layer, or `false` to only generate regular variable rasterization rate maps.
///
/// Flipped is defined as +Y = up for clip/normalized device coordinates (flipped from Metal convention).
/// Generating flipped rasterization rate maps requires the configuration to have foveation enabled.
/// Can only be used for intermediatry render passes, the final render pass of the drawable cannot
/// be flipped and must use +Y = down for clip/normalized device coordinates (Metal conventions).
/// Generating flipped maps will bring additional computational cost to your render loop, regardless 
/// of if the map is accessed/used.
///
/// When `true` the `cp_drawable_t` will provide flipped variable rasterization rate maps via the
/// `cp_drawable_get_flipped_rasterization_rate_map` function.
void
cp_layer_renderer_configuration_set_generate_flipped_rasterization_rate_maps(cp_layer_renderer_configuration_t configuration,
                                                                             bool generate_flipped_rasterization_rate_maps)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the texture configuration for the drawable views in the layer.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: The layout configuration for the textures.
///
/// Layouts define how the compositor creates the color and depth textures
/// it passes to your app. A layout might use separate textures for each view,
/// or combine the content from multiple views into a single texture. The layout
/// type also determines which Metal texture type the compositor creates for you.
/// For more information about the supported layouts, see ``cp_layer_renderer_layout``.
cp_layer_renderer_layout
cp_layer_renderer_configuration_get_layout(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Changes the layout configuration for the drawable views in the layer.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - layout: The layout configuration to apply to the layer.
///
/// Layouts define how the compositor creates the textures it passes to your
/// app. Use this function to change the layout you use for your content. A
/// layout might use separate textures for each view, or combine the content
/// from multiple views into a single texture. The layout type also determines
/// which Metal texture type the compositor creates for you. For more
/// information about the supported layouts, see ``cp_layer_renderer_layout``.
void
cp_layer_renderer_configuration_set_layout(cp_layer_renderer_configuration_t configuration,
                                           cp_layer_renderer_layout layout)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the distances for the far and near clipping planes you use
/// during drawing.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: The distances to the far and near planes in meters. The
/// compositor returns values in reverse-z ordering, with the value for the
/// far plane in the vector’s `x` property and the value for the near plane
/// in the vector’s `y` property.
///
/// The near and far planes reflect distances from the person viewing
/// the content. The compositor uses these values to compute the perspective
/// projection matrix and to clip content that is not between the near
/// and far planes.
simd_float2
cp_layer_renderer_configuration_get_default_depth_range(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Sets the default distances to the far and near clipping planes you use
/// during drawing.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - depth_range: The distances to the far and near planes in meters.
///    Specify the values in reverse-z ordering, with the value for the far
///    plane in the vector’s `x` property and the value for the near plane
///    in the vector’s `y` property.
///
/// Use this function to modify the configuration details for your layer.
/// The near and far planes correspond to distances from the person viewing
/// the content. The compositor uses these values to compute the perspective
/// projection matrix and to clip content that is not between the near and far
/// planes. It only supports reverse-Z depth, which means the value in the
/// texture should be 1 for near 0 for far.
///
/// This function modifies the layer's default depth values. You can
/// also change these values separately for the ``cp_drawable_t`` type of
/// individual frames.
void
cp_layer_renderer_configuration_set_default_depth_range(cp_layer_renderer_configuration_t configuration,
                                                        simd_float2 depth_range)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

#ifdef __OBJC__

/// Sets the pixel format for the drawable's render context stencil textures to the specified
/// value.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - stencil_format: The pixel format to apply to the drawable's render context stencil
///    textures.
void
cp_layer_renderer_configuration_set_drawable_render_context_stencil_format(cp_layer_renderer_configuration_t configuration,
                                                                           MTLPixelFormat stencil_format)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the pixel format to use for the stencil texture in drawable's render context.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///     method of your configuration provider.
/// - Returns: The pixel format to use for the drawable's render context stencil textures.
MTLPixelFormat
cp_layer_renderer_configuration_get_drawable_render_context_stencil_format(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

#endif

/// Returns the raster sample count to use in drawable's render context.
///
/// - Parameters:
///    - configuration: The layer configuration type that contains the
///    information. The system passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///     method of your configuration provider.
/// - Returns: The raster sample count to use for the drawable's render context.
int
cp_layer_renderer_configuration_get_drawable_render_context_raster_sample_count(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Sets the raster sample count for the drawable's render context to the specified
/// value.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - raster_sample_count: The raster sample count to apply to the drawable's render context.
void
cp_layer_renderer_configuration_set_drawable_render_context_raster_sample_count(cp_layer_renderer_configuration_t configuration,
                                                                                int raster_sample_count)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Get max render quality the layer can use when drawing to the drawables.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: The max render qualityto use for the drawable's.
///
/// The max render quality is a value between [0, 1].
/// This determines the max render quality at which drawing can happen.
///
/// Setting a higher max render quality will impact the resolution that is allocated for the drawable textures.
/// This memory will count against the app's memory limit so should only be specified as high as renderer
/// can reasonably achieve frame rate at. During runtime, the render quality can be changed on the
/// layer renderer but will not impact memory usage, see ``cp_layer_renderer_set_render_quality``.
cp_render_quality_t
cp_layer_renderer_configuration_get_max_render_quality(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Set max render quality the layer can use when drawing to the drawables.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - render_quality: A value between between [0, 1].
///    This determines the max render quality at which drawing can happen.
///
/// Setting a higher max render quality will impact the resolution that is allocated for the drawable textures.
/// This memory will count against the app's memory limit so should only be specified as high as renderer
/// can reasonably achieve frame rate at. During runtime, the render quality can be changed on the
/// layer renderer but will not impact memory usage, see ``cp_layer_renderer_set_render_quality``.
void
cp_layer_renderer_configuration_set_max_render_quality(cp_layer_renderer_configuration_t configuration,
                                                       cp_render_quality_t render_quality)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

#if CP_MTL4_AVAILABLE

/// Get whether the layer can use Metal4 when drawing to the drawables.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
/// - Returns: Whether the layer supports using Metal4, otherwise defaults to Metal3.
bool
cp_layer_renderer_configuration_get_supports_mtl4(cp_layer_renderer_configuration_t configuration)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0));

/// Set whether the layer can use Metal4 when drawing to the drawables.
///
/// - Parameters:
///    - configuration: The layer configuration type to modify. The system
///    passes an instance of this type to the
///     ``CompositorLayerConfiguration/makeConfiguration(capabilities:configuration:)``
///    method of your configuration provider.
///    - supports_mtl4: Whether the layer supports using Metal4, otherwise defaults to Metal3.
void
cp_layer_renderer_configuration_set_supports_mtl4(cp_layer_renderer_configuration_t configuration,
                                                  bool supports_mtl4)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

#endif

CP_NONNULL_EXTERN_C_END

#endif /* cp_layer_renderer_configuration_h */
