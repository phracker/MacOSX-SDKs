/*
	File:  VTFrameProcessorParameters.h
 
	Framework:  VideoToolbox
 
	Copyright © 2023-2024 Apple Inc. All rights reserved.
 
*/
 
#ifndef VTFRAMEPROCESSORPARAMETERS_H
#define VTFRAMEPROCESSORPARAMETERS_H

#ifdef __OBJC__

#import <CoreMedia/CMBase.h>
#import <Foundation/Foundation.h>
#import <VideoToolbox/VTFrameProcessorFrame.h>

NS_HEADER_AUDIT_BEGIN(nullability)


/// The base protocol for input and output processing parameters for a Video Toolbox frame processor implementation.
///
/// Pass an instance of a class corresponding to this protocol to `processFrameWithParameters` calls. In async versions of those APIs, the completion handler returns the same instance.
API_AVAILABLE(macos(15.4), ios(26.0), tvos(26.0), visionos(26.0)) API_UNAVAILABLE(watchos)
@protocol VTFrameProcessorParameters <NSObject>

@required

/// Use `VTFrameProcessorFrame` that contains the current source frame for all processing features; must be non-null.
@property(nonatomic, readonly) VTFrameProcessorFrame * sourceFrame;

@optional // WARNING: Optional properties must be refined for swift

/// Destination frame that contains the destination frame for processors which output a single processed frame.
@property(nonatomic, readonly) VTFrameProcessorFrame * destinationFrame NS_REFINED_FOR_SWIFT;

/// Array of destination frames for processors which may output more than one processed frame.
@property(nonatomic, readonly) NSArray<VTFrameProcessorFrame *> * destinationFrames NS_REFINED_FOR_SWIFT;


@end

NS_HEADER_AUDIT_END(nullability)

#endif // __OBJC__

#endif // VTFRAMEPROCESSORPARAMETERS_H
