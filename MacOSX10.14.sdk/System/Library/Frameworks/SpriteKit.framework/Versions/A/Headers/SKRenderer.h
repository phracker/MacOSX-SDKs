//
// SKRenderer.h
// SpriteKit
//
// Copyright (c) 2016 Apple Inc. All rights reserved
//

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKScene.h>

/* SKRenderer is not available for WatchKit apps and the iOS simulator */
#if SKVIEW_AVAILABLE && !TARGET_OS_SIMULATOR

#import <Metal/Metal.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A renderer for displaying a SpriteKit scene in an existing Metal workflow.
 */
NS_AVAILABLE(10_13, 11_0)
SK_EXPORT @interface SKRenderer : NSObject

/**
 Creates a renderer with the specified Metal device.
 
 @param device A Metal device.
 @return A new renderer object.
 */
+ (SKRenderer *)rendererWithDevice:(id<MTLDevice>)device;

/**
 Render the scene content in the specified Metal command buffer.
 
 @param viewport The pixel dimensions in which to render.
 @param commandBuffer The Metal command buffer in which SpriteKit should schedule rendering commands.
 @param renderPassDescriptor The Metal render pass descriptor describing the rendering target.
 */
- (void)renderWithViewport:(CGRect)viewport
             commandBuffer:(id <MTLCommandBuffer>)commandBuffer
      renderPassDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor;

/**
 Render the scene content using a specific Metal command encoder.
 
 @param viewport The pixel dimensions in which to render.
 @param renderCommandEncoder The Metal render command encoder that SpriteKit will use to encode rendering commands. This method will not call endEncoding.
 @param renderPassDescriptor The Metal render pass descriptor describing the rendering target.
 @param commandQueue The Metal command queue.
 */
- (void)renderWithViewport:(CGRect)viewport
      renderCommandEncoder:(id <MTLRenderCommandEncoder>)renderCommandEncoder
      renderPassDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor
              commandQueue:(id <MTLCommandQueue>)commandQueue;

/**
 Update the scene at the specified system time.
 
 @param currentTime The timestamp in seconds.
 */
- (void)updateAtTime:(NSTimeInterval)currentTime;

/**
 The currently presented scene, otherwise nil. If in a transition, the 'incoming' scene is returned.
 */
@property (nonatomic, nullable) SKScene *scene;

/**
 Ignores sibling and traversal order to sort the rendered contents of a scene into the most efficient batching possible.
 This will require zPosition to be used in the scenes to properly guarantee elements are in front or behind each other.

 This defaults to NO, meaning that sibling order overrides efficiency heuristics in the rendering of the scenes in the view.

 Setting this to YES for a complex scene may substantially increase performance, but care must be taken as only zPosition
 determines render order before the efficiency heuristics are used.
 */
@property (nonatomic) BOOL ignoresSiblingOrder;

/**
 A boolean that indicated whether non-visible nodes should be automatically culled when rendering.
 */
@property (nonatomic) BOOL shouldCullNonVisibleNodes;

/**
 Toggles display of performance stats when rendering. All default to false.
 */
@property (nonatomic) BOOL showsDrawCount;
@property (nonatomic) BOOL showsNodeCount;
@property (nonatomic) BOOL showsQuadCount;
@property (nonatomic) BOOL showsPhysics;
@property (nonatomic) BOOL showsFields;

@end

NS_ASSUME_NONNULL_END

#endif

