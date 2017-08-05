//
//  MTLCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;

/*!
 @protocol MTLCommandEncoder
 @abstract MTLCommandEncoder is the common interface for objects that write commands into MTLCommandBuffers.
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLCommandEncoder <NSObject>

/*!
 @property device
 @abstract The device this resource was created against.
 */
@property (readonly) id <MTLDevice> device;

/*!
 @property label
 @abstract A string to help identify this object.
 */
@property (nullable, copy, atomic) NSString *label;

/*!
 @method endEncoding
 @abstract Declare that all command generation from this encoder is complete, and detach from the MTLCommandBuffer.
 */
- (void)endEncoding;

/* Debug Support */

/*!
 @method insertDebugSignpost:
 @abstract Inserts a debug string into the command buffer.  This does not change any API behavior, but can be useful when debugging.
 */
- (void)insertDebugSignpost:(NSString *)string;

/*!
 @method pushDebugGroup:
 @abstract Push a new named string onto a stack of string labels.
 */
- (void)pushDebugGroup:(NSString *)string;

/*!
 @method popDebugGroup
 @abstract Pop the latest named string off of the stack.
*/
- (void)popDebugGroup;

@end
NS_ASSUME_NONNULL_END
