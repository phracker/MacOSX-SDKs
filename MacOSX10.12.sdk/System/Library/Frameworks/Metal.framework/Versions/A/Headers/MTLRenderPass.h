//
//  MTLRenderPass.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;

typedef NS_ENUM(NSUInteger, MTLLoadAction) {
    MTLLoadActionDontCare = 0,
    MTLLoadActionLoad = 1,
    MTLLoadActionClear = 2,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLStoreAction) {
    MTLStoreActionDontCare = 0,
    MTLStoreActionStore = 1,
    MTLStoreActionMultisampleResolve = 2,
    MTLStoreActionStoreAndMultisampleResolve NS_ENUM_AVAILABLE(10_12,10_0) = 3,
    MTLStoreActionUnknown NS_ENUM_AVAILABLE(10_12,10_0) = 4,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef struct
{
    double red;
    double green;
    double blue;
    double alpha;
} MTLClearColor;

// Should we provide a set of APIs similar to the old methods below?
MTL_INLINE MTLClearColor MTLClearColorMake(double red, double green, double blue, double alpha);

@protocol MTLTexture;
@protocol MTLBuffer;

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPassAttachmentDescriptor : NSObject <NSCopying>

/*!
 @property texture
 @abstract The MTLTexture object for this attachment.
 */
@property (nullable, nonatomic, strong) id <MTLTexture> texture;

/*!
 @property level
 @abstract The mipmap level of the texture to be used for rendering.  Default is zero.
 */
@property (nonatomic) NSUInteger level;

/*!
 @property slice
 @abstract The slice of the texture to be used for rendering.  Default is zero.
 */
@property (nonatomic) NSUInteger slice;

/*!
 @property depthPlane
 @abstract The depth plane of the texture to be used for rendering.  Default is zero.
 */
@property (nonatomic) NSUInteger depthPlane;

/*!
 @property resolveTexture
 @abstract The texture used for multisample resolve operations.  Only used (and required)
 if the store action is set to MTLStoreActionMultisampleResolve.
 */
@property (nullable, nonatomic, strong) id <MTLTexture> resolveTexture;

/*!
 @property resolveLevel
 @abstract The mipmap level of the resolve texture to be used for multisample resolve.  Defaults to zero.
 */
@property (nonatomic) NSUInteger resolveLevel;

/*!
 @property resolveLevel
 @abstract The texture slice of the resolve texture to be used for multisample resolve.  Defaults to zero.
 */
@property (nonatomic) NSUInteger resolveSlice;

/*!
 @property resolveDepthPlane
 @abstract The texture depth plane of the resolve texture to be used for multisample resolve.  Defaults to zero.
 */
@property (nonatomic) NSUInteger resolveDepthPlane;

/*!
 @property loadAction
 @abstract The action to be performed with this attachment at the beginning of a render pass.  Default is
 MTLLoadActionDontCare unless specified by a creation or init method.
 */
@property (nonatomic) MTLLoadAction loadAction;

/*!
 @property storeAction
 @abstract The action to be performed with this attachment at the end of a render pass.  Default is
 MTLStoreActionDontCare unless specified by a creation or init method.
 */
@property (nonatomic) MTLStoreAction storeAction;

@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPassColorAttachmentDescriptor : MTLRenderPassAttachmentDescriptor

/*!
 @property clearColor
 @abstract The clear color to be used if the loadAction property is MTLLoadActionClear
 */
@property (nonatomic) MTLClearColor clearColor;

@end

/*!
 @enum MTLMultisampleDepthResolveFilter
 @abstract Controls the MSAA depth resolve operation. Supported on iOS GPU Family 3 and later.
 */
typedef NS_ENUM(NSUInteger, MTLMultisampleDepthResolveFilter)
{
    MTLMultisampleDepthResolveFilterSample0 = 0,
    MTLMultisampleDepthResolveFilterMin = 1,
    MTLMultisampleDepthResolveFilterMax = 2,
} NS_ENUM_AVAILABLE_IOS(9_0);

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPassDepthAttachmentDescriptor : MTLRenderPassAttachmentDescriptor

/*!
 @property clearDepth
 @abstract The clear depth value to be used if the loadAction property is MTLLoadActionClear
 */
@property (nonatomic) double clearDepth;

/*!
 @property resolveFilter
 @abstract The filter to be used for depth multisample resolve.  Defaults to MTLMultisampleDepthResolveFilterSample0.
 */
@property (nonatomic) MTLMultisampleDepthResolveFilter depthResolveFilter NS_AVAILABLE_IOS(9_0);

@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPassStencilAttachmentDescriptor : MTLRenderPassAttachmentDescriptor

/*!
 @property clearStencil
 @abstract The clear stencil value to be used if the loadAction property is MTLLoadActionClear
 */
@property (nonatomic) uint32_t clearStencil;

@end

NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPassColorAttachmentDescriptorArray : NSObject
/* Individual attachment state access */
- (MTLRenderPassColorAttachmentDescriptor *)objectAtIndexedSubscript:(NSUInteger)attachmentIndex;

/* This always uses 'copy' semantics.  It is safe to set the attachment state at any legal index to nil, which resets that attachment descriptor state to default vaules. */
- (void)setObject:(nullable MTLRenderPassColorAttachmentDescriptor *)attachment atIndexedSubscript:(NSUInteger)attachmentIndex;

@end

/*!
 @class MTLRenderPassDescriptor
 @abstract MTLRenderPassDescriptor represents a collection of attachments to be used to create a concrete render command encoder
 */
NS_CLASS_AVAILABLE(10_11, 8_0)
@interface MTLRenderPassDescriptor : NSObject <NSCopying>

/*!
 @method renderPassDescriptor
 @abstract Create an autoreleased default frame buffer descriptor
 */
+ (MTLRenderPassDescriptor *)renderPassDescriptor;

@property (readonly) MTLRenderPassColorAttachmentDescriptorArray *colorAttachments;

@property (copy, nonatomic, null_resettable) MTLRenderPassDepthAttachmentDescriptor *depthAttachment;

@property (copy, nonatomic, null_resettable) MTLRenderPassStencilAttachmentDescriptor *stencilAttachment;

/*!
 @property visibilityResultBuffer:
 @abstract Buffer into which samples passing the depth and stencil tests are counted.
 */
@property (nullable, nonatomic, strong) id <MTLBuffer> visibilityResultBuffer;

/*!
 @property renderTargetArrayLength:
 @abstract The number of active layers
 */
@property (nonatomic) NSUInteger renderTargetArrayLength NS_AVAILABLE_MAC(10_11);

@end

// Inline definitions
MTL_INLINE MTLClearColor MTLClearColorMake(double red, double green, double blue, double alpha)
{
    MTLClearColor result;
    result.red = red;
    result.green = green;
    result.blue = blue;
    result.alpha = alpha;
    return result;
}

NS_ASSUME_NONNULL_END
