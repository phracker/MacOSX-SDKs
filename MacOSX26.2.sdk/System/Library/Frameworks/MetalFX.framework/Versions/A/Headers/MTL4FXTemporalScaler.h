//
//  MTL4FXTemporalScaler.h
//  MetalFX
//
//  Copyright (c) 2025 Apple Inc. All rights reserved.
//

#import <Metal/Metal.h>
#import <Metal/MTL4Compiler.h>
#import <MetalFX/MTLFXTemporalScaler.h>

/// An upscaling effect that generates a higher resolution texture in a render pass by analyzing multiple input textures over time.
///
/// You create instances of this class by calling ``MTLFXTemporalScalerDescriptor/newTemporalScalerWithDevice:compiler:``.
///
/// When using instances of objects conforming to this protocol, you configure the different properties it
/// inherits from protocol ``MTLFXTemporalScalerBase`` and then call ``encodeToCommandBuffer:`` to
/// encode its work into a Metal command buffer.
///
/// See ``MTLFXTemporalScalerBase`` for more details on configuring and using spatial scalers.
///
API_AVAILABLE(macos(26.0), ios(26.0))
#if defined(TARGET_OS_VISION) && TARGET_OS_VISION
API_UNAVAILABLE(visionos)
#endif
@protocol MTL4FXTemporalScaler <MTLFXTemporalScalerBase>

/// Encode this spatial scaler work into a command buffer.
///
/// - Parameters:
///    - commandBuffer: A command buffer into which this spatial scaler encodes work.
///
- (void)encodeToCommandBuffer:(nonnull id<MTL4CommandBuffer>)commandBuffer;

@end

