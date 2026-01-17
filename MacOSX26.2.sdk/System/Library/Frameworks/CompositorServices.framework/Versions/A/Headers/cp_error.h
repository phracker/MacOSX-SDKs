//
//  cp_error.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_error_h
#define cp_error_h

CP_NONNULL_EXTERN_C_BEGIN

/// The domain for errors that occur during layer renderer configuration.
CP_EXTERN CFErrorDomain const cp_layer_renderer_configuration_error_domain CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Errors that can occur during layer configuration.
typedef CF_ERROR_ENUM(cp_layer_renderer_configuration_error_domain, cp_layer_renderer_configuration_error_code)
{
    /// An error that indicates the system didn't find a default
    /// layer renderer configuration.
    cp_layer_renderer_configuration_error_code_missing_configuration = -20,

    /// An error that indicates the layer doesn’t support the current
    /// pixel format for color textures.
    ///
    /// Compare the value the ``cp_layer_renderer_configuration_get_color_format``
    /// function returns and make sure it matches one of the values the
    /// ``cp_layer_renderer_capabilities_supported_color_format`` function returns.
    cp_layer_renderer_configuration_error_code_unsupported_color_format = -4,

    /// An error that indicates the layer doesn’t support the current
    /// texture usage for color textures.
    ///
    /// Compare the value the ``cp_layer_renderer_configuration_get_color_usage``
    /// function returns and make sure it has at least `MTLTextureUsageShaderRead`
    /// and does not contain `MTLTextureUsageShaderAtomic` or `MTLTextureUsageShaderWrite`
    cp_layer_renderer_configuration_error_code_unsupported_color_usage = -5,

    /// An error that indicates the layer doesn’t support the current
    /// pixel format for depth textures.
    ///
    /// Compare the value the ``cp_layer_renderer_configuration_get_depth_format``
    /// function returns and make sure it matches one of the values the
    /// ``cp_layer_renderer_capabilities_supported_depth_format`` function returns.
    cp_layer_renderer_configuration_error_code_unsupported_depth_format = -7,

    /// An error that indicates the layer doesn’t support the current
    /// texture usage for depth textures.
    ///
    /// Compare the value the ``cp_layer_renderer_configuration_get_depth_usage``
    /// function returns and make sure it has at least `MTLTextureUsageShaderRead`
    /// and does not contain `MTLTextureUsageShaderAtomic`
    cp_layer_renderer_configuration_error_code_unsupported_depth_usage = -8,

    /// An error that indicates foveation is enabled but not supported.
    ///
    /// Disable foveation in your layer's configuration.
    cp_layer_renderer_configuration_error_code_variable_rasterization_rate_is_not_supported = -16,

    /// An error that occurs when you try to enable temporal anti-aliasing
    /// but the current configuration parameters don't support it.
    cp_layer_renderer_configuration_error_code_temporal_anti_aliasing_not_supported = -17,

    /// An error that indicates not enough frames are available for rendering.
    cp_layer_renderer_configuration_error_code_not_enough_frames_requested = -10,

    /// An error that indicates the system requested too many frames
    /// for rendering.
    cp_layer_renderer_configuration_error_code_too_many_frames_requested = -11,

    /// An error that indicates the depth range values aren't in
    /// reverse-z order.
    ///
    /// When you call the ``cp_drawable_set_depth_range`` function,
    /// make sure the first value in your `depth_range` vector contains
    /// the value for the far plane. In addition, make sure the distance
    /// to the far plane is greater than the distance to the near plane.
    cp_layer_renderer_configuration_error_code_unsupported_forward_depth_range = -101,

    /// An error that indicates the configuration's current layout value
    /// is invalid.
    ///
    /// Specify a supported layout value using the ``cp_layer_renderer_configuration_set_layout``
    /// function. Get a list of supported layouts from the
    /// ``cp_layer_renderer_capabilities_supported_layout`` function.
    cp_layer_renderer_configuration_error_code_layout_not_supported = -6,

    /// An error that indicates the near plane of the client is smaller
    /// than the supported value.
    cp_layer_renderer_configuration_error_code_unsupported_near_plane_distance = -104,

    /// An error that indicates the layer doesn’t support the current
    /// pixel format for tracking areas textures.
    ///
    /// Compare the value the ``cp_layer_renderer_configuration_get_tracking_areas_format``
    /// function returns and make sure it matches one of the values the
    /// ``cp_layer_renderer_capabilities_supported_tracking_areas_format`` function returns.
    cp_layer_renderer_configuration_error_code_unsupported_tracking_areas_format API_AVAILABLE(visionos(26.0), macosx(26.0)) = -21,

    /// An error that indicates the layer doesn’t support the current
    /// texture usage for tracking areas textures.
    ///
    /// Compare the value the ``cp_layer_renderer_configuration_get_tracking_areas_usage``
    /// function returns and make sure it has at least `MTLTextureUsageShaderRead`
    /// and does not contain `MTLTextureUsageShaderAtomic`
    cp_layer_renderer_configuration_error_code_unsupported_tracking_areas_usage API_AVAILABLE(visionos(26.0), macosx(26.0)) = -22,

    /// An error that indicates the layer doesn't support the current
    /// pixel format for stencil texture.
    ///
    /// Compare the value the ``cp_layer_renderer_configuration_get_drawable_render_context_stencil_format``
    /// function returns and make sure it matches one of the values the
    /// ``cp_layer_renderer_capabilities_drawable_render_context_supported_stencil_format`` function returns.
    cp_layer_renderer_configuration_error_code_unsupported_drawable_render_context_stencil_format API_AVAILABLE(visionos(26.0), macosx(26.0)) = -23,

    /// An error that indicates the configuration's render quality is unsupported.
    /// This could be because foveation is disabled or the quality is outside of the valid range of [0, 1],
    /// the error `userInfo` will contain additional information.
    cp_layer_renderer_configuration_error_code_unsupported_render_quality API_AVAILABLE(visionos(26.0)) = -18,

} CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0)) ;

CP_NONNULL_EXTERN_C_END

#endif /* cp_error_h */
