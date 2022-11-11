//
//  ARTrackingStatusTypes.h
//  ARKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 A value describing the camera’s tracking state.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARTrackingState) {
    /** Tracking is not available. */
    ARTrackingStateNotAvailable,
    
    /** Tracking is limited. See tracking reason for details. */
    ARTrackingStateLimited,
    
    /** Tracking is Normal. */
    ARTrackingStateNormal,
} NS_REFINED_FOR_SWIFT;

/**
 A reason describing why the camera’s tracking state is limited.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARTrackingStateReason) {
    /** Tracking is not limited. */
    ARTrackingStateReasonNone,
    
    /** Tracking is limited due to initialization in progress. */
    ARTrackingStateReasonInitializing,
    
    /** Tracking is limited due to a excessive motion of the camera. */
    ARTrackingStateReasonExcessiveMotion,
    
    /** Tracking is limited due to a lack of features visible to the camera. */
    ARTrackingStateReasonInsufficientFeatures,
    
    /** Tracking is limited due to a relocalization in progress. */
    ARTrackingStateReasonRelocalizing API_AVAILABLE(ios(11.3)),

} NS_REFINED_FOR_SWIFT;
