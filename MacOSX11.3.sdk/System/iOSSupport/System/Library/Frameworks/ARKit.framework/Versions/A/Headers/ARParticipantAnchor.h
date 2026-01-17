//
//  ARParticipantAnchor.h
//  ARKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This anchor represents the physical position and orientation of another participant in the collaborative session.
 
 @discussion The participant anchors are automatically added to the ARSession and are updated with each frame.
           The participant can be identified by `sessionIdentifier` property of the anchor.
 */
API_AVAILABLE(ios(13.0))
@interface ARParticipantAnchor : ARAnchor

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
