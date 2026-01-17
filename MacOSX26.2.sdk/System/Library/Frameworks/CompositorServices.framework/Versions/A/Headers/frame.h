//
//  frame.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_frame_h
#define cp_frame_h

CP_NONNULL_EXTERN_C_BEGIN

/// An opaque type that provides access to the timing information and
/// data types you need to render a single frame of content.
///
/// During each cycle of your app’s rendering loop, retrieve a frame
/// using the ``cp_layer_renderer_query_next_frame`` function and use it to
/// render your app’s content. The ``cp_frame_t`` type provides access
/// to the information you need to render your frame in a timely manner.
/// It also provides access to the ``cp_drawable_t`` type you use to
/// retrieve the textures you need for drawing.
///
/// Separate the work you do for each frame into two phases: the update
/// phase and the encode phase. Use the update phase to perform app-specific
/// tasks, such as processing interactions with your content. Use the
/// encode phase to commit the Metal commands you need to draw your
/// content for the current pose. For both phases, use frame functions
/// to notify the Compositor when you start and stop the related work.
/// For example, surround update work with calls to the
/// ``cp_frame_start_update`` and ``cp_frame_end_update``
/// functions.
CP_STRUCT_REF(cp_frame, CP_OBJECT_NAME(cp_layer_renderer).Frame, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Returns the sequential index number of the specified frame.
///
/// - Parameters:
///    - frame: The frame to query.
/// - Returns: The sequential index of the frame, which is always a
/// positive integer.
///
/// The layer assigns a unique index number to each frame, starting at
/// the first frame and incrementing the index by 1 for each new frame.
cp_layer_frame_index_t
cp_frame_get_frame_index(cp_frame_t frame)
CF_SWIFT_NAME(getter:cp_frame_t.frameIndex(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Computes and returns the predicted timing information for the specified frame.
///
/// - Parameters:
///    - frame: The frame you're preparing to draw.
/// - Returns: The predicted timing information for the specified frame, or `NULL`
/// if the layer is in the ``cp_layer_renderer/cp_layer_renderer_state_paused`` or
/// ``cp_layer_renderer/cp_layer_renderer_state_invalidated`` state.
///
/// Use the returned timing information in any functions that return
/// frame-related deadlines. For example, pass the timing information
/// to the ``cp_frame_timing_get_optimal_input_time`` function to
/// determine when to start encoding the frame. This function updates
/// the frame-specific timing information using the latest data from
/// the compositor before it returns it.
///
/// Don’t call this function after you call ``cp_frame_query_drawable``
/// for the specified frame. If you need the timing information after you
/// retrieve the frame's ``cp_drawable_t`` type, save the return value
/// of this function, or call ``cp_drawable_get_frame_timing`` to get
/// the information from the drawable instead.
CP_NULLABLE_STRUCT_REF
cp_frame_timing_t
cp_frame_predict_timing(cp_frame_t frame)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the drawable type you use to retrieve the textures and
/// drawing environment for the frame.
///
/// - Parameters:
///    - frame: The frame to query.
/// - Returns: The drawable type, or `NULL` if the layer is in the 
/// ``cp_layer_renderer/cp_layer_renderer_state_paused`` or
/// ``cp_layer_renderer/cp_layer_renderer_state_invalidated`` state.
///
/// Call this function when you're ready to encode the drawing commands
/// for the frame. The ``cp_drawable_t`` type contains the textures and
/// other information you need to set up your render descriptor in Metal.
///
/// Note: This function isn't safe to be called concurrently. Always ensure a
/// single thread call this function at a time.
CP_NULLABLE_STRUCT_REF
cp_drawable_t
cp_frame_query_drawable(cp_frame_t frame)
API_DEPRECATED("Use cp_frame_query_drawables instead", visionos(1.0, 26.0))
API_UNAVAILABLE(macosx, ios)
CF_REFINED_FOR_SWIFT;

/// Returns the drawable array type you use to retrieve the drawables for
/// drawing environment for the frame.
///
/// - Parameters:
///    - frame: The frame to query.
/// - Returns: The drawable array type, if the layer is in the
/// ``cp_layer_renderer/cp_layer_renderer_state_paused`` or
/// ``cp_layer_renderer/cp_layer_renderer_state_invalidated`` states
/// the array will have a count of 0 and frame is invalid.
///
/// Call this function when you're ready to encode the drawing commands
/// for the frame. The ``cp_drawable_t`` type contains the textures and
/// other information you need to set up your render descriptor in Metal.
/// See ``cp_drawable_get_target`` for how each drawable will be used.
///
/// If array count is 0, the frame has been cancelled as there are no drawables
/// to draw to and the frame should be discarded and is invalid to access.
///
/// Note: This function isn't safe to be called concurrently. Always ensure a
/// single thread call this function at a time.
cp_drawable_array_t
cp_frame_query_drawables(cp_frame_t frame)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Notifies the compositor that you started updating the app-specific
/// content you need to render the frame.
///
/// - Parameters:
///    - frame: The frame you are ready to prepare.
///
/// This function helps you optimize your app’s rendering efficiency.
/// Before you render a frame, you might need to respond to
/// interactions and update your app's data structures before you can
/// render items in your scene.  Call this function immediately
/// before you start that work, and call the ``cp_frame_end_update``
/// function as soon as you finish. The compositor uses the time difference
/// to improve its predictions for when to start the frame encoding process.
///
/// Move as much work as possible into the update phase to minimize encoding
/// time. Don't do any work that relies on the current pose information during
/// the update phase. Instead, make any pose-related changes during the
/// encoding phase.
void
cp_frame_start_update(cp_frame_t frame)
CF_SWIFT_NAME(cp_frame_t.startUpdate(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Notifies the compositor that you finished updating the app-specific
/// content you need to render the frame.
///
/// - Parameters:
///    - frame: The frame you finished preparing.
///
/// This function helps you optimize your app’s rendering efficiency.
/// Before you render a frame, you might need to respond to
/// interactions and update your app's data structures before you can
/// render items in your scene. Call the ``cp_frame_start_update``
/// function immediately before you start that work, and call this function
/// as soon as you finish. Compositor uses the frame update time to improve
/// its predictions for when to start the frame encoding process.
///
/// Move as much work as possible into the update phase to minimize encoding
/// time. Don't do any work that relies on the current pose information during
/// the update phase. Instead, make any pose-related changes during the
/// encoding phase.
void
cp_frame_end_update(cp_frame_t frame)
CF_SWIFT_NAME(cp_frame_t.endUpdate(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Notifies the compositor that you're ready to generate the
/// GPU commands to render the specified frame.
///
/// - Parameters:
///    - frame: The frame you're ready to encode and send to the GPU.
///
/// This function helps you optimize your app’s rendering efficiency.
/// Call this function function before you start any of the GPU work that depends
/// on the input data. Call the ``cp_frame_end_submission`` function after
/// you finish your drawing commands and are ready to commit the frame to
/// the GPU. Compositor uses the time difference to improve its predictions
/// for when to start the frame submission process. Those predictions help
/// you schedule the encoding process at a more optimal time for the
/// system.
void
cp_frame_start_submission(cp_frame_t frame)
CF_SWIFT_NAME(cp_frame_t.startSubmission(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Notifies the compositor that you finished generating the GPU
/// commands to render the specified frame.
///
/// - Parameters:
///    - frame: The frame you're ready to submit to the GPU.
///
/// This function helps you optimize your app’s rendering efficiency.
/// Call the ``cp_frame_start_submission`` function before you start any of the GPU
/// work that depends on the input data. Call this function after
/// you finish your drawing commands and are ready to commit the frame to
/// the GPU. Compositor uses the time difference to improve its predictions
/// for when to start the frame submission process. Those predictions help
/// you schedule the encoding process at a more optimal time for the
/// system.
void
cp_frame_end_submission(cp_frame_t frame)
CF_SWIFT_NAME(cp_frame_t.endSubmission(self:)) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the transform which can be used for monocular frustum culling. A matrix to convert
/// between the device coordinate space to normalized device coordinate space.
/// This should be acquired after query frame via ``cp_layer_renderer_query_next_frame`` and
/// before calling into ``cp_frame_end_submission``. Renderer should not utilize this transform for actual rendering output.
/// 
/// - Parameters:
///    - frame: frame: The frame you finished preparing.
///    - drawable_target: whether this is intended for `built_in` or `recorder`drawable
///    - normalized_device_coordinates_convension: The
///    normalized device coordinate axes convention used.
///    - view_index: The index of the view you want. The index must
///    be greater than or equal to `0` and less than the value that
///    ``cp_frame_get_drawable_target_view_count`` returns.
///    - increase_tangents: The requested increased tangents
///    for computing the projection transform. Values should be positive.
///    - depth_range: The requested depth range
///    for computing the projection transform. The range should be bigger than the one used for rendering
/// - Returns: A perspective projection matrix that transforms coordinates
///  from view coordinate space to clip space.
///
/// The convention is defined in normalized device coordinates, which impact
/// the rendering direction of rendering but have no impact on the convention
/// used for model/view space. To convert from view space to the axis direction convention
/// used by the projection matrix, a rotation/mirror matrix can be applied pre-projection matrix.
///
/// The axes are defined as:
/// • X axes determines the horizontal direction of pixels -- right convention means the left-most pixel is the left of the view
/// • Y axes determines the vertical direction of pixels -- up convention means the top-most pixel is the top of the view
/// • Z axes determines the handedness/winding order
/// The default convention is ``cp_axis_direction_convention_right_up_back``
/// for CompositorServices and Metal renderers which has a counter-clockwise winding order.
///
/// To avoid false positives during culling, transform should have broader tangents and depth range compared to one
/// will be used for rendering. As the the time performing culling becomes more distant from `presentation time`,
/// renderer should request for wider tangents/depth.
simd_float4x4
cp_frame_monocular_frustum_matrix_for_drawable_target(cp_frame_t frame,
                                                      cp_drawable_target drawable_target,
                                                      cp_axis_direction_convention normalized_device_coordinates_convension,
                                                      size_t view_index,
                                                      simd_float4 increase_tangents,
                                                      simd_float2 depth_range)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the transform which can be used for binocular frustum culling. A matrix to convert
/// between the device coordinate space to normalized device coordinate space.
/// This should be acquired after query frame via ``cp_layer_renderer_query_next_frame`` and
/// before calling into ``cp_frame_end_submission``. Renderer should not utilize this transform for actual rendering output.
///
/// @code
///                 /
///                /
///               / Monocular eye
///              /------
///  Binocular  /
///     eye    |
///             \     ╱
///              \   ╱
///               \ ╱
///                \ Monocular eye
///                 ╲
///                  ╲
///                   ╲
///@endcode
///
/// - Parameters:
///    - frame: frame: The frame you finished preparing.
///    - drawable_target: whether this is intended for `built_in` or `recorder`drawable
///    - normalized_device_coordinates_convension: The
///    normalized device coordinate axes convention used.
///    - increase_tangents: The requested increased tangents
///    for computing the projection transform. Values should be positive.
///    - depth_range: The requested  depth range
///    for computing the projection transform. The range should be bigger than the one used for rendering
/// - Returns: A transform which combines  perspective projection matrix that transforms coordinates
///  from view coordinate space to clip space and a view matrix which brings device coordinate space to binocular camera space
///
/// The convention is defined in normalized device coordinates, which impact
/// the rendering direction of rendering but have no impact on the convention
/// used for model/view space. To convert from view space to the axis direction convention
/// used by the projection matrix, a rotation/mirror matrix can be applied pre-projection matrix.
///
/// The axes are defined as:
/// • X axes determines the horizontal direction of pixels -- right convention means the left-most pixel is the left of the view
/// • Y axes determines the vertical direction of pixels -- up convention means the top-most pixel is the top of the view
/// • Z axes determines the handedness/winding order
/// The default convention is ``cp_axis_direction_convention_right_up_back``
/// for CompositorServices and Metal renderers which has a counter-clockwise winding order.
///
/// It computes corresponding binocular view relative to views, for defined transforms and projection matrix.
///
/// To avoid false positives during culling, transform should have broader tangents and depth range compared to one
/// will be used for rendering. As the the time performing culling becomes more distant from `presentation time`,
/// renderer should request for wider tangents/depth.
///
/// ``cp_frame_get_drawable_target_view_count`` for given target should be more than 1 view.
simd_float4x4
cp_frame_binocular_frustum_matrix_for_drawable_target(cp_frame_t frame,
                                                      cp_drawable_target drawable_target,
                                                      cp_axis_direction_convention convention,
                                                      simd_float4 increase_tangents,
                                                      simd_float2 depth_range)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the number of view in the drawable target.
///
/// - Parameters:
///    - frame: frame: The frame you finished preparing.
///    - drawable_target: whether this is intended for `built_in` or `recorder`drawable
/// - Returns: The number of views available for drawing. For example, a return
/// value of `2` indicates there are two views for this target drawable in this frame.
/// value of `0` indicates there is no view available for this target drawable in this frame.
///
/// Use the returned value as the maximum number of views to retrieve
/// from the ``cp_frame_binocular_frustum_matrix_for_drawable_target``
/// or ``cp_frame_monocular_frustum_matrix_for_drawable_target`` functions.
size_t
cp_frame_get_drawable_target_view_count(cp_frame_t frame,
                                        cp_drawable_target drawable_target)
CF_SWIFT_NAME(cp_frame_t.drawableTargetViewCount(self:target:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the transform which can be used for monocular frustum culling. A matrix to convert
/// between the device coordinate space to normalized device coordinate space.
/// This should be acquired after query frame via ``cp_layer_renderer_query_next_frame`` and
/// before calling into ``cp_frame_end_submission``. Renderer should not utilize this transform for actual rendering output.
///
/// - Parameters:
///    - frame: frame: The frame you finished preparing.
///    - normalized_device_coordinates_convension: The
///    normalized device coordinate axes convention used.
///    - view_index: The index of the view you want. The index must
///    be greater than or equal to `0` and less than the value that
///    ``cp_layer_renderer_properties_get_view_count`` returns.
///    - increase_tangents: The requested increased tangents
///    for computing the projection transform. Values should be positive.
///    - depth_range: The requested depth range
///    for computing the projection transform. The range should be bigger than the one used for rendering
/// - Returns: A perspective projection matrix that transforms coordinates
///  from view coordinate space to clip space.
///
/// The convention is defined in normalized device coordinates, which impact
/// the rendering direction of rendering but have no impact on the convention
/// used for model/view space. To convert from view space to the axis direction convention
/// used by the projection matrix, a rotation/mirror matrix can be applied pre-projection matrix.
///
/// The axes are defined as:
/// • X axes determines the horizontal direction of pixels -- right convention means the left-most pixel is the left of the view
/// • Y axes determines the vertical direction of pixels -- up convention means the top-most pixel is the top of the view
/// • Z axes determines the handedness/winding order
/// The default convention is ``cp_axis_direction_convention_right_up_back``
/// for CompositorServices and Metal renderers which has a counter-clockwise winding order.
///
/// To avoid false positives during culling, transform should have broader tangents and depth range compared to one
/// will be used for rendering. As the the time performing culling becomes more distant from `presentation time`,
/// renderer should request for wider tangents/depth.
simd_float4x4
cp_frame_monocular_frustum_matrix(cp_frame_t frame,
                                  cp_axis_direction_convention normalized_device_coordinates_convension,
                                  size_t view_index,
                                  simd_float4 increase_tangents,
                                  simd_float2 depth_range)
CF_REFINED_FOR_SWIFT
API_DEPRECATED("Use cp_frame_monocular_frustum_matrix_for_drawable_target with drawable target instead", visionos(2.0, 26.0));

/// Returns the transform which can be used for binocular frustum culling. A matrix to convert
/// between the device coordinate space to normalized device coordinate space.
/// This should be acquired after query frame via ``cp_layer_renderer_query_next_frame`` and
/// before calling into ``cp_frame_end_submission``. Renderer should not utilize this transform for actual rendering output.
///
/// @code
///                 /
///                /
///               / Monocular eye
///              /------
///  Binocular  /
///     eye    |
///             \     ╱
///              \   ╱
///               \ ╱
///                \ Monocular eye
///                 ╲
///                  ╲
///                   ╲
///@endcode
///
/// - Parameters:
///    - frame: frame: The frame you finished preparing.
///    - normalized_device_coordinates_convension: The
///    normalized device coordinate axes convention used.
///    - increase_tangents: The requested increased tangents
///    for computing the projection transform. Values should be positive.
///    - depth_range: The requested  depth range
///    for computing the projection transform. The range should be bigger than the one used for rendering
/// - Returns: A transform which combines  perspective projection matrix that transforms coordinates
///  from view coordinate space to clip space and a view matrix which brings device coordinate space to binocular camera space
///
/// The convention is defined in normalized device coordinates, which impact
/// the rendering direction of rendering but have no impact on the convention
/// used for model/view space. To convert from view space to the axis direction convention
/// used by the projection matrix, a rotation/mirror matrix can be applied pre-projection matrix.
///
/// The axes are defined as:
/// • X axes determines the horizontal direction of pixels -- right convention means the left-most pixel is the left of the view
/// • Y axes determines the vertical direction of pixels -- up convention means the top-most pixel is the top of the view
/// • Z axes determines the handedness/winding order
/// The default convention is ``cp_axis_direction_convention_right_up_back``
/// for CompositorServices and Metal renderers which has a counter-clockwise winding order.
///
/// It computes corresponding binocular view relative to views, for defined transforms and projection matrix.
///
/// To avoid false positives during culling, transform should have broader tangents and depth range compared to one
/// will be used for rendering. As the the time performing culling becomes more distant from `presentation time`,
/// renderer should request for wider tangents/depth.
simd_float4x4
cp_frame_binocular_frustum_matrix(cp_frame_t frame,
                                  cp_axis_direction_convention convention,
                                  simd_float4 increase_tangents,
                                  simd_float2 depth_range)
CF_REFINED_FOR_SWIFT
API_DEPRECATED("Use cp_frame_binocular_frustum_matrix_for_drawable_target with drawable target instead", visionos(2.0, 26.0));

CP_NONNULL_EXTERN_C_END

#endif /* cp_frame_h */
