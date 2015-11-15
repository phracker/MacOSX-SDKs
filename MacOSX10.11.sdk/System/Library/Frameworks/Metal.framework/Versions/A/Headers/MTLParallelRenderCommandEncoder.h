//
//  MTLParallelRenderCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Metal/MTLDefines.h>
#import <Metal/MTLRenderPass.h>
#import <Metal/MTLCommandEncoder.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLRenderCommandEncoder;

/*!
 @protocol MTLParallelRenderCommandEncoder
 @discussion The MTLParallelRenderCommandEncoder protocol is designed to allow a single render to texture operation to be efficiently (and safely) broken up across multiple threads.
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLParallelRenderCommandEncoder <MTLCommandEncoder>

/*!
 @method renderCommandEncoder
 @abstract Return a new autoreleased object that conforms to <MTLRenderCommandEncoder> that may be used to encode on a different thread.
 */
- (id <MTLRenderCommandEncoder>)renderCommandEncoder;

@end
NS_ASSUME_NONNULL_END