//
// Scaler.h
// HVFLib
//
// Copyright (c) 2024 Apple Inc. All rights reserved.
//

#ifndef HVF_Scaler_H
#define HVF_Scaler_H

#include <hvf/Types.h>
#include <hvf/RenderContext.h>
#include <os/availability.h>

#ifdef __cplusplus
extern "C" {
#endif

// Return the storage that must be allocated for a part renderer
size_t HVF_part_renderer_storage_size(void)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Create a part renderer in the storage provided, which must be at least as large as
// what's returned by HVF_part_renderer_storage_size(). This storage must be on a double
// boundary. The passed-in hvgl table must also be on a double boundary. The hvpm table is optional
// and may be NULL and zero size.
// The return value is 0 for success, nonzero for failure.
int HVF_open_part_renderer(const void *hvgl, size_t hvglSize, const void *hvpm, size_t hvpmSize, void *storage, size_t storageSize)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Return the hvgl table version supported by the scaler code
HVFTableVersion HVF_table_version(HVFPartRenderer *renderer)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Return the version of the hvf library
HVFLibraryVersion HVF_library_version(void)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Return the number of parts in the hvgl table
HVFPartIndex HVF_part_count(HVFPartRenderer *renderer)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Return the number of glyphs (suitable for rendering) in the hvgl table. The
// glyphs are always a prefix of all parts
uint32_t HVF_glyph_count(HVFPartRenderer *renderer)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Set the renderer to render the part indicated by the part index. This
// resets the axis values to the default value of 0.0.
// The return value is 0 for success, nonzero for failure.
int HVF_set_render_part(HVFPartRenderer *renderer, HVFPartIndex partIndex)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Return the number of axes for the current part, or -1 if the part is not set.
int HVF_render_part_axis_count(HVFPartRenderer *renderer)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Set the axis value (in design space, [-1.0, 1.0]) for the indicated global axis
// (using the same axis numbering as would be in the fvar table).
// The return value is 0 for success, nonzero for failure.
int HVF_set_axis_value(HVFPartRenderer *renderer, int axis, HVFAxisValue value)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Render the current part using the supplied callback.
// The return value is 0 for success, nonzero for failure.
int HVF_render_current_part(HVFPartRenderer *renderer, HVFRenderContext context, void *caller_data)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Clear the cache of loaded parts. When rendering a large number of parts
// with the same part renderer, clearing the cache prevents the cache size from
// growing without bounds. This is a time/space tradeoff. Typically the cache should be cleared
// every dozen or so parts.
// The return value is 0 for success, nonzero for failure.
int HVF_clear_part_cache(HVFPartRenderer *renderer)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

// Reclaim any subsidary storage used by the renderer and destroy it.
// The return value is 0 for success, nonzero for failure.
int HVF_close_part_renderer(HVFPartRenderer *renderer)
API_AVAILABLE(macos(15.4), ios(18.4), watchos(11.4), tvos(18.4), visionos(2.4))
;

#ifdef __cplusplus
}
#endif

#endif // HVF_Scaler_H
