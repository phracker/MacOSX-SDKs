//
//  drawable_render_context.h
//  CompositorServices
//
//  Copyright © 2024 Apple. All rights reserved.
//

#ifndef drawable_render_context_h
#define drawable_render_context_h

CP_NONNULL_EXTERN_C_BEGIN

/// An object that can render any effects associated with a drawable
/// This is required for applications that want to render using the
/// Progressive Immersion Style
CP_STRUCT_REF(cp_drawable_render_context, cp_drawable_t.RenderContext, API_AVAILABLE(visionos(26.0), macosx(26.0)));

#ifdef __OBJC__

/// Store the `value` parameter in the stencil texture in the pixels that Compositor
/// will display on the screen.
///
/// - Parameters:
///    - render_context: The render context to use to present the drawable.
///    - command_encoder: The command encoder to use to render the Compositor effects
///                       and present the drawable.
///    - value: The value to use when updating the stencil texture in the command_encoder.
///
/// - Note: In Full and Mixed immersion style, this will be the full texture.
///
/// - Note: The command encoder used in the render context has the following constraints:
///     - stencil texture: should have the same pixel format as
///                        ``cp_layer_renderer_configuration_get_drawable_render_context_stencil_format``
///     - renderTargetArrayLength: should be the same as the number of views
///                                in the drawable.
///     - rasterizationRateMap: should be the one provided by the drawable.
///     - layer renderer layout: Dedicated and Shared layout is not supported.
///
/// - Note: If the render encoder has multiple color attachments then set `supportColorAttachmentMapping`
///         to true to avoid Metal API validation errors.
///         This API is not available on simulator; as a workaround, either disable API validation or separate
///         the rendering into multiple render encoders for other color attachments.
///
/// - Note: This function will modify the depth stencil state, the viewports, the vertex amplification count
///         and some of the texture bindings in the render command encoder passed to the function.
///         Make sure to set those values again to the ones expected in your application.
void
cp_drawable_render_context_draw_mask_on_stencil_attachment(cp_drawable_render_context_t render_context,
                                                           id<MTLRenderCommandEncoder> command_encoder,
                                                           uint8_t value)
CF_SWIFT_NAME(cp_drawable_render_context_t.drawMaskOnStencilAttachment(self:commandEncoder:value:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Finish encoding the render context.
///
/// - Parameters:
///    - render_context: The render context to use to present the drawable.
///    - command_encoder: The command encoder to use to render the Compositor effects
///                       and present the drawable.
///
/// - Note: The ownership of the command encoder is passed to the drawable render context, which will
///         call endEncoding on the command encoder.
///
/// - Note: The command encoder used in the render context has the following constraints:
///     - color texture: colorAttachment[0] should contain the color texture
///                      provided by the drawable.
///     - depth texture: depthAttachment should contain the depth texture provided
///                      by the drawable.
///     - renderTargetArrayLength: should be the same as the number of views
///                                in the drawable.
///     - rasterizationRateMap: should be the one provided by the drawable.
///     - layer renderer layout: Dedicated and Shared layout is not supported.
///
/// - Note: If the render encoder has multiple color attachments then set `supportColorAttachmentMapping`
///         to true to avoid Metal API validation errors.
///         This API is not available on simulator; as a workaround, either disable API validation or separate
///         the rendering into multiple render encoders for other color attachments.
void
cp_drawable_render_context_end_encoding(cp_drawable_render_context_t render_context,
                                        id<MTLRenderCommandEncoder> command_encoder)
CF_SWIFT_NAME(cp_drawable_render_context_t.endEncoding(self:commandEncoder:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

#if CP_MTL4_AVAILABLE

/// Store the `value` parameter in the stencil texture in the pixels that Compositor
/// will display on the screen.
///
/// - Parameters:
///    - render_context: The render context to use to present the drawable.
///    - command_encoder: The command encoder to use to render the Compositor effects
///                       and present the drawable.
///    - value: The value to use when updating the stencil texture in the command_encoder.
///
/// - Note: In Full and Mixed immersion style, this will be the full texture.
///
/// - Note: The command encoder used in the render context has the following constraints:
///     - stencil texture: should have the same pixel format as
///                        ``cp_layer_renderer_configuration_get_drawable_render_context_stencil_format``
///     - renderTargetArrayLength: should be the same as the number of views
///                                in the drawable.
///     - rasterizationRateMap: should be the one provided by the drawable.
///     - layer renderer layout: Dedicated and Shared layout is not supported.
///
/// - Note: If the render encoder has multiple color attachments then set `supportColorAttachmentMapping`
///         to true to avoid Metal API validation errors.
///         This API is not available on simulator; as a workaround, either disable API validation or separate
///         the rendering into multiple render encoders for other color attachments.
///
/// - Note: This function will modify the depth stencil state, the viewports, the vertex amplification count
///         and some of the texture bindings in the render command encoder passed to the function.
///         Make sure to set those values again to the ones expected in your application.
void
cp_drawable_render_context_mtl4_draw_mask_on_stencil_attachment(cp_drawable_render_context_t render_context,
                                                                id<MTL4RenderCommandEncoder> command_encoder,
                                                                uint8_t value)
CF_SWIFT_NAME(cp_drawable_render_context_t.drawMaskOnStencilAttachment(self:commandEncoder:value:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Finish encoding the render context.
///
/// - Parameters:
///    - render_context: The render context to use to present the drawable.
///    - command_encoder: The command encoder to use to render the Compositor effects
///                       and present the drawable.
///
/// - Note: The ownership of the command encoder is passed to the drawable render context, which will
///         call endEncoding on the command encoder.
///
/// - Note: The command encoder used in the render context has the following constraints:
///     - color texture: colorAttachment[0] should contain the color texture
///                      provided by the drawable.
///     - depth texture: depthAttachment should contain the depth texture provided
///                      by the drawable.
///     - renderTargetArrayLength: should be the same as the number of views
///                                in the drawable.
///     - rasterizationRateMap: should be the one provided by the drawable.
///     - layer renderer layout: Dedicated and Shared layout is not supported.
///
/// - Note: If the render encoder has multiple color attachments then set `supportColorAttachmentMapping`
///         to true to avoid Metal API validation errors.
///         This API is not available on simulator; as a workaround, either disable API validation or separate
///         the rendering into multiple render encoders for other color attachments.
void
cp_drawable_render_context_mtl4_end_encoding(cp_drawable_render_context_t render_context,
                                             id<MTL4RenderCommandEncoder> command_encoder)
CF_SWIFT_NAME(cp_drawable_render_context_t.endEncoding(self:commandEncoder:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

#endif

#endif

CP_NONNULL_EXTERN_C_END

#endif /* drawable_render_context_h */
