//
//  ARAppClipCodeAnchor.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <ARKit/ARAnchor.h>

NS_ASSUME_NONNULL_BEGIN

/**
A value describing app clip code URL decoding state.
*/
API_AVAILABLE(ios(14.3))
typedef NS_ENUM(NSInteger, ARAppClipCodeURLDecodingState) {
    /** App clip code tracking is attempting to decode the URL. */
    ARAppClipCodeURLDecodingStateDecoding,
	
    /** App clip code tracking failed to decode the URL. */
    ARAppClipCodeURLDecodingStateFailed,
    
    /** App clip code tracking decoded the URL. */
    ARAppClipCodeURLDecodingStateDecoded
} NS_SWIFT_NAME(ARAppClipCodeAnchor.URLDecodingState);

/**
 An anchor representing an app clip code in the world.
 */
API_AVAILABLE(ios(14.3))
@interface ARAppClipCodeAnchor : ARAnchor <ARTrackable>

/**
The URL encoded in this app clip code. Not nil only if urlDecodingState is .decoded.
 */
@property (nonatomic, copy, nullable, readonly) NSURL *url;

/**
 The URL decoding state of the app clip code.
 */
@property (nonatomic, assign, readonly) ARAppClipCodeURLDecodingState urlDecodingState;

/**
The estimated radius of the app clip code in meters.
 */
@property (nonatomic, assign, readonly) float radius;

/** Unavailable */
- (instancetype)initWithTransform:(simd_float4x4)transform NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name transform:(simd_float4x4)transform NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
