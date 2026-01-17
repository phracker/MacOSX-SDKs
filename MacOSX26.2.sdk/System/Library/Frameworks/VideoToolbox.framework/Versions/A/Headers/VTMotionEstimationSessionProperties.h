/*
	File:  VTMotionEstimationSessionProperties.h
 
	Framework:  VideoToolbox
 
	Copyright 2022 Apple Inc. All rights reserved.
 
*/

#ifndef _VT_MOTION_ESTIMATION_SESSION_PROPERTIES_H_
#define _VT_MOTION_ESTIMATION_SESSION_PROPERTIES_H_

#include <CoreMedia/CMBase.h>
#include <CoreFoundation/CoreFoundation.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#pragma pack(push)
#pragma pack()

#pragma mark Creation Options


/// Options you use to create motione-estimation sessions.
///
/// Use these keys in the ``motionVectorProcessorSelectionOptions`` parameter to ``VTMotionEstimationSessionCreate`` to
/// configure the created session.


/// The size of the search blocks that motion estimation session uses.
///
/// ``VTMotionEstimationSessionCreate`` takes a dictionary of creation options, `motionVectorProcessorSelectionOptions`.
/// You can supply ``kVTMotionEstimationSessionCreationOption_MotionVectorSize`` with `CFNumber` to override the default
/// search block size. Supported motion vector size is 4 or 16, meaning 4x4 or 16x16 respectively. 16x16 is the default
/// if you don't provide this key.
VT_EXPORT const CFStringRef kVTMotionEstimationSessionCreationOption_MotionVectorSize API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read/write, CFNumber

/// An option to use for higher quality motion estimation.
///
/// ``VTMotionEstimationSessionCreate`` takes a dictionary of creation options, `motionVectorProcessorSelectionOptions`.
/// You can supply ``kVTMotionEstimationSessionCreationOption_UseMultiPassSearch`` with `kCFBooleanTrue` to provide
/// higher quality motion estimation. True-motion achieves higher quality by running the motion estimator in multiple
/// passes. The default is `kCFBooleanFalse`.
VT_EXPORT const CFStringRef kVTMotionEstimationSessionCreationOption_UseMultiPassSearch API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read/write, CFBoolean

/// Enable multi pass true motion detection.
///
/// Renamed to `kVTMotionEstimationSessionCreationOption_UseMultiPassSearch`.
VT_EXPORT const CFStringRef kVTMotionEstimationSessionCreationOption_DetectTrueMotion API_UNAVAILABLE(macos, ios, tvos, watchos, visionos); // Read/write, CFBoolean DEPRECATED

/// A label you use to log and track resources.
///
/// ``VTMotionEstimationSessionCreate`` takes a dictionary of creation options, `motionVectorProcessorSelectionOptions`.
/// You can supply ``kVTMotionEstimationSessionCreationOption_Label`` with `CFString` to specify a label used in logging
/// and resource tracking.
VT_EXPORT const CFStringRef kVTMotionEstimationSessionCreationOption_Label API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos); // Read/write, CFString

#pragma mark Properties

/// Properties of motion-estimation sessions.
///
/// This file defines properties the you may uses to configure motion-estimation sessions after creation.
///
/// Clients can query supported properties by calling ``VTSessionCopySupportedPropertyDictionary``, and use
/// ``VTSessionSetProperty`` and ``VTSessionCopyProperty``.

#pragma pack(pop)

#if defined(__cplusplus)
}
#endif

#endif // _VT_MOTION_ESTIMATION_SESSION_PROPERTIES_H_
