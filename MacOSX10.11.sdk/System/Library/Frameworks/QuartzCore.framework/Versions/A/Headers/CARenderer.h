/* CoreAnimation - CARenderer.h

   Copyright (c) 2007-2015, Apple Inc.
   All rights reserved. */

/* This class lets an application manually drive the rendering of a
 * layer tree into an OpenGL rendering context. This is _not_ the
 * best solution for real-time output, use an NSView to host a layer
 * tree for that.
 *
 * The contract between CARenderer and the provided OpenGL context is
 * as follows:
 *
 * 1. the context should have an orthographic projection matrix and an
 *    identity model-view matrix, such that vertex position (0,0) is in
 *    the bottom left corner. (That is, window coordinates must match
 *    vertex coordinates.)
 *
 *    Sample code to initialize the OpenGL context for a window of width
 *    W and height H could be:
 *
 *      glViewport (0, 0, W, H);
 *      glMatrixMode (GL_PROJECTION);
 *      glLoadIdentity ();
 *      glOrtho (0, W, 0, H, -1, 1);
 *
 * 2. all OpenGL state apart from the viewport and projection matrices
 *    must have their default values when -render is called. On return
 *    from the -render method, the default values will be preserved.
 */

#import <QuartzCore/CABase.h>
#import <CoreVideo/CVBase.h>
#import <Foundation/NSObject.h>

@class NSDictionary, CALayer;

NS_ASSUME_NONNULL_BEGIN

@interface CARenderer : NSObject
{
@private
  struct CARendererPriv *_priv;
}

/* Create a new renderer object. Its render target is the specified
 * Core OpenGL context. 'dict' is an optional dictionary of parameters.  */

+ (CARenderer *)rendererWithCGLContext:(void *)ctx
    options:(nullable NSDictionary *)dict;

/* The root layer associated with the renderer. */

@property(nullable, strong) CALayer *layer;

/* The bounds rect of the render target. */

@property CGRect bounds;

/* Begin rendering a frame at time 't'. If 'ts' is non-null it defines
 * the host time and update frequency of the target device. */

- (void)beginFrameAtTime:(CFTimeInterval)t timeStamp:(nullable CVTimeStamp *)ts;

/* Returns the bounds of the update region - the area that contains all
 * pixels that will be rendered by the current frame. Initially this
 * will include all differences between the current frame and the
 * previously rendered frame. */

- (CGRect)updateBounds;

/* Add rectangle 'r' to the update region of the current frame. */

- (void)addUpdateRect:(CGRect)r;

/* Render the update region of the current frame to the target context. */

- (void)render;

/* Returns the time at which the next update should happen. If infinite
 * no update needs to be scheduled yet. If the current frame time, a
 * continuous animation is running and an update should be scheduled
 * after a "natural" delay. */

- (CFTimeInterval)nextFrameTime;

/* Release any data associated with the current frame. */

- (void)endFrame;

@end

NS_ASSUME_NONNULL_END
