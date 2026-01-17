//
//  CNDecision.h
//  Cinematic
//
//  Copyright © 2022-2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>

#import <Cinematic/CNDetection.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

NS_REFINED_FOR_SWIFT NS_SWIFT_SENDABLE
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0)) API_UNAVAILABLE(watchos)
/// Represents a decision to focus on a specific detectionID or detectionGroupID; optionally strong.
///
/// A strong decision keeps focus for as long as possible.
///
@interface CNDecision : NSObject <NSCopying>

/// Make a decision to focus on the detection with the given detectionID.
/// A strong decision keeps focus for as long as possible.
- (instancetype)initWithTime:(CMTime)time
                 detectionID:(CNDetectionID)detectionID
                      strong:(BOOL)isStrong;

/// Make a decision to focus on the best among those detections with the same detectionGroupID.
/// A strong decision keeps focus for as long as possible.
- (instancetype)initWithTime:(CMTime)time
            detectionGroupID:(CNDetectionGroupID)detectionGroupID
                      strong:(BOOL)isStrong;

/// The first presentation time at which the subject should be in focus.
/// The rack focus transition to the subject occurs prior to this time.
@property (readonly) CMTime time;

/// The detectionID of the detection to focus on if this is not a group decision.
@property (readonly) CNDetectionID detectionID;

/// The detectionGroupID of the detection to focus on if this is a group decision.
@property (readonly) CNDetectionGroupID detectionGroupID;

/// Whether this is a user-created decision, or a base decision.
@property (readonly, getter=isUserDecision) BOOL userDecision;

/// Whether this is a group decision or not.
@property (readonly, getter=isGroupDecision) BOOL groupDecision;

/// Whether this is a strong decision or not.
/// A strong decision keeps focus for as long as possible.
@property (readonly, getter=isStrongDecision) BOOL strongDecision;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
