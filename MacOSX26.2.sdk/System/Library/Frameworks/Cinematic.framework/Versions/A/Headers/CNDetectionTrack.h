//
//  CNDetectionTrack.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Cinematic/CNDetection.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Abstract class representing a series of detections of the same subject over time.
@interface CNDetectionTrack : NSObject <NSCopying>

/// The type of subject detected by this detection track.
@property (readonly) CNDetectionType detectionType;

/// The detectionID of the subject detected during this track; unique within a cinematic script.
@property (readonly) CNDetectionID detectionID;

/// The detectionGroupID of the subject detected by the track.
///
/// The detectionGroupID can be used to associate related detections such as the face and torso of the same person.
///
@property (readonly) CNDetectionGroupID detectionGroupID;

/// Whether this detection track was created by the client.
@property (getter=isUserCreated, readonly) BOOL userCreated;

/// Whether this detection track has discrete detections (otherwise continuous).
///
/// A discrete detection track will return detections only at the specific times a detection occurs.
/// A continuous detection track will return a detection for any requested time and an empty array for time ranges.
///
@property (getter=isDiscrete, readonly) BOOL discrete;

#pragma mark - Detections

- (nullable CNDetection *)detectionAtOrBeforeTime:(CMTime)time;
- (nullable CNDetection *)detectionNearestTime:(CMTime)time;

/// Gets the array of detections in the detection track within the given time range. Makes sense for discrete detection tracks only.
- (NSArray <CNDetection *> *)detectionsInTimeRange:(CMTimeRange)timeRange;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// A continuous detection track representing focus at a fixed disparity.
@interface CNFixedDetectionTrack : CNDetectionTrack

/// Create a detection track with fixed focus at the given disparity.
- (instancetype)initWithFocusDisparity:(float)focusDisparity;

/// Create a detection track with fixed focus at the disparity of an existing detection.
- (instancetype)initWithOriginalDetection:(CNDetection *)originalDetection;

@property (readonly) float focusDisparity;

/// The original detection upon which this fixed detection track was based, if any.
///
/// This is the way to determine the time and rect from which fixed focus originated, if any.
/// This detection is not part of the detection track and has a different detectionID or none.
///
/// - Important: To get a detection from the fixed detection track, use detectionAtOrBeforeTime: instead, which will return a properly time-stamped detection.
///
@property (readonly, nullable, strong) CNDetection *originalDetection;

@end

NS_REFINED_FOR_SWIFT
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// A discrete detection track composed of individual detections.
@interface CNCustomDetectionTrack : CNDetectionTrack

/// Initialize a custom detection track with an array of detections, optionally applying smoothing.
///
/// The smoothing algorithm used is the same one that is used for built-in detections during recording.
/// It compensates for some amount of jitter in the disparity measure by smoothing out variability.
///
- (instancetype)initWithDetections:(NSArray<CNDetection *> *)detections smooth:(BOOL)applySmoothing;

@property (readonly, strong) NSArray<CNDetection *> *allDetections;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
