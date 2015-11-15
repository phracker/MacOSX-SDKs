/*!
 @header MTKView.h
 @framework MetalKit
 @abstract MetalKit helper functionality for creating a view
 @discussion This view class provides functionality to setup metal drawable textures for common rendering scenarios
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <MetalKit/MTKDefines.h>

#import <AppKit/AppKit.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>

@protocol MTKViewDelegate;

/*!
 @class MTKView
 @abstract View for rendering metal content
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKView : NSView <NSCoding>

/*!
 @property delegate
 @abstract The delegate handling common view operations
 */
@property (nonatomic, weak, nullable) id <MTKViewDelegate> delegate;

/*!
 @property device
 @abstract The MTLDevice used to create metal objects
 @discussion On iOS this is set to the default device.  On OS X this must be explicitly set by the application.
  */
@property (nonatomic, nullable) id <MTLDevice> device;

/*!
 @property currentDrawable
 @abstract The drawable to be used for the current frame.
 @discussion currentDrawable is updated at the end -draw (i.e. after the delegate's drawInView method is called)
 */
@property (nonatomic, readonly, nullable) id <CAMetalDrawable> currentDrawable;

/*!
 @property framebufferOnly
 @abstract If the currentDrawable can be used for sampling or texture read operations
 @discussion This defaults to YES. This property controls whether or not the returned drawables' MTLTextures may only be used for framebuffer attachments (YES) or whether they may also be used for texture sampling and pixel read/write operations (NO). A value of YES allows the CAMetalLayer to allocate the MTLTexture objects in ways that are optimized for display purposes that makes them unsuitable for sampling. The recommended value for most applications is YES.
 */
@property (nonatomic) BOOL framebufferOnly;

/*!
 @property presentsWithTransaction
 @abstract If the layer should be presented synchronously
 @discussion Defaults to NO. When NO, changes to the layer's render buffer appear on-screen asynchronously to normal layer updates. When YES, changes to the MTL content are sent to the screen via the standard CATransaction mechanisms.
*/
@property (nonatomic) BOOL presentsWithTransaction;

/*!
 @property colorPixelFormat
 @abstract The pixelFormat for the drawable's texture
 */
@property (nonatomic) MTLPixelFormat colorPixelFormat;

/*!
 @property depthStencilPixelFormat
 @abstract The pixelFormat used to create depthStencilTexture
 */
@property (nonatomic) MTLPixelFormat depthStencilPixelFormat;

/*!
 @property sampleCount
 @abstract The sample count used to to create multisampleColorTexture
 @discussion This defaults to 1.  If sampleCount is greater than 1 a multisampled color texture will be created and the currentDrawable's texture will be set as the resolve texture in the currentRenderPassDescriptor and the store action will be set to MTLStoreActionMultisampleResolve
 */
@property (nonatomic) NSUInteger sampleCount;

/*!
 @property clearColor
 @abstract The clear color value used to generate the currentRenderPassDescriptor
 @discussion This defaults to (0.0, 0.0, 0.0, 1.0)
 */
@property (nonatomic) MTLClearColor clearColor;

/*!
 @property clearDepth
 @abstract The clear depth value used to generate the currentRenderPassDescriptor
 @discussion This defaults to 1.0
 */
@property (nonatomic) double clearDepth;

/*!
 @property clearStencil
 @abstract The clear stencil value used to generate currentRenderPassDescriptor
 @discussion This defaults to 0
 */
@property (nonatomic) uint32_t clearStencil;

/*!
 @property depthStencilTexture
 @abstract A packed depth and stencil texture to be attached to a MTLRenderPassDescriptor
 @discussion The view will generate the depth buffer using the specified depthPixelFormat.  This will be nil if depthStencilPixelFormat is MTLPixelFormatInvalid.
 */
@property (nonatomic, readonly, nullable) id <MTLTexture> depthStencilTexture;

/*!
 @property multisampleColorTexture
 @abstract A multisample color sample texture that will be resolved into the currentDrawable's texture
 @discussion The view will generate the samplerBuffer buffer using the specified colorPixelFormat.  This will be nil if sampleCount is less than or equal to 1.
 */
@property (nonatomic, readonly, nullable) id <MTLTexture> multisampleColorTexture;

/*!
 @method releaseDrawables
 @abstract Release the depthStencilTexture and multisampleColorTexture
 @discussion Can be called by the app to release the textures in order to conserve memory when it goes into the background
 */
- (void)releaseDrawables;

/*!
 @property currentRenderPassDescriptor
 @abstract A render pass descriptor generated from the  currentDrawable's texture and the view's depth, stencil, and sample buffers and clear values.
 @discussion This is a convience property.  The view does not use this descriptor and there is no requirement for an app to use this descriptor.
 */
@property (nonatomic, readonly, nullable) MTLRenderPassDescriptor *currentRenderPassDescriptor;

/*!
 @property preferredFramesPerSecond
 @abstract The rate you want the view to redraw its contents.
 @discussion When your application sets its preferred frame rate, the view chooses a frame rate as close to that as possible based on the capabilities of the screen the view is displayed on. The actual frame rate chosen is usually a factor of the maximum refresh rate of the screen to provide a consistent frame rate. For example, if the maximum refresh rate of the screen is 60 frames per second, that is also the highest frame rate the view sets as the actual frame rate. However, if you ask for a lower frame rate, it might choose 30, 20, 15 or some other factor to be the actual frame rate. Your application should choose a frame rate that it can consistently maintain. The default value is 30 frames per second.
 */
@property(nonatomic) NSInteger preferredFramesPerSecond;

/*!
 @property nominalFramesPerSecond
 @abstract The set number of achievable frames per second
 @discussion The nominal frames per second that was decided upon given the value for preferredFramesPerSecond and the screen on which the MTKView resides. The value chosen will be as close to preferredFramesPerSecond as possible, without exceeding the screen's refresh rate. This value does not account for dropped frames, so it is not a measurement of your statistical frames per second. It is the static value for which updates should take place.
 */
@property (nonatomic, readonly) NSInteger nominalFramesPerSecond;

/*!
  @property enableSetNeedsDisplay
  @abstract Controls whether the view responds to setNeedsDisplay.
  @discussion If true, then the view behaves similarily to a UIView.  When the view has been marked for display, the drawRect method will be called during the next drawing cycle. If false, the view's draw method will never be called during the next drawing cycle. It is expected that -draw will be  called directly in this case and not automatically at the frame interval indicated by nominalFramesPerSecond. This value is false by default.
 */
@property (nonatomic) BOOL enableSetNeedsDisplay;

/*!
 @property autoResizeDrawable
 @abstract Controls whether to resize the drawable as the view changes size.
 @discussion If true, the size of the currentDrawable's texture, depthStencilTexture, and multisampleColorTexture will automatically resize as the view resizes.  If false, these textures will take on the size of drawableSize and drawaableSize will not change.  This is true by default.
 */
@property (nonatomic) BOOL autoResizeDrawable;

/*!
 @property drawableSize
 @abstract The current size of drawable textures
 @discussion The size currentDrawable's texture, depthStencilTexture, and multisampleColorTexture.  If autoResizeDrawable is true this value will be updated as the view's size changes.  If autoResizeDrawable is falue, this can be set to fix the size of the drawable textures.
 */
@property (nonatomic) CGSize drawableSize;

/*!
 @property paused
 @abstract Controls whether the draw methods should countinue at preferredFramesPerSecond
 @discussion If true, the delegate will receive drawInview: messages or the subclass will receive drawRect: messages at nominalFramesPerSecond times per second.
 */
@property (nonatomic, getter=isPaused) BOOL paused;

/*!
 @method draw
 @abstract Render to the frame buffer
 @discussion Nominally called at nominalFramesPerSecond.  This calls the delegate drawInView method or (if MTKView is subclassed) the drawRect method.
 */
- (void)draw;

@end

/*!
 @class MTKViewDelegate
 @abstract Allows an object to render into the view at nominalFramesPerSecond and respond to events affecting rendering
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MTKViewDelegate <NSObject>

/*!
 @method view:willLayoutWithSize:
 @abstract Called whenever view changes size (or orientation)
 @discussion Delegate can recompute view and projection matricies or regenerate any buffers to be compatible with the new view size or resolution
 @param view MTKView which called this method
 @param size New drawable size
 */
- (void)view:(nonnull MTKView *)view willLayoutWithSize:(CGSize)size;

/*!
 @method drawInView:
 @abstract Called by view for delegate to render scene
 @discussion Nominally called by view after at nominalFramesPerSecond during -[MTKView display].
 */
- (void)drawInView:(nonnull MTKView *)view;

@end
