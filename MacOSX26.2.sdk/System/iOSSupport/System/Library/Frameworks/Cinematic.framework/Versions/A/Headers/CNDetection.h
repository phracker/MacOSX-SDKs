//
//  CNDetection.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef int64_t CNDetectionID NS_TYPED_EXTENSIBLE_ENUM;
typedef int64_t CNDetectionGroupID NS_TYPED_EXTENSIBLE_ENUM;

/// The type of object that was detected.
///
/// Special detection types include:
/// - autoFocus: from the autofocus system of the camera
/// - fixedFocus: an explicit request to focus at a fixed disparity
/// - custom: an object tracked via a custom tracker
///
typedef NS_ENUM(NSInteger, CNDetectionType) {
    CNDetectionTypeUnknown = 0,

    CNDetectionTypeHumanFace = 1,
    CNDetectionTypeHumanHead = 2,
    CNDetectionTypeHumanTorso = 3,

    CNDetectionTypeCatBody = 4,
    CNDetectionTypeDogBody = 5,

    CNDetectionTypeCatHead = 9,
    CNDetectionTypeDogHead = 10,

    CNDetectionTypeSportsBall = 11,

    CNDetectionTypeAutoFocus = 100,
    CNDetectionTypeFixedFocus = 101,
    CNDetectionTypeCustom = 102,
} API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos);

NS_REFINED_FOR_SWIFT
/// A cinematic detection of a subject.
///
/// Specifies the type, distance (as disparity), bounds (as a normalized rectangle), and time (as CMTime) of the detection.
/// Detections obtained from the cinematic script include a detectionID that can be used to track the detection over time.
/// Some types of detections also include a detectionGroupID that associates related detections (e.g. the face and torso of the same person).
///
NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
@interface CNDetection : NSObject <NSCopying>

/// Initialize a cinematic detection.
///
/// For playback and edit, most detections are obtained by from the cinematic script rather than being created.
/// However, if you need to add a custom track, you can build an array of detections to create one.
/// Any detections you create will not have a valid detectionID until the custom track is added to the cinematic script.
/// Doing so will return the assigned detectionID. Any detections newly obtained from the cinematic script will have their assigned detectionID.
///
/// - Parameters:
///   - time: the presentation time of the frame in which the detection occurred
///   - detectionType: the type of object that was detected (face, torso, cat, dog, etc.)
///   - normalizedRect: the rectangle within the image where the object occurs, normalized such that (0.0, 0.0) is the top-left and (1.0, 1.0) is the bottom-right
///   - focusDisparity: the disparity to use in order to focus on the object (use the static `disparity` method to compute if unknown)
///
- (instancetype)initWithTime:(CMTime)time
               detectionType:(CNDetectionType)detectionType
              normalizedRect:(CGRect)normalizedRect
              focusDisparity:(float)focusDisparity;

/// The presentation time of the frame in which the detection occurred.
@property (readonly) CMTime time;

/// The type of object that was detected (face, torso, cat, dog, etc.)
@property (readonly) CNDetectionType detectionType;

/// The rectangle within the image where the object occurs, normalized such that (0.0, 0.0) is the top-left and (1.0, 1.0) is the bottom-right.
@property (readonly) CGRect normalizedRect;

/// The disparity to use in order to focus on the object.
/// If the disparity is unknown, use the class method to find it: `disparityInNormalizedRect:sourceDisparity:detectionType:priorDisparity:`.
@property (readonly) float focusDisparity;

/// An unique identifier assigned by the cinematic script to all detections of the same subject and detection type across time.
/// If you build a custom detection track, the detectionID will be assigned when you add it to the script.
@property (readonly) CNDetectionID detectionID;

/// An unique identifier assigned by the cinematic script to all detections of the same subject and related detection types across time.
/// For example, the face/torso detections of the same person are assigned the same detectionGroupID.
@property (readonly) CNDetectionGroupID detectionGroupID;

/// Determine whether a given detectionID is valid
+ (BOOL)isValidDetectionID:(CNDetectionID)detectionID;

/// Determine whether a given detectionGroupID is valid
+ (BOOL)isValidDetectionGroupID:(CNDetectionGroupID)detectionGroupID;

/// A localized accessibility label converting a specific detection type into a broad category (person, pet, etc.).
+ (NSString *)accessibilityLabelForDetectionType:(CNDetectionType)detectionType;

/// Determine the disparity to use to focus on the object in the rectangle.
/// - Parameters:
///   - disparityBuffer: A pixel buffer from the cinematic disparity track for the frame in which the object occurs.
///   - normalizedRect: The rectangle within the disparity buffer where the object occurs, normalized such that (0.0, 0.0) is the top-left and (1.0, 1.0) is the bottom-right of the disparity buffer.
///   - detectionType: The type of object expected within the rectangle. Pass `CNDetectionTypeUnknown` if unknown.
///   - priorDisparity: The disparity of the object in the prior frame. This helps ensure the object is not mistaken for another that enters the same rectangle. Pass `NAN` if there is no known prior, such as in the first frame in which the object is being tracked.
+ (float)disparityInNormalizedRect:(CGRect)normalizedRect
                   sourceDisparity:(CVPixelBufferRef)sourceDisparity
                     detectionType:(CNDetectionType)detectionType
                    priorDisparity:(float)priorDisparity;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
