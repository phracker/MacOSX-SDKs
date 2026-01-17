//
//  layer_renderer.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_layer_renderer_h
#define cp_layer_renderer_h

CP_NONNULL_EXTERN_C_BEGIN

/// The potential states of the layer renderer, which tell you how to
/// proceed with drawing operations.
typedef CF_ENUM(uint32_t, cp_layer_renderer_state) {
    
    /// A state that indicates the layer renderer isn't currently drawing.
    ///
    /// A layer renderer starts in this state and later transitions to the
    /// running or invalid states. Don't draw while in this state.
    /// Wait until the layer changes to one of the other states to
    /// take further action on the layer.
    cp_layer_renderer_state_paused = 1,
    
    /// A state that indicates the layer renderer is ready for you to draw
    /// your content.
    ///
    /// When the layer enters this state, start your rendering loop
    /// and draw your content. Keep drawing frames of content until
    /// the layer transitions to another state.
    cp_layer_renderer_state_running,
    
    /// A state that indicates the layer renderer no longer supports drawing
    /// operations.
    ///
    /// A layer enters this state shortly before the system releases
    /// its resources. When the layer enters this state, exit your
    /// rendering loop and release any drawing-related structures.
    cp_layer_renderer_state_invalidated
} CF_SWIFT_NAME(CP_OBJECT_cp_layer_renderer.State) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// An opaque type that provides the Metal types and timing
/// information you need to draw your content.
CP_OBJECT_DECL(cp_layer_renderer, LayerRenderer, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Returns the configuration details you used to create the
/// specified layer.
///
/// - Parameters layer_renderer: The layer renderer to query.
/// - Returns: An opaque type you use to retrieve the configuration details.
///
/// Provide a custom ``LayerStageConfiguration`` to provide the initial
/// configuration details for the layer. After the system creates the layer, use this
/// function to retrieve those details. The system uses this information during the
/// initial setup of the layer's data structures. Changes you make to the
/// returned structure don't affect the layer's current configuration.
cp_layer_renderer_configuration_t
cp_layer_renderer_get_configuration(cp_layer_renderer_t layer_renderer)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the configured properties of the specified layer renderer.
///
/// - Parameters layer_renderer: The layer renderer to query.
/// - Returns: An opaque type you can use to fetch the individual
/// layer properties.
///
/// The layer properties include details about the layer's textures,
/// such as their organization and the location of drawable views in those
/// textures.
cp_layer_renderer_properties_t
cp_layer_renderer_get_properties(cp_layer_renderer_t layer_renderer)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

#ifdef __OBJC__

/// Returns the GPU interface that the layer uses for drawing operations.
///
/// - Parameters layer_renderer: The layer renderer to query.
/// - Returns: The Metal device to use for your drawing operations.
///
/// You can inspect the returned device for any information you might need.
/// The system uses the returned device to create the textures you use for
/// drawing. It also uses the device to create synchronization events for
/// the layer.
id<MTLDevice>
cp_layer_renderer_get_device(cp_layer_renderer_t layer_renderer)
CF_SWIFT_NAME(getter:CP_OBJECT_cp_layer_renderer.device(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

#if CP_MTL4_AVAILABLE
/// Returns the command queue that the layer uses for drawing operations.
///
/// - Parameters layer_renderer: The layer renderer to query.
///
/// Should only be called with when supporting Metal4 through configuration.
/// ``cp_layer_renderer_configuration_set_supports_mtl4``
id<MTL4CommandQueue>
cp_layer_renderer_get_mtl4_command_queue(cp_layer_renderer_t layer_renderer)
CF_SWIFT_NAME(getter:CP_OBJECT_cp_layer_renderer.commandQueue(self:)) API_AVAILABLE(visionos(26.0), macosx(26.0));
#endif

#endif

/// Returns the layer's current state, which indicates whether the layer is
/// visible and ready for you to draw content.
///
/// - Parameters layer_renderer: The layer renderer to query.
/// - Returns: The current state of the layer.
///
/// Use the layer's state value to determine when to start and stop your
/// rendering loop. Draw content only when the layer is in the
/// ``cp_layer_renderer/cp_layer_renderer_state_running`` state. Stop your rendering loop when
/// the layer enters other states. When the layer reaches the
/// ``cp_layer_renderer/cp_layer_renderer_state_invalidated`` state, it's safe to
/// clean up and deallocate your render loop structures.
enum cp_layer_renderer_state
cp_layer_renderer_get_state(cp_layer_renderer_t layer_renderer)
CF_SWIFT_NAME(getter:CP_OBJECT_cp_layer_renderer.state(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Stops further execution of your code until the layer renderer leaves
/// the paused state.
///
/// - Parameters layer_renderer: The layer renderer to monitor. If the layer isn't
/// in the ``cp_layer_renderer/cp_layer_renderer_state_paused`` state, this function returns
/// immediately.
///
/// Call this function to let the system handle events while
/// you wait for the layer renderer to become ready. The function services
/// incoming layer-related events until the layer exits the paused
/// state.
void
cp_layer_renderer_wait_until_running(cp_layer_renderer_t layer_renderer)
CF_SWIFT_NAME(CP_OBJECT_cp_layer_renderer.waitUntilRunning(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the next frame to use for drawing.
///
/// - Parameters layer_renderer: The layer renderer that manages the drawing destination.
///
/// - Returns: An opaque type to use for drawing operations. The function
/// returns `nil` if the layer is paused, invalidated, or has too many frames
/// already in use.
///
/// This function retrieves the next frame for you to use in your drawing
/// operations. The system maintains a limited number of frames, so don't try
/// to render more than one frame in advance. If this function returns `nil`,
/// wait a short time and try again. After the system draws the current frame,
/// it returns that frame to the shared pool and makes it available for you
/// to use.
///
/// The index of each returned frame is always greater than the index of the
/// previous frame. The system increments index values sequentially so you
/// can differentiate frames you are currently drawing.
CP_NULLABLE_STRUCT_REF
cp_frame_t
cp_layer_renderer_query_next_frame(cp_layer_renderer_t layer_renderer)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Return how many times a frame is repeated on display. This is typically used to
/// build dynamic frame pacing.
///
/// - Parameters layer_renderer: The layer on which you're drawing.
///
/// - Returns: The repeat count. If the repeat count is set to a value greater or equal to 1, it means this
/// layer repeated the client frame `repeat count` times, effectively multiplying the
/// frame duration by `repeat count + 1`.
///
/// Lowering the number of frames being rendered every second will decrease the power usage per frame.
/// This value should only be increased if appropriate for the content being rendered.
int
cp_layer_renderer_get_minimum_frame_repeat_count(cp_layer_renderer_t layer_renderer)
CF_SWIFT_NAME(getter:CP_OBJECT_cp_layer_renderer.minimumFrameRepeatCount(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Set the frame repeat count. This is typically used to build dynamic frame pacing.
///
/// - Parameters:
///    - layer_renderer: The layer on which you're drawing.
///    - frame_repeat_count: How many times a frame is repeated on display.
///
/// If the repeat count is set to a value greater or equal to 1, it means this
/// layer repeats the client frame `repeat count` times, effectively multiplying the
/// frame duration by `repeat count + 1`.
///
/// Lowering the number of frames being rendered every second will decrease the power usage per frame.
/// This value should only be increased if appropriate for the content being rendered.
void
cp_layer_renderer_set_minimum_frame_repeat_count(cp_layer_renderer_t layer_renderer,
                                                 int frame_repeat_count)
CF_SWIFT_NAME(setter:CP_OBJECT_cp_layer_renderer.minimumFrameRepeatCount(self:frame_repeat_count:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Get the render quality to be used by the drawables.
///
/// - Parameters:
///    - layer_renderer: The layer on which you're drawing.
///
/// The render quality will increase the resolution at which rendering happens.
/// This value cannot exceed the quality specified on the layer renderer configuration
/// see ``cp_layer_renderer_configuration_set_max_render_quality``.
/// The quality will be changed to the target render quality over a set duration to hide
/// the transition of quality from the user.
///
/// The renderer should monitor its frame rate to determine whether its making the frames
/// on time. If it is unable to maintain proper frame rate, the app should reduce the render
/// quality, reduce the scene complexity, or increase the frame repeat count see
/// ``cp_layer_renderer_set_minimum_frame_repeat_count``.
/// It is generally preferable to reduce anything else before increasing the frame repeat count.
cp_render_quality_t
cp_layer_renderer_get_render_quality(cp_layer_renderer_t layer_renderer)
CF_SWIFT_NAME(getter:CP_OBJECT_cp_layer_renderer.renderQuality(self:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Set the render quality to be used by the drawables.
///
/// - Parameters:
///    - layer_renderer: The layer on which you're drawing.
///    - render_quality: The value of quality [0, 1].
///    With 0 being the minimum quality that is supported on the device,
///    and 1 being the highest quality that is supported on the device.
///
/// The render quality will increase the resolution at which rendering happens.
/// This value cannot exceed the quality specified on the layer renderer configuration
/// see ``cp_layer_renderer_configuration_set_max_render_quality``.
/// The quality will be changed to the target render quality over a set duration to hide
/// the transition of quality from the user.
///
/// The renderer should monitor its frame rate to determine whether its making the frames
/// on time. If it is unable to maintain proper frame rate, the app should reduce the render
/// quality, reduce the scene complexity, or increase the frame repeat count see
/// ``cp_layer_renderer_set_minimum_frame_repeat_count``.
/// It is generally preferable to reduce anything else before increasing the frame repeat count.
void
cp_layer_renderer_set_render_quality(cp_layer_renderer_t layer_renderer, cp_render_quality_t render_quality)
CF_SWIFT_NAME(setter:CP_OBJECT_cp_layer_renderer.renderQuality(self:renderQuality:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

CP_NONNULL_EXTERN_C_END

#endif /* cp_layer_renderer_h */
