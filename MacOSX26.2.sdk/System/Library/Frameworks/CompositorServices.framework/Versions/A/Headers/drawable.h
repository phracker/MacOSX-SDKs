//
//  drawable.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_drawable_h
#define cp_drawable_h

CP_NONNULL_EXTERN_C_BEGIN

/// The state of ownership for the drawable.
///
/// Use these constants to determine whether the drawable is ready
/// for you to use. When the drawable is in the ``cp_drawable_state_rendering``
/// state, you can begin drawing. Other states indicate the
/// drawable is either busy or not assigned to a frame.
typedef CF_ENUM(uint32_t, cp_drawable_state) {
    
    /// A drawable that is not in use and ready for assignment to a frame.
    cp_drawable_state_available = 0,
    
    /// A drawable that is assigned to a frame and ready to accept
    /// your drawing commands.
    cp_drawable_state_rendering,
    
    /// A drawable that the compositor is currently displaying onscreen.
    cp_drawable_state_presenting
} CF_SWIFT_NAME(cp_drawable_t.State) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// The target where the drawable will be displayed/used.
///
/// Use these constants to determine whether content should
/// be drawn for certain targets.
typedef CF_ENUM(uint32_t, cp_drawable_target) {

    /// A drawable that is targeting the built-in display,
    /// this is what a user will see in the device.
    cp_drawable_target_built_in CF_SWIFT_NAME(builtIn) = 0,

    /// A drawable that will be used for capture purposes,
    /// this could be used for video or AirPlay streaming and
    /// will be visible to users outside of the device.
    cp_drawable_target_capture,

} CF_SWIFT_NAME(cp_drawable_t.Target) API_AVAILABLE(visionos(26.0), macosx(26.0));

/// An opaque type that contains the textures and other information
/// you need to set up your render pipeline.
///
/// Use the drawable type to retrieve the textures for your render pipelines,
/// and use the drawable’s views to get details about how to render to those
/// textures. Get the drawable for a frame using the ``cp_frame_query_drawable``
/// function. The layer manages a limited number of reusable drawable types
/// and recycles them after each use. Draw only one frame at a time to ensure
/// each new frame’s drawable type is ready in time.
CP_STRUCT_REF(cp_drawable, CP_OBJECT_NAME(cp_layer_renderer).Drawable, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Returns the number of color and depth textures available in the drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: The number of textures available for drawing. For example, a return
/// value of `2` indicates there are two color textures and two depth
/// textures available.
///
/// Use the returned value as the maximum number of textures to retrieve
/// from the ``cp_drawable_get_color_texture`` or ``cp_drawable_get_depth_texture``
/// functions.
size_t
cp_drawable_get_texture_count(cp_drawable_t drawable)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the number of tracking areas textures available in the drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: The number of textures available for drawing. For example, a return
/// value of `2` indicates there are two tracking areas textures available.
///
/// Use the returned value as the maximum number of textures to retrieve
/// from the ``cp_drawable_get_tracking_areas_texture``function.
/// This will be equal to ``cp_drawable_get_texture_count`` when tracking
/// areas textures are enabled through the configuration otherwise will be 0.
size_t
cp_drawable_get_tracking_areas_texture_count(cp_drawable_t drawable)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));

#ifdef __OBJC__

/// Returns the depth texture at the specified index in the drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - index: The index of the depth texture you want. The index must
///    be greater than or equal to `0` and less than the value that
///    ``cp_drawable_get_texture_count`` returns.
/// - Returns: The Metal depth texture at the specified index.
///
/// Use the returned texture in your render pipeline as the depth texture
/// for your content. The layer’s texture topology determines the layout and
/// content for each texture. The drawable’s views contain information
/// about how those views map to the textures.
id<MTLTexture>
cp_drawable_get_depth_texture(cp_drawable_t drawable, size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the color texture at the specified index in the drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - index: The index of the color texture you want. The index must
///    be greater than or equal to `0` and less than the value that
///    ``cp_drawable_get_texture_count`` returns.
/// - Returns: The Metal color texture at the specified index.
///
/// Use the returned texture in your render pipeline to store the pixels
/// you want to appear onscreen. The layer’s texture topology determines
/// the layout and content for each texture. The drawable’s views contain
/// information about how those views map to the textures.
id<MTLTexture>
cp_drawable_get_color_texture(cp_drawable_t drawable, size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the tracking areas texture at the specified index in the drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - index: The index of the texture you want. The index must
///    be greater than or equal to `0` and less than the value that
///    ``cp_drawable_get_tracking_areas_texture_count`` returns.
/// - Returns: The Metal object index texture at the specified index.
///
/// Use the returned texture in your render pipeline to store the tracking areas ID
/// used for hover effects and indirect gestures. The layer’s texture topology determines
/// the layout and content for each texture. The drawable’s views contain
/// information about how those views map to the textures.
id<MTLTexture>
cp_drawable_get_tracking_areas_texture(cp_drawable_t drawable, size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));
#endif

/// Returns a tracking area which is create on the drawable's list of tracking areas.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - identifier: The unique identifier for the tracking area.
/// - Returns: A tracking area that was created.
///
/// A tracking area describes a region of a view that interacts
/// with the gaze/cursor.
/// Cannot use ``cp_tracking_area_identifier_invalid`` as
/// an identifier.
CP_NULLABLE_STRUCT_REF
cp_tracking_area_t
cp_drawable_add_tracking_area(cp_drawable_t drawable,
                              cp_tracking_area_identifier identifier)
CF_SWIFT_NAME(cp_drawable_t.addTrackingArea(self:identifier:)) API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the number of rasterization rate maps associated with the
/// drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: The number of rasterization rate maps available for drawing.
///
/// Use the returned value as the maximum number of rate maps to retrieve
/// from the ``cp_drawable_get_rasterization_rate_map`` function.
size_t
cp_drawable_get_rasterization_rate_map_count(cp_drawable_t drawable)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

#ifdef __OBJC__
/// Returns the rasterization rate map at the specified index in the drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - index: The index of the rasterization rate map you want.
///    The index must be greater than or equal to `0` and less than the value
///    that ``cp_drawable_get_rasterization_rate_map_count`` returns.
/// - Returns: The rasterization rate map at the specified index.
///
/// Apply the rasterization rate map to your render descriptor when you set
/// up your drawing environment. A rate map defines how the GPU scales
/// different parts of the texture to fill the screen. You use these rate
/// maps to save time and render less important parts of your scene at lower
/// resolutions. For example, when foveation is enabled, the drawable
/// includes a rasterization rate map to render the portions of the texture
/// in someone’s peripheral vision at a lower resolution.
id<MTLRasterizationRateMap>
cp_drawable_get_rasterization_rate_map(cp_drawable_t drawable, size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the Y flipped rasterization rate map at the specified index in the drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - index: The index of the rasterization rate map you want.
///    The index must be greater than or equal to `0` and less than the value
///    that ``cp_drawable_get_rasterization_rate_map_count`` returns.
/// - Returns: The Y flipped rasterization rate map at the specified index.
///
/// This function provides a Y flipped map that is generated form the ``cp_drawable_get_rasterization_rate_map``.
/// Flipped is defined as +Y = down for clip/normalized device coordinates (flipped from Metal).
/// If projection matrix is needed, use ``cp_drawable_compute_projection``
/// with a +Y = down axes convention to generate the correct matrix.
///
/// Can only be used for intermediary render passes, the final render pass of the
/// drawable it cannot be flipped and must use Metal convention of +Y = up.
///
/// Generating a flipped rasterization rate map will bring additional computational
/// cost to your render loop.
///
/// In order to generate Y flipped rasterization rate maps in your rendering session,
/// update the ``cp_layer_renderer_configuration_t`` using the function
/// ``cp_layer_renderer_configuration_set_generate_flipped_rasterization_rate_maps``.
id<MTLRasterizationRateMap>
cp_drawable_get_flipped_rasterization_rate_map(cp_drawable_t drawable, size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));
#endif

/// Returns the number of separate views to draw for the frame.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: The number of separate views to draw.
///
/// The number of views corresponds to the number of separate versions
/// of your scene you create for the frame. For a device with stereoscopic
/// video, you render two views — one for each eye. The actual number of
/// views can vary based on the drawing environment or your app’s
/// configuration. For example, you typically render only one view in
/// Simulator.
///
/// Fetch the actual views using the ``cp_drawable_get_view`` function.
size_t
cp_drawable_get_view_count(cp_drawable_t drawable)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the specified view from the drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - index: The index of the view you want. The index must be
///    greater than or equal to 0 and less than the value that
///    ``cp_drawable_get_view_count`` returns.
/// - Returns: The view at the specified index.
///
/// Each view contains information you need to render into the drawable’s
/// textures.
cp_view_t
cp_drawable_get_view(cp_drawable_t drawable, size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

#ifdef __OBJC__

/// Specifies the world position and orientation to apply to the current
/// frame.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - device_anchor: The `ar_device_anchor` that specifies the 3D rotation and translation
///    factors you applied to your content when you rendered the frame.
///
/// Device anchor information tells the compositor the position and orientation
/// you used to render your frame's content. If you specify a device anchor value,
/// the compositor compares your value against the hardware-provided device anchor
/// information before displaying the frame onscreen. If the device anchor values
/// don't match, the compositor adjusts the pixels of your frame to align it
/// with the hardware device anchor.
///
/// Device anchor information is particularly important on a head-mounted display
/// because it helps your content more closely match the actual movements
/// of someone's head. Because the actual device anchor can change between the time
/// you encode your drawing commands and the time the frame appears onscreen,
/// you must predict the device anchor in advance using available information. The
/// ``cp_frame_timing_get_optimal_input_time`` function provides a good
/// time to start the prediction for each frame. Use the
/// ``cp_frame_timing_get_presentation_time`` function to get the presentation
/// time for the frame.
void
cp_drawable_set_device_anchor(cp_drawable_t drawable, _Nullable ar_device_anchor_t device_anchor)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the predicted device anchor information you specified for the frame.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: The current device anchor for the frame, or ``null``
/// if you didn't specify a device anchor.
_Nullable ar_device_anchor_t
cp_drawable_get_device_anchor(cp_drawable_t drawable)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

#endif /* __OBJC__ */

/// Returns the distances to the far and near clipping planes you
/// use during drawing.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: The distances to the far and near planes in meters.
/// The compositor returns values in reverse-z ordering, with the
/// value for the far plane in the vector’s `x` property and the
/// value for the near plane in the vector’s `y` property.
///
/// Use this function to get the near and far planes for the specified
/// drawable. These planes are the distances from the person viewing
/// the content. The compositor uses these values to compute the
/// perspective projection matrix and to clip content that is not
/// between the near and far planes.
simd_float2
cp_drawable_get_depth_range(cp_drawable_t drawable)
CF_SWIFT_NAME(getter:cp_drawable_t.depthRange(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Sets the distances to the near and far clipping planes for the
/// current drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - depth_range: The distances to the far and near planes in meters.
///    Specify the values in reverse-z ordering, with the value for the
///    far plane in the vector’s `x` property and the value for the near
///    plane in the vector’s `y` property.
///
/// Use this function to change the depth range for this frame of content.
/// The near and far planes correspond to distances from the person viewing
/// the content. The compositor uses these values to compute the perspective
/// projection matrix and to clip content that is not between the near and far
/// planes. It only supports reverse-Z depth, which means the value in the
/// texture should be 1 for near 0 for far.
///
/// After setting depth range for the drawable, the projection matrix will
/// need to be requeried, see ``cp_drawable_compute_projection``
///
/// Configure the default depth range for all frames in your layer using the
/// ``cp_layer_renderer_configuration_set_default_depth_range`` function.
void
cp_drawable_set_depth_range(cp_drawable_t drawable, simd_float2 depth_range)
CF_SWIFT_NAME(setter:cp_drawable_t.depthRange(self:depthRange:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

#ifdef __OBJC__

/// Encodes a notification event to the specified command buffer to present
/// the drawable’s content onscreen.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - command_buffer: The command buffer you used to encode your
///    frame’s content. If the command buffer is already committed,
///    this function aborts your app with an error.
///
/// - Note: Commit the command buffer after calling present.
///
/// Call this function as the last step before committing the specified
/// command buffer. Specifically, call it after you finish encoding all
/// the work required to render the frame, and immediately before you
/// call the command buffer’s <doc://com.apple.documentation/documentation/metal/mtlcommandbuffer/1443003-commit>
/// method. The function adds a presentation event to the buffer that
/// causes the compositor to display your frame.
void
cp_drawable_encode_present(cp_drawable_t drawable,
                           id<MTLCommandBuffer> command_buffer)
CF_SWIFT_NAME(cp_drawable_t.encodePresent(self:commandBuffer:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

#if CP_MTL4_AVAILABLE
/// Encodes a notification event to the specified command buffer to present
/// the drawable’s content onscreen.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///
/// - Note: Commit the command buffer to the layer queue before calling present.
///
/// Call this function as the last step before committing the specified
/// command buffer. Specifically, call it after you finish encoding all
/// the work required to render the frame, and immediately before you
/// call the command buffer’s <doc://com.apple.documentation/documentation/metal/mtlcommandbuffer/1443003-commit>
/// method. The function adds a presentation event to the buffer that
/// causes the compositor to display your frame.
void
cp_drawable_mtl4_encode_present(cp_drawable_t drawable)
CF_SWIFT_NAME(cp_drawable_t.encodePresent(self:)) API_AVAILABLE(visionos(26.0), macosx(26.0));
#endif

#endif

/// Returns a value that indicates the current operational state
/// of the drawable type.
///
/// - Parameters: The drawable to check.
/// - Returns: ``cp_drawable_state/cp_drawable_state_rendering`` if the
/// drawable type is ready for you to draw your content, or any other value if
/// the compositor currently owns the drawable.
///
/// Compositor reuses the underlying data structures associated with
/// drawable types, and the state of the drawable indicates whether
/// it's ready for you to use. Perform your drawing operations only
/// when the drawable is in the ``cp_drawable_state/cp_drawable_state_rendering`` state.
enum cp_drawable_state
cp_drawable_get_state(cp_drawable_t drawable)
CF_SWIFT_NAME(getter:cp_drawable_t.state(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns a value that indicates the target of the drawable type.
///
/// - Parameters: The drawable to check.
/// - Returns: ``cp_drawable_target/cp_drawable_target_built_in`` if the
/// drawable will be displayed for the user in the device, or any other value if the drawable
/// maybe used for other purposes.
///
/// When drawing for the drawable this can be used to alter
/// what is rendered for different targets.
/// Renderer should always prioritize ``cp_drawable_target/cp_drawable_target_built_in``
/// target type.
cp_drawable_target
cp_drawable_get_target(cp_drawable_t drawable)
CF_SWIFT_NAME(getter:cp_drawable_t.target(self:)) API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the index of the frame of content for you to produce.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: The presentation index of the frame.
///
/// When your compositor scene becomes visible, you start drawing
/// frames of content. The compositor assigns a sequential index to
/// each frame to indicate its position in the final output. You can
/// use these indexes to differentiate frames during drawing or predict
/// future frame indexes. For example, you might start playback of an
/// audio file when a specific frame appears onscreen.
cp_compositor_frame_index_t
cp_drawable_get_presentation_frame_index(cp_drawable_t drawable)
CF_SWIFT_NAME(getter:cp_drawable_t.presentationFrameIndex(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the timing information for the frame of the specified drawable.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: The timing information for the drawable’s associated frame.
///
/// Pass the returned type to the ``cp_frame_timing_get_optimal_input_time``
/// function to determine when to start the encoding process for a frame.
/// Pass it to other functions to determine other time-related deadlines.
cp_frame_timing_t
cp_drawable_get_frame_timing(cp_drawable_t drawable)
CF_SWIFT_NAME(getter:cp_drawable_t.frameTiming(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the perspective projection matrix to be used for rendering.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
///    - normalized_device_coordinates_convension: The
///    normalized device coordinate axes convention used.
///    - view_index: The index of the view you want. The index must
///    be greater than or equal to `0` and less than the value that
///    ``cp_drawable_get_view_count`` returns.
/// - Returns: A perspective projection matrix that transforms coordinates
///  from view coordinate space to clip space.
///
/// To update depth range used for the projection matrix, see
/// ``cp_drawable_set_depth_range``. Should be called
/// prior to computing the projection matrix.
///
/// The convention is defined in normalized device coordinates, which impact
/// the rendering direction of rendering but have no impact on the convention
/// used for model/view space. To convert from view space to the axis direction convention
/// used by the projection matrix, a rotation/mirror matrix can be applied pre-projection matrix.
///
/// The axes are defined as:
/// • X axes determines the horizontal direction of pixels -- right convention means the left-most pixel is the left of the view
/// • Y axes determines the vertical direction of pixels -- up convention means the top-most pixel is the top of the view
/// • Z axes determines the handedness/winding order -- depth should still be written in reverse-Z for best precision
/// The default convention is ``cp_axis_direction_convention_right_up_back``
/// for CompositorServices and Metal renderers which has a counter-clockwise winding order.
///
/// Final render pass must be done using ``cp_axis_direction_convention_right_up_back``
/// or ``cp_axis_direction_convention_right_up_forward`` depending on the renderer
/// winding order convention.
/// Only intermediate passes can be done using different coordinate systems.
///
/// For foveated renderers using +Y = down convention, will need to use the flipped version of
/// the rasterization rate maps, see ``cp_drawable_get_flipped_rasterization_rate_map``
simd_float4x4
cp_drawable_compute_projection(cp_drawable_t drawable,
                               cp_axis_direction_convention normalized_device_coordinates_convension,
                               size_t view_index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(2.0), macosx(26.0));

/// Returns whether content capture is protected and it is safe to
/// draw content that should be protected from capture.
///
/// - Parameters:
///    - drawable: The drawable for a frame.
/// - Returns: Whether it is safe to draw content that is for built-in
/// display only. When this value is true, any capture of content
/// being displayed on the built-in display will be obscured by the
/// system. If false, it cannot be assumed that content will not
/// be seen by users outside of the device, both live and recorded.
///
/// Use this function to ensure that drawing that is only meant for
/// eyes in the device is not drawn when false.
/// Only adopt if app has adopted SwiftUI `activatesContentCaptureProtected`
/// scene modifier and drawing will have content that is not desired
/// to meant to be captured.
/// For ``cp_drawable_target_capture`` this will
/// always return false as it is upto the renderer to handle drawing
/// content that will be captured beyond the built-in displays.
bool
cp_drawable_is_content_capture_protected(cp_drawable_t drawable)
CF_SWIFT_NAME(getter:cp_drawable_t.isContentCaptureProtected(self:))
API_AVAILABLE(visionos(26.0))
API_UNAVAILABLE(macosx, ios);

#ifdef __OBJC__

/// Adds a render context to a drawable.
/// This object will draw any content that the compositor needs to render
/// in the application.
/// - Note: The render context can only be used when the layer renderer is using layered layout
///         or in platforms that only render one view (ex: simulator)
///
/// - Note: The render context makes use of the device_anchor set in
///         ``cp_drawable_set_device_anchor`` the device_anchor should be set in the
///         drawable before calling ``cp_drawable_add_render_context``.
cp_drawable_render_context_t
cp_drawable_add_render_context(cp_drawable_t drawable, id<MTLCommandBuffer> cmd_buffer)
CF_SWIFT_NAME(cp_drawable_t.addRenderContext(self:commandBuffer:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

#if CP_MTL4_AVAILABLE
/// Adds a render context to a drawable.
/// This object will draw any content that the compositor needs to render
/// in the application.
/// - Note: The render context can only be used when the layer renderer is using layered layout
///         or in platforms that only render one view (ex: simulator)
///
/// - Note: The render context makes use of the device_anchor set in
///         ``cp_drawable_set_device_anchor`` the device_anchor should be set in the
///         drawable before calling ``cp_drawable_add_render_context``.
cp_drawable_render_context_t
cp_drawable_add_mtl4_render_context(cp_drawable_t drawable)
CF_SWIFT_NAME(cp_drawable_t.addRenderContext(self:))
API_AVAILABLE(visionos(26.0), macosx(26.0));
#endif

#endif

/*
 * MARK: - cp_drawable_array
 */

/// An opaque type that contains the drawable types and other information
/// you need to set up your render pipeline.
///
/// See ``cp_drawable_t`` for more information about drawables.
CP_STRUCT_REF(cp_drawable_array, API_AVAILABLE(visionos(26.0), macosx(26.0)));

/// Returns the drawable at the specified index in the array.
///
/// - Parameters:
///    - drawable_array: The drawable array for a frame.
///    - index: The index of the drawable you want. The index must
///    be greater than or equal to `0` and less than the value that
///    ``cp_drawable_array_get_count`` returns.
/// - Returns: The drawable available for drawing at the specified index.
///
/// The ``cp_drawable_t`` type contains the textures and other
/// information you need to set up your render descriptor in Metal.
cp_drawable_t
cp_drawable_array_get_drawable(cp_drawable_array_t drawable_array, size_t index)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the number of drawables in the array.
///
/// - Parameters:
///    - drawable_array: The drawable array for a frame.
/// - Returns: The number of drawables available for drawing. For example, a return
/// value of `2` indicates there are two drawables for this frame.
///
/// Use the returned value as the maximum number of textures to retrieve
/// from the ``cp_drawable_array_get_drawable`` functions.
size_t
cp_drawable_array_get_count(cp_drawable_array_t drawable_array)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));

CP_NONNULL_EXTERN_C_END

#endif /* cp_drawable_h */
