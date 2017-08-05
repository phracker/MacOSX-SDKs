//
//  MTLRenderCommandEncoder.h
//  Metal
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Metal/MTLDefines.h>
#import <Metal/MTLCommandEncoder.h>
#import <Metal/MTLCommandBuffer.h>
#import <Metal/MTLRenderPass.h>
#import <Metal/MTLFence.h>
#import <Metal/MTLStageInputOutputDescriptor.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MTLDevice;
@protocol MTLFunction;
@protocol MTLBuffer;
@protocol MTLSamplerState;

@protocol MTLDepthStencilState;
@protocol MTLTexture;
@protocol MTLRenderPipelineState;

typedef NS_ENUM(NSUInteger, MTLPrimitiveType) {
    MTLPrimitiveTypePoint = 0,
    MTLPrimitiveTypeLine = 1,
    MTLPrimitiveTypeLineStrip = 2,
    MTLPrimitiveTypeTriangle = 3,
    MTLPrimitiveTypeTriangleStrip = 4,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLVisibilityResultMode) {
    MTLVisibilityResultModeDisabled = 0,
    MTLVisibilityResultModeBoolean = 1,
    MTLVisibilityResultModeCounting NS_ENUM_AVAILABLE(10_11, 9_0) = 2,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef struct {
    NSUInteger x, y, width, height;
} MTLScissorRect;

typedef struct {
    double originX, originY, width, height, znear, zfar;
} MTLViewport;

typedef NS_ENUM(NSUInteger, MTLCullMode) {
    MTLCullModeNone = 0,
    MTLCullModeFront = 1,
    MTLCullModeBack = 2,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLWinding) {
    MTLWindingClockwise = 0,
    MTLWindingCounterClockwise = 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef NS_ENUM(NSUInteger, MTLDepthClipMode) {
    MTLDepthClipModeClip = 0,
    MTLDepthClipModeClamp = 1,
} NS_ENUM_AVAILABLE(10_11, 9_0);

typedef NS_ENUM(NSUInteger, MTLTriangleFillMode) {
    MTLTriangleFillModeFill = 0,
    MTLTriangleFillModeLines = 1,
} NS_ENUM_AVAILABLE(10_11, 8_0);

typedef struct {
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t vertexStart;
    uint32_t baseInstance;
} MTLDrawPrimitivesIndirectArguments;

typedef struct {
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t indexStart;
    int32_t  baseVertex;
    uint32_t baseInstance;
} MTLDrawIndexedPrimitivesIndirectArguments;

typedef struct {
    uint32_t patchCount;
    uint32_t instanceCount;
    uint32_t patchStart;
    uint32_t baseInstance;
} MTLDrawPatchIndirectArguments;

typedef struct {
    /* NOTE: edgeTessellationFactor and insideTessellationFactor are interpreted as half (16-bit floats) */
    uint16_t edgeTessellationFactor[4];
    uint16_t insideTessellationFactor[2];
} MTLQuadTessellationFactorsHalf;

typedef struct {
    /* NOTE: edgeTessellationFactor and insideTessellationFactor are interpreted as half (16-bit floats) */
    uint16_t edgeTessellationFactor[3];
    uint16_t insideTessellationFactor;
} MTLTriangleTessellationFactorsHalf;

/*!
 @abstract Points at which a fence may be waited on or signaled.
 @constant MTLRenderStageVertex   All vertex work prior to rasterization has completed.
 @constant MTLRenderStageFragment All rendering work has completed.
 */
typedef NS_OPTIONS(NSUInteger, MTLRenderStages)
{
    MTLRenderStageVertex   = (1UL << 0),
    MTLRenderStageFragment = (1UL << 1),
} NS_ENUM_AVAILABLE_IOS(10_0);

/*!
 @protocol MTLRenderCommandEncoder
 @discussion MTLRenderCommandEncoder is a container for graphics rendering state and the code to translate the state into a command format that the device can execute. 
 */
NS_AVAILABLE(10_11, 8_0)
@protocol MTLRenderCommandEncoder <MTLCommandEncoder>

/*!
 @method setRenderPipelineState
 @brief Sets the current render pipeline state object.
 */
- (void)setRenderPipelineState:(id <MTLRenderPipelineState>)pipelineState;

/* Vertex Resources */

/*!
 @method setVertexBytes:length:atIndex:
 @brief Set the data (by copy) for a given vertex buffer binding point.  This will remove any existing MTLBuffer from the binding point.
 */
- (void)setVertexBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setVertexBuffer:offset:atIndex:
 @brief Set a global buffer for all vertex shaders at the given bind point index.
 */
- (void)setVertexBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 @method setVertexBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all vertex shaders at the given bind point index.
 */
- (void)setVertexBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setVertexBuffers:offsets:withRange:
 @brief Set an array of global buffers for all vertex shaders with the given bind point range.
 */
- (void)setVertexBuffers:(const id <MTLBuffer> __nullable [])buffers offsets:(const NSUInteger [])offsets withRange:(NSRange)range;

/*!
 @method setVertexTexture:atIndex:
 @brief Set a global texture for all vertex shaders at the given bind point index.
 */
- (void)setVertexTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 @method setVertexTextures:withRange:
 @brief Set an array of global textures for all vertex shaders with the given bind point range.
 */
- (void)setVertexTextures:(const id <MTLTexture> __nullable [__nullable])textures withRange:(NSRange)range;

/*!
 @method setVertexSamplerState:atIndex:
 @brief Set a global sampler for all vertex shaders at the given bind point index.
 */
- (void)setVertexSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 @method setVertexSamplerStates:withRange:
 @brief Set an array of global samplers for all vertex shaders with the given bind point range.
 */
- (void)setVertexSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers withRange:(NSRange)range;

/*!
 @method setVertexSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all vertex shaders at the given bind point index.
 */
- (void)setVertexSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index;

/*!
 @method setVertexSamplerStates:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all vertex shaders with the given bind point range.
 */
- (void)setVertexSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers lodMinClamps:(const float [__nullable])lodMinClamps lodMaxClamps:(const float [__nullable])lodMaxClamps withRange:(NSRange)range;

/*!
 @method setViewport:
 @brief Set the viewport, which is used to transform vertexes from normalized device coordinates to window coordinates.  Fragments that lie outside of the viewport are clipped, and optionally clamped for fragments outside of znear/zfar.
 */
- (void)setViewport:(MTLViewport)viewport;

/*!
 @method setFrontFacingWinding:
 @brief The winding order of front-facing primitives.
 */
- (void)setFrontFacingWinding:(MTLWinding)frontFacingWinding;

/*!
 @method setCullMode:
 @brief Controls if primitives are culled when front facing, back facing, or not culled at all.
 */
- (void)setCullMode:(MTLCullMode)cullMode;

/*!
@method setDepthClipMode:
@brief Controls what is done with fragments outside of the near or far planes.
*/
- (void)setDepthClipMode:(MTLDepthClipMode)depthClipMode NS_AVAILABLE(10_11, NA);

/*!
 @method setDepthBias:slopeScale:clamp:
 @brief Depth Bias.
 */
- (void)setDepthBias:(float)depthBias slopeScale:(float)slopeScale clamp:(float)clamp;

/*!
 @method setScissorRect:
 @brief Specifies a rectangle for a fragment scissor test.  All fragments outside of this rectangle are discarded.
 */
- (void)setScissorRect:(MTLScissorRect)rect;

/*!
 @method setTriangleFillMode:
 @brief Set how to rasterize triangle and triangle strip primitives.
 */
- (void)setTriangleFillMode:(MTLTriangleFillMode)fillMode;

/* Fragment Resources */

/*!
 @method setFragmentBytes:length:atIndex:
 @brief Set the data (by copy) for a given fragment buffer binding point.  This will remove any existing MTLBuffer from the binding point.
 */
- (void)setFragmentBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setFragmentBuffer:offset:atIndex:
 @brief Set a global buffer for all fragment shaders at the given bind point index.
 */
- (void)setFragmentBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset atIndex:(NSUInteger)index;

/*!
 @method setFragmentBufferOffset:atIndex:
 @brief Set the offset within the current global buffer for all fragment shaders at the given bind point index.
 */
- (void)setFragmentBufferOffset:(NSUInteger)offset atIndex:(NSUInteger)index NS_AVAILABLE(10_11, 8_3);

/*!
 @method setFragmentBuffers:offsets:withRange:
 @brief Set an array of global buffers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentBuffers:(const id <MTLBuffer> __nullable [])buffers offsets:(const NSUInteger [])offset withRange:(NSRange)range;

/*!
 @method setFragmentTexture:atIndex:
 @brief Set a global texture for all fragment shaders at the given bind point index.
 */
- (void)setFragmentTexture:(nullable id <MTLTexture>)texture atIndex:(NSUInteger)index;

/*!
 @method setFragmentTextures:withRange:
 @brief Set an array of global textures for all fragment shaders with the given bind point range.
 */
- (void)setFragmentTextures:(const id <MTLTexture> __nullable [__nullable])textures withRange:(NSRange)range;

/*!
 @method setFragmentSamplerState:atIndex:
 @brief Set a global sampler for all fragment shaders at the given bind point index.
 */
- (void)setFragmentSamplerState:(nullable id <MTLSamplerState>)sampler atIndex:(NSUInteger)index;

/*!
 @method setFragmentSamplerStates:withRange:
 @brief Set an array of global samplers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers withRange:(NSRange)range;

/*!
 @method setFragmentSamplerState:lodMinClamp:lodMaxClamp:atIndex:
 @brief Set a global sampler for all fragment shaders at the given bind point index.
 */
- (void)setFragmentSamplerState:(nullable id <MTLSamplerState>)sampler lodMinClamp:(float)lodMinClamp lodMaxClamp:(float)lodMaxClamp atIndex:(NSUInteger)index;

/*!
 @method setFragmentSamplerStates:lodMinClamps:lodMaxClamps:withRange:
 @brief Set an array of global samplers for all fragment shaders with the given bind point range.
 */
- (void)setFragmentSamplerStates:(const id <MTLSamplerState> __nullable [__nullable])samplers lodMinClamps:(const float [__nullable])lodMinClamps lodMaxClamps:(const float [__nullable])lodMaxClamps withRange:(NSRange)range;

/* Constant Blend Color */
/*!
 @method setBlendColorRed:green:blue:alpha:
 @brief Set the constant blend color used across all blending on all render targets
 */
- (void)setBlendColorRed:(float)red green:(float)green blue:(float)blue alpha:(float)alpha;

/*! 
 @method setDepthStencilState:
 @brief Set the DepthStencil state object.
 */
- (void)setDepthStencilState:(nullable id <MTLDepthStencilState>)depthStencilState;

/*! 
 @method setStencilReferenceValue:
 @brief Set the stencil reference value for both the back and front stencil buffers.
 */
- (void)setStencilReferenceValue:(uint32_t)referenceValue;

/*!
 @method setStencilFrontReferenceValue:backReferenceValue:
 @brief Set the stencil reference value for the back and front stencil buffers independently.
 */
- (void)setStencilFrontReferenceValue:(uint32_t)frontReferenceValue backReferenceValue:(uint32_t)backReferenceValue NS_AVAILABLE(10_11, 9_0);

/*!
 @method setVisibilityResultMode:offset:
 @abstract Monitor if samples pass the depth and stencil tests.
 @param mode Controls if the counter is disabled or moniters passing samples.
 @param offset The offset relative to the occlusion query buffer provided when the command encoder was created.  offset must be a multiple of 8.
 */
- (void)setVisibilityResultMode:(MTLVisibilityResultMode)mode offset:(NSUInteger)offset;

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

/* Drawing */

/*!
 @method drawPrimitives:vertexStart:vertexCount:instanceCount:
 @brief Draw primitives without an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param vertexStart For each instance, the first index to draw
 @param vertexCount For each instance, the number of indexes to draw
 @param instanceCount The number of instances drawn.
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType vertexStart:(NSUInteger)vertexStart vertexCount:(NSUInteger)vertexCount instanceCount:(NSUInteger)instanceCount;

/*!
 @method drawPrimitives:vertexStart:vertexCount:
 @brief Draw primitives without an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param vertexStart For each instance, the first index to draw
 @param vertexCount For each instance, the number of indexes to draw
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType vertexStart:(NSUInteger)vertexStart vertexCount:(NSUInteger)vertexCount;

/*!
 @method drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:
 @brief Draw primitives with an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexCount The number of indexes to read from the index buffer for each instance.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 @param instanceCount The number of instances drawn.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset instanceCount:(NSUInteger)instanceCount;

/*!
 @method drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:
 @brief Draw primitives with an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexCount The number of indexes to read from the index buffer for each instance.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset;

/*!
 @method drawPrimitives:vertexStart:vertexCount:instanceCount:baseInstance:
 @brief Draw primitives without an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param vertexStart For each instance, the first index to draw
 @param vertexCount For each instance, the number of indexes to draw
 @param instanceCount The number of instances drawn.
 @param baseInstance Offset for instance_id.
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType vertexStart:(NSUInteger)vertexStart vertexCount:(NSUInteger)vertexCount instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance NS_AVAILABLE(10_11, 9_0);

/*!
 @method drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:baseVertex:baseInstance:
 @brief Draw primitives with an index list.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexCount The number of indexes to read from the index buffer for each instance.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 @param instanceCount The number of instances drawn.
 @param baseVertex Offset for vertex_id. NOTE: this can be negative
 @param baseInstance Offset for instance_id.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexCount:(NSUInteger)indexCount indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset instanceCount:(NSUInteger)instanceCount baseVertex:(NSInteger)baseVertex baseInstance:(NSUInteger)baseInstance NS_AVAILABLE(10_11, 9_0);

/*!
 @method drawPrimitives:indirectBuffer:indirectBufferOffset:
 @brief Draw primitives without an index list using an indirect buffer see MTLDrawPrimitivesIndirectArguments.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indirectBuffer A buffer object that the device will read drawPrimitives arguments from, see MTLDrawPrimitivesIndirectArguments.
 @param indirectBufferOffset Byte offset within @a indirectBuffer to start reading indexes from.  @a indirectBufferOffset must be a multiple of 4.
 */
- (void)drawPrimitives:(MTLPrimitiveType)primitiveType indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset NS_AVAILABLE(10_11, 9_0);

/*!
 @method drawIndexedPrimitives:indexType:indexBuffer:indexBufferOffset:indirectBuffer:indirectBufferOffset:
 @brief Draw primitives with an index list using an indirect buffer see MTLDrawIndexedPrimitivesIndirectArguments.
 @param primitiveType The type of primitives that elements are assembled into.
 @param indexType The type if indexes, either 16 bit integer or 32 bit integer.
 @param indexBuffer A buffer object that the device will read indexes from.
 @param indexBufferOffset Byte offset within @a indexBuffer to start reading indexes from.  @a indexBufferOffset must be a multiple of the index size.
 @param indirectBuffer A buffer object that the device will read drawIndexedPrimitives arguments from, see MTLDrawIndexedPrimitivesIndirectArguments.
 @param indirectBufferOffset Byte offset within @a indirectBuffer to start reading indexes from.  @a indirectBufferOffset must be a multiple of 4.
 */
- (void)drawIndexedPrimitives:(MTLPrimitiveType)primitiveType indexType:(MTLIndexType)indexType indexBuffer:(id <MTLBuffer>)indexBuffer indexBufferOffset:(NSUInteger)indexBufferOffset indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset NS_AVAILABLE(10_11, 9_0);

/*!
 @method textureBarrier:
 @brief Ensure that following fragment shaders can read textures written by previous draw calls (in particular the framebuffer)
 */
- (void)textureBarrier NS_AVAILABLE_MAC(10_11);

/*!
 @method updateFence:afterStages:
 @abstract Update the event to capture all GPU work so far enqueued by this encoder for the given stages.
 @discussion Unlike <st>updateFence:</st>, this method will update the event when the given stage(s) complete, allowing for commands to overlap in execution.
 On iOS, render command encoder fence updates are always delayed until the end of the encoder.
 */
- (void)updateFence:(id <MTLFence>)fence afterStages:(MTLRenderStages)stages NS_AVAILABLE_IOS(10_0);

/*!
 @method waitForFence:beforeStages:
 @abstract Prevent further GPU work until the event is reached for the given stages.
 @discussion Unlike <st>waitForFence:</st>, this method will only block commands assoicated with the given stage(s), allowing for commands to overlap in execution.
 On iOS, render command encoder fence waits always occur the beginning of the encoder.
 */
- (void)waitForFence:(id <MTLFence>)fence beforeStages:(MTLRenderStages)stages NS_AVAILABLE_IOS(10_0);

-(void)setTessellationFactorBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset instanceStride:(NSUInteger)instanceStride NS_AVAILABLE(10_12, 10_0);

-(void)setTessellationFactorScale:(float)scale NS_AVAILABLE(10_12, 10_0);

-(void)drawPatches:(NSUInteger)numberOfPatchControlPoints patchStart:(NSUInteger)patchStart patchCount:(NSUInteger)patchCount patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance NS_AVAILABLE(10_12, 10_0);

-(void)drawPatches:(NSUInteger)numberOfPatchControlPoints patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset NS_AVAILABLE(10_12, NA);

-(void)drawIndexedPatches:(NSUInteger)numberOfPatchControlPoints patchStart:(NSUInteger)patchStart patchCount:(NSUInteger)patchCount patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset controlPointIndexBuffer:(id <MTLBuffer>)controlPointIndexBuffer controlPointIndexBufferOffset:(NSUInteger)controlPointIndexBufferOffset instanceCount:(NSUInteger)instanceCount baseInstance:(NSUInteger)baseInstance NS_AVAILABLE(10_12, 10_0);

-(void)drawIndexedPatches:(NSUInteger)numberOfPatchControlPoints patchIndexBuffer:(nullable id <MTLBuffer>)patchIndexBuffer patchIndexBufferOffset:(NSUInteger)patchIndexBufferOffset controlPointIndexBuffer:(id <MTLBuffer>)controlPointIndexBuffer controlPointIndexBufferOffset:(NSUInteger)controlPointIndexBufferOffset indirectBuffer:(id <MTLBuffer>)indirectBuffer indirectBufferOffset:(NSUInteger)indirectBufferOffset NS_AVAILABLE(10_12, NA);

@end
NS_ASSUME_NONNULL_END
