//
//  SCNRenderer.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MTLDevice;
@protocol MTLCommandQueue;
@protocol MTLRenderCommandEncoder;
@class MTLRenderPassDescriptor;

/*! @class SCNRenderer
	@abstract SCNRenderer lets you use the SceneKit renderer in an OpenGL context or Metal render pass descriptor of your own.
 */
NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNRenderer : NSObject <SCNSceneRenderer, SCNTechniqueSupport>

/*! 
 @method rendererWithContext:options:
 @abstract Creates a new renderer object.
 @param context The context to render into.
 @param options An optional dictionary for future extensions.
 */
+ (instancetype)rendererWithContext:(CGLContextObj)context options:(nullable NSDictionary *)options;

/*!
 @method rendererWithDevice:options:
 @abstract Creates a new renderer object that renders using Metal.
 @param device The metal device to use. Pass nil to let SceneKit choose a default device.
 @param options An optional dictionary for future extensions.
 */
+ (instancetype)rendererWithDevice:(nullable id <MTLDevice>)device options:(nullable NSDictionary *)options NS_AVAILABLE(10_11, 9_0);

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @method renderAtTime:
 @abstract renders the receiver's scene at the specified time (system time).
 @discussion This method only work if the receiver was allocated with an OpenGL context. Use renderAtTime:withEncoder:pass:commandQueue: to render with Metal.
 */
- (void)renderAtTime:(CFTimeInterval)time NS_AVAILABLE(10_10, 8_0);

/*!
 @method renderAtTime:viewport:commandBuffer:passDescriptor:
 @abstract renders the receiver's scene at the specified time (system time) viewport, metal command buffer and pass descriptor.
 @discussion Use this method to render using Metal.
 */
- (void)renderAtTime:(CFTimeInterval)time viewport:(CGRect)viewport commandBuffer:(id <MTLCommandBuffer>)commandBuffer passDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor NS_AVAILABLE(10_11, 9_0);

/*!
 @property nextFrameTime
 @abstract Returns the time at which the next update should happen. If infinite no update needs to be scheduled yet. If the current frame time, a continuous animation is running and an update should be scheduled after a "natural" delay.
 */
@property(nonatomic, readonly) CFTimeInterval nextFrameTime NS_AVAILABLE(10_10, 8_0);

/*!
 @method render
 @abstract renders the receiver's scene at the current system time.
 @discussion This method only work if the receiver was allocated with an OpenGL context and it is deprecated (use renderAtIme: instead). Use renderAtTime:withEncoder:pass:commandQueue: to render with Metal.
 */
- (void)render NS_DEPRECATED(10_8, 10_11, 8_0, 9_0);

@end

NS_ASSUME_NONNULL_END
