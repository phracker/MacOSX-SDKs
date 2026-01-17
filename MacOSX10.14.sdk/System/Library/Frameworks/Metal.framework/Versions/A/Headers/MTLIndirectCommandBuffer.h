//
//  MTLIndirectCommandBuffer.h
//  Metal
//
//  Copyright © 2017 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLIndirectCommandEncoder.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 @abstract
 A bitfield of commands that may be performed indirectly.
 */
typedef NS_OPTIONS(NSUInteger, MTLIndirectCommandType) {
    MTLIndirectCommandTypeDraw                = (1 << 0),
    MTLIndirectCommandTypeDrawIndexed         = (1 << 1),
    MTLIndirectCommandTypeDrawPatches         = (1 << 2),
    MTLIndirectCommandTypeDrawIndexedPatches  = (1 << 3) ,
} API_AVAILABLE(macos(10.14), ios(12.0));



/*!
 @abstract
 Describes the limits and features that can be used in an indirect command
 */
MTL_EXPORT API_AVAILABLE(macos(10.14), ios(12.0))
@interface MTLIndirectCommandBufferDescriptor : NSObject

/*!
 @abstract
 A bitfield of the command types that be encoded.
 @discussion
 MTLCommandTypeDispatch cannot be mixed with any other command type.
 */
@property (readwrite, nonatomic) MTLIndirectCommandType commandTypes;

/*!
 @abstract
 Whether the render or compute pipeline are inherited from the encoder
 */
@property (readwrite, nonatomic) BOOL inheritPipelineState API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios);

/*!
 @abstract
 Whether the render or compute pipeline can set arguments.
 */
@property (readwrite, nonatomic) BOOL inheritBuffers;

/*!
 @abstract
 The maximum bind index of vertex argument buffers that can be set per command.
 */
@property (readwrite, nonatomic) NSUInteger maxVertexBufferBindCount;

/*!
 @absract
 The maximum bind index of fragment argument buffers that can be set per command.
 */
@property (readwrite, nonatomic) NSUInteger maxFragmentBufferBindCount;



@end


API_AVAILABLE(macos(10.14), ios(12.0))
@protocol MTLIndirectCommandBuffer <MTLResource>

@property (readonly) NSUInteger size;

-(void)resetWithRange:(NSRange)range;

- (id <MTLIndirectRenderCommand>)indirectRenderCommandAtIndex:(NSUInteger)commandIndex;

@end

NS_ASSUME_NONNULL_END
