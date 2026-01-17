//
//  MTL4FXFrameInterpolator.h
//  MetalFX
//
//  Copyright (c) 2025 Apple Inc. All rights reserved.
//

#import <Metal/Metal.h>


#import <MetalFX/MTLFXFrameInterpolator.h>

/// An effect that generates textures by interpolating two input textures.
///
/// You create instances of this class by calling ``MTLFXFrameInterpolatorDescriptor/newFrameInterpolatorWithDevice:compiler:``.
///
/// When using instances of objects conforming to this protocol, you configure the different properties it
/// inherits from protocol ``MTLFXFrameInterpolatorBase`` and then call ``encodeToCommandBuffer:`` to
/// encode its work into a Metal command buffer.
///
/// See ``MTLFXFrameInterpolatorBase`` for more details on configuring and using frame interpolators.
///
API_AVAILABLE(macos(26.0), ios(26.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@protocol MTL4FXFrameInterpolator <MTLFXFrameInterpolatorBase>

/// Encode this frame interpolator's work into a command buffer.
///
/// - Parameters:
///    - commandBuffer: A command buffer into which this frame interpolator encodes work.
///
- (void)encodeToCommandBuffer:(nonnull id<MTL4CommandBuffer>)commandBuffer;

@end

