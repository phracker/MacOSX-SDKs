//
//  cp_types.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_types_h
#define cp_types_h

CP_NONNULL_EXTERN_C_BEGIN

/// A frame index in the layer’s timeline.
///
/// The layer assigns sequential indexes to the frames it provides to
/// your app.
typedef uint64_t cp_layer_frame_index_t CF_SWIFT_NAME(LayerFrameIndex) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// The sequential index for a frame in the compositor’s timeline.
///
/// During the creation of your content, the compositor creates
/// frames for you to render your content. This type stores the
/// index the compositor assigns to that frame. The compositor
/// presents frames onscreen sequentially based on their indexes.
typedef uint64_t cp_compositor_frame_index_t CF_SWIFT_NAME(CompositorFrameIndex) API_AVAILABLE(visionos(1.0), macosx(26.0));

/// A Mach absolute time clock value.
///
/// Mach absolute time measures the number of ticks that have elapsed
/// since an arbitrary point after system startup. Each value represents
/// a unique point in time during the course of your app's execution.
typedef struct cp_time { uint64_t cp_mach_abs_time; } API_AVAILABLE(visionos(1.0), macosx(26.0))
CF_REFINED_FOR_SWIFT cp_time_t CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Converts a Mach absolute time value to a Core Foundation time value.
///
/// - Parameters:
///    - time: The time value to convert.
/// - Returns: The elapsed time in seconds that correspond to the specified
/// time value.
CFTimeInterval
cp_time_to_cf_time_interval(cp_time_t time)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Blocks the current thread until the specified time.
///
/// - Parameters:
///    - time: The Mach absolute time at which to wake up the thread.
void cp_time_wait_until(cp_time_t time)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Axis direction convention for defining the X/Y/Z directions.
///
/// This can be used to define different coordinate systems such
/// as model/view/normalized device coordinate spaces for rendering.
///
/// @note only defined +X = right convention as this is exclusively used
/// by ``cp_drawable_compute_projection``
/// which currently only supports right convention mainly due to foveated
/// rendering rasterization rate maps using a right axis.
typedef CF_ENUM(uint8_t, cp_axis_direction_convention) {
     cp_axis_direction_convention_right_up_back      CF_SWIFT_NAME(rightUpBack) = 0,
     cp_axis_direction_convention_right_up_forward   CF_SWIFT_NAME(rightUpForward),
     cp_axis_direction_convention_right_down_back    CF_SWIFT_NAME(rightDownBack),
     cp_axis_direction_convention_right_down_forward CF_SWIFT_NAME(rightDownForward),
} CF_SWIFT_NAME(AxisDirectionConvention)
API_AVAILABLE(visionos(2.0), macosx(26.0));

/// Render quality controls the quality which drawing happens at.
///
/// This can be used to increase the quality of what users see,
/// however this directly impacts the memory allocated for resources
/// which is billed to the app as well as per-frame GPU time. The app
/// should monitor its frame rate to ensure its not regularly missing
/// frames and will likely need to change the quality based on scene
/// complexity that is being shown.
///
/// To control the memory allocated for resources
/// @see ``cp_layer_renderer_configuration_set_max_render_quality``
/// To control the per-frame GPU cost
/// @see ``cp_layer_renderer_set_render_quality``
typedef float cp_render_quality_t
CF_TYPED_EXTENSIBLE_ENUM
CF_SWIFT_NAME(CP_OBJECT_cp_layer_renderer.RenderQuality)
API_AVAILABLE(visionos(26.0), macosx(26.0));

CP_NONNULL_EXTERN_C_END

#endif /* cp_types_h */
