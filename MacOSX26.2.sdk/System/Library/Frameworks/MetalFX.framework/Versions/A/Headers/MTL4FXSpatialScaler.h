//
//  MTL4FXSpatialScaler.h
//  MetalFX
//
//  Copyright (c) 2025 Apple Inc. All rights reserved.
//


#import <Metal/Metal.h>
#import <Metal/MTL4Compiler.h>
#import <MetalFX/MTLFXSpatialScaler.h>

/// An upscaling effect that generates a higher resolution texture in a render pass by spatially analyzing an input texture.
///
/// You create instances of this class by calling ``MTLFXSpatialScalerDescriptor/newSpatialScalerWithDevice:compiler:``.
///
/// When using instances of objects conforming to this protocol, you configure the different properties it
/// inherits from protocol ``MTLFXSpatialScalerBase`` and then call ``encodeToCommandBuffer:`` to
/// encode its work into a Metal command buffer.
///
/// See ``MTLFXSpatialScalerBase`` for more details on configuring and using spatial scalers.
///
API_AVAILABLE(macos(26.0), ios(26.0))
@protocol MTL4FXSpatialScaler <MTLFXSpatialScalerBase>

/// Encode this spatial scaler work into a command buffer.
///
/// - Parameters:
///    - commandBuffer: A command buffer into which this spatial scaler encodes work.
///
- (void)encodeToCommandBuffer:(nonnull id<MTL4CommandBuffer>)commandBuffer;

@end

