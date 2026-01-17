//
//  frame_timing.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_frame_timing_h
#define cp_frame_timing_h

CP_NONNULL_EXTERN_C_BEGIN

/// An opaque type that stores information about a frame’s
/// encoding, rendering, and presentation deadlines.
///
/// Before you start drawing, call the ``cp_frame_predict_timing``
/// function to update and retrieve the frame’s timing information.
/// After you access the frame’s ``cp_drawable_t`` type, get the
/// timing information using the ``cp_drawable_get_frame_timing`` function.
CP_STRUCT_REF(cp_frame_timing, cp_frame_t.Timing, API_AVAILABLE(visionos(1.0), macosx(26.0)));

/// Returns the optimal time to query the input for a frame.
///
/// - Parameters:
///    - timing_information: The frame’s timing information. Fetch this
///    information using the ``cp_frame_predict_timing`` function. If
///    you already called that function once for the frame, you can call
///    the ``cp_drawable_get_frame_timing`` function to get the information
///    instead.
/// - Returns: The Mach absolute time at which to query the input for your frame.
///
/// The returned value indicates the optimal time for you to query the input
/// for your frame.
cp_time_t
cp_frame_timing_get_optimal_input_time(cp_frame_timing_t frame_timing)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the time at which you must finish all work for the specified
/// frame.
///
/// - Parameters:
///    - timing_information: The frame’s timing information. Fetch this
///    information using the ``cp_frame_predict_timing`` function. If you
///    already called that function once for the frame, you can call the
///    ``cp_drawable_get_frame_timing`` function to get the information
///    instead.
/// - Returns: The Mach absolute time at which you must finish all work
/// for the frame. This value reflects the total presentation time minus
/// the overhead for the compositor to render your frame and display it
/// onscreen.
///
/// Finish all CPU and GPU work by the returned time to ensure the timely
/// display of the frame onscreen.
cp_time_t
cp_frame_timing_get_rendering_deadline(cp_frame_timing_t frame_timing)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the time at which the system will display the frame
/// onscreen.
///
/// - Parameters:
///    - timing_information: The frame’s timing information. Fetch
///    this information using the ``cp_frame_predict_timing`` function.
///    If you already called that function once for the frame, you
///    can call the ``cp_drawable_get_frame_timing`` function to get
///    the information instead.
/// - Returns: The Mach absolute time at which the layer presents the
/// frame onscreen.
///
/// You can use the presentation time as a synchronization point for
/// other parts of your app. For example, you might play a specific
/// audio clip when the frame appears.
cp_time_t
cp_frame_timing_get_presentation_time(cp_frame_timing_t frame_timing)
CF_REFINED_FOR_SWIFT API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Returns the time to used to predict transform of trackable anchors to provide best
/// content registration with the frame.
///
/// - Parameters:
///    - timing_information: The frame’s timing information. Fetch
///    this information using the ``cp_frame_predict_timing`` function.
///    If you already called that function once for the frame, you
///    can call the ``cp_drawable_get_frame_timing`` function to get
///    the information instead.
/// - Returns: The Mach absolute time to use to predict transform of a trackable anchor.
///
/// You can use trackable anchor prediction time for prediction of ARKit trackable anchors
/// to register rendered anchored content to the real-world objects. The offset of this time 
/// to presentation time is variable, so it is recommended to query this per-frame.
///
/// - note: For predicting ARKit device anchor use presentation time, see
/// ``cp_frame_timing_get_presentation_time``
cp_time_t
cp_frame_timing_get_trackable_anchor_time(cp_frame_timing_t frame_timing)
API_AVAILABLE(visionos(2.0), macosx(26.0))
CF_REFINED_FOR_SWIFT;

CP_NONNULL_EXTERN_C_END

#endif /* cp_frame_timing_h */
