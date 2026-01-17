//
//  MTLRenderPass.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>




#import <Metal/MTLTypes.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;

typedef NS_ENUM(NSUInteger, MTLLoadAction) {
    MTLLoadActionDontCare = 0,
    MTLLoadActionLoad = 1,
    MTLLoadActionClear = 2,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_ENUM(NSUInteger, MTLStoreAction) {
    MTLStoreActionDontCare = 0,
    MTLStoreActionStore = 1,
    MTLStoreActionMultisampleResolve = 2,
    MTLStoreActionStoreAndMultisampleResolve API_AVAILABLE(macos(10.12), ios(10.0)) = 3,
    MTLStoreActionUnknown API_AVAILABLE(macos(10.12), ios(10.0)) = 4,
    MTLStoreActionCustomSampleDepthStore API_AVAILABLE(macos(10.13), ios(11.0)) = 5,
} API_AVAILABLE(macos(10.11), ios(8.0));

typedef NS_OPTIONS(NSUInteger, MTLStoreActionOptions) {
    MTLStoreActionOptionNone                  = 0,
    MTLStoreActionOptionCustomSamplePositions = 1 << 0,
} API_AVAILABLE(macos(10.13), ios(11.0));

typedef struct
{
    double red;
    double green;
    double blue;
    double alpha;
} MTLClearColor;

MTL_INLINE MTLClearColor MTLClearColorMake(double red, double green, double blue, double alpha);

@protocol MTLTexture;
@protocol MTLBuffer;

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
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

/*!
 @property storeActionOptions
 @abstract Optional configuration for the store action performed with this attachment at the end of a render pass.  Default is
 MTLStoreActionOptionNone.
 */
@property (nonatomic) MTLStoreActionOptions storeActionOptions API_AVAILABLE(macos(10.13), ios(11.0));

@end

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
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
} API_AVAILABLE(macos(10.14), ios(9.0));

MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
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
@property (nonatomic) MTLMultisampleDepthResolveFilter depthResolveFilter API_AVAILABLE(macos(10.14), ios(9.0));

@end



/*!
 @enum MTLMultisampleStencilResolveFilter
 @abstract Controls the MSAA stencil resolve operation.
 */
typedef NS_ENUM(NSUInteger, MTLMultisampleStencilResolveFilter)
{
    /*!
     @constant MTLMultisampleStencilResolveFilterSample0
     @abstract The stencil sample corresponding to sample 0. This is the default behavior.
     */
    MTLMultisampleStencilResolveFilterSample0               = 0,

    /*!
     @constant MTLMultisampleStencilResolveFilterDepthResolvedSample
     @abstract The stencil sample corresponding to whichever depth sample is selected by the depth resolve filter. If depth resolve is not enabled, the stencil sample is chosen based on what a depth resolve filter would have selected.
     */
    MTLMultisampleStencilResolveFilterDepthResolvedSample   = 1,
} API_AVAILABLE(macos(10.14), ios(12.0));



MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
@interface MTLRenderPassStencilAttachmentDescriptor : MTLRenderPassAttachmentDescriptor

/*!
 @property clearStencil
 @abstract The clear stencil value to be used if the loadAction property is MTLLoadActionClear
 */
@property (nonatomic) uint32_t clearStencil;

/*!
 @property stencilResolveFilter
 @abstract The filter to be used for stencil multisample resolve. Defaults to MTLMultisampleStencilResolveFilterSample0.
 */
@property (nonatomic) MTLMultisampleStencilResolveFilter stencilResolveFilter API_AVAILABLE(macos(10.14), ios(12.0));

@end



MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
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
MTL_EXPORT API_AVAILABLE(macos(10.11), ios(8.0))
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
@property (nonatomic) NSUInteger renderTargetArrayLength API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios);





/*!
 @method setSamplePositions:count:
 @abstract Configure the custom sample positions, to be used in MSAA rendering (i.e. when sample count > 1).
 @param positions The source array for custom sample position data.
 @param count Specifies the length of the positions array, and must be a valid sample count or 0 (to disable custom sample positions).
 */
- (void)setSamplePositions:(const MTLSamplePosition * _Nullable)positions count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(11.0));

/*!
 @method getSamplePositions:count:
 @abstract Retrieve the previously configured custom sample positions. The positions input array will only be modified when count specifies a length sufficient for the number of previously configured positions.
 @param positions The destination array for custom sample position data.
 @param count Specifies the length of the positions array, which must be large enough to hold all configured sample positions.
 @return The number of previously configured custom sample positions.
 */
- (NSUInteger)getSamplePositions:(MTLSamplePosition * _Nullable)positions count:(NSUInteger)count API_AVAILABLE(macos(10.13), ios(11.0));


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
