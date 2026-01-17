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

/*!
 @method setColorStoreAction:atIndex:
 @brief If the the store action for a given color attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setColorStoreAction:atIndex: must be used to finalize the store action before endEncoding is called.
 @param storeAction The desired store action for the given color attachment.  This may be set to any value other than MTLStoreActionUnknown.
 @param colorAttachmentIndex The index of the color attachment
*/
- (void)setColorStoreAction:(MTLStoreAction)storeAction atIndex:(NSUInteger)colorAttachmentIndex NS_AVAILABLE(10_12, 10_0);

/*!
 @method setDepthStoreAction:
 @brief If the the store action for the depth attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setDepthStoreAction: must be used to finalize the store action before endEncoding is called.
*/
- (void)setDepthStoreAction:(MTLStoreAction)storeAction NS_AVAILABLE(10_12, 10_0);

/*!
 @method setStencilStoreAction:
 @brief If the the store action for the stencil attachment was set to MTLStoreActionUnknown when the render command encoder was created,
 setStencilStoreAction: must be used to finalize the store action before endEncoding is called.
*/
- (void)setStencilStoreAction:(MTLStoreAction)storeAction NS_AVAILABLE(10_12, 10_0);

@end
NS_ASSUME_NONNULL_END
