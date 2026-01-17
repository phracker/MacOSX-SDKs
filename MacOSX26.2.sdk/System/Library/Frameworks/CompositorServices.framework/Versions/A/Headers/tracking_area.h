//
//  tracking_area.h
//  CompositorNonUI
//
//  Created by Jacob Wilson on 10/9/24.
//  Copyright © 2024 Apple. All rights reserved.
//

#ifndef cp_tracking_area_h
#define cp_tracking_area_h

CP_NONNULL_EXTERN_C_BEGIN

/// An opaque type that describes a region of a view that
/// interacts with the gaze/cursor.
CP_STRUCT_REF(cp_tracking_area, cp_drawable_t.TrackingArea, API_AVAILABLE(visionos(26.0), macosx(26.0)));

/// An opaque type that describes a hover effect of the tracking area.
CP_STRUCT_REF(cp_hover_effect, API_AVAILABLE(visionos(26.0), macosx(26.0)));

/// A value used when rendering a tracking area.
///
/// When rendering to ``cp_drawable_get_tracking_areas_texture``
/// use this value to write the pixel value.
/// Upper bound limit is based on pixel format set by
/// ``cp_layer_renderer_configuration_get_tracking_areas_format``
/// Can change per-frame for the same rendered mesh/object.
/// A value of 0 is reserved to represent the absence of a tracking area.
typedef uint16_t cp_tracking_area_render_value
CF_TYPED_EXTENSIBLE_ENUM
CF_SWIFT_NAME(cp_tracking_area_t.RenderValue)
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Value to be used in the tracking area texture, to indicate that there
/// is no tracking area at a given pixel.
static const cp_tracking_area_render_value cp_tracking_area_render_value_invalid
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0)) = 0;

/// An identifier for the tracking area.
///
/// All tracking areas should have a unique value in a frame.
/// This value should be constant for the same rendered mesh/object
/// across frames to ensure tracking areas are identifiable between
/// frames.
/// There is no reserved values so all values are considered valid
/// but should be unique.
typedef uint64_t cp_tracking_area_identifier
CF_TYPED_EXTENSIBLE_ENUM
CF_SWIFT_NAME(cp_tracking_area_t.Identifier)
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Identifier reserved as invalid.
///
/// Should not be used as identifier for ``cp_drawable_add_tracking_area``.
static const cp_tracking_area_identifier cp_tracking_area_identifier_invalid
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0)) = 0;

/// Returns the render value for the tracking area.
///
/// - Parameters:
///    - tracking_area: The tracking area for a frame.
/// - Returns: The render value for the tracking area for this frame.
/// This value is what should be used in this frames render pass to identify the
/// tracking area of given identifier.
///
/// Use the returned value in the render pass of ``cp_drawable_get_tracking_areas_texture``
/// for the pixel value of the tracking area identifier.
cp_tracking_area_render_value
cp_tracking_area_get_render_value(cp_tracking_area_t tracking_area)
CF_SWIFT_NAME(getter:cp_tracking_area_t.renderValue(self:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the identifier for the tracking area.
///
/// - Parameters:
///    - tracking_area: The tracking area for a frame.
/// - Returns: The identifier for the tracking area.
/// This should be a unique value for this tracking area and consistent
/// for the rendered mesh/object across frames.
cp_tracking_area_identifier
cp_tracking_area_get_identifier(cp_tracking_area_t tracking_area)
CF_SWIFT_NAME(getter:cp_tracking_area_t.identifier(self:))
API_AVAILABLE(visionos(26.0), macosx(26.0));

/// Returns the hover effect opaque object for the tracking area for this frame.
///
/// - Parameters:
///    - tracking_area: The tracking area for a frame.
/// - Returns: The hover effect for the tracking area.
///
/// The hover effect contains information used to render the hover
/// effect using the tracking area textures and gaze once application
/// render pass has completed.
/// Can only create 1 hover effect per-tracking area, to destroy and
/// disable the hover effect see ``cp_hover_effect_destroy``
cp_hover_effect_t
cp_tracking_area_add_automatic_hover_effect(cp_tracking_area_t tracking_area)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(26.0), macosx(26.0));

CP_NONNULL_EXTERN_C_END

#endif /* cp_tracking_area_h */
