/*!
 @header MTKView.h
 @framework MetalKit
 @abstract MetalKit helper functionality for creating a view
 @discussion This view class provides functionality to setup metal drawable textures for common rendering scenarios
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */

#import <MetalKit/MTKDefines.h>

#import <UIKit/UIKit.h>

#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>

@protocol MTKViewDelegate;

/*!
 @class MTKView
 @abstract View for rendering metal content
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface MTKView : UIView <NSCoding,CALayerDelegate>

/*!
 @method initWithFrame:device
 @abstract Initalize the view with a frame and device
 @param frameRect The frame rectangle for the created view object.
 @param device The MTLDevice to be used by the view to create Metal objects
 */
- (nonnull instancetype)initWithFrame:(CGRect)frameRect device:(nullable id<MTLDevice>)device NS_DESIGNATED_INITIALIZER;

/*!
 @method initWithCoder:
 @abstract Returns a view initalized from data in a given unarchiver
 @param coder An unarchiver object
 */
- (nonnull instancetype)initWithCoder:(nonnull NSCoder *)coder NS_DESIGNATED_INITIALIZER;

/*!
 @property delegate
 @abstract The delegate handling common view operations
 */
@property (nonatomic, weak, nullable) id <MTKViewDelegate> delegate;

/*!
 @property device
 @abstract The MTLDevice used to create Metal objects
 @discussion This must be explicitly set by the application unless it was passed into the initializer. Defaults to nil
  */
@property (nonatomic, nullable) id <MTLDevice> device;

/*!
 @property currentDrawable
 @abstract The drawable to be used for the current frame.
 @discussion currentDrawable is updated at the end -draw (i.e. after the delegate's drawInMTKView method is called)
 */
@property (nonatomic, readonly, nullable) id <CAMetalDrawable> currentDrawable;

/*!
 @property framebufferOnly
 @abstract If the currentDrawable can be used for sampling or texture read operations
 @discussion This defaults to YES. This property controls whether or not the returned drawables' MTLTextures may only be used for framebuffer attachments (YES) or whether they may also be used for texture sampling and pixel read/write operations (NO). A value of YES allows the CAMetalLayer to allocate the MTLTexture objects in ways that are optimized for display purposes that makes them unsuitable for sampling. The recommended value for most applications is YES.
 */
@property (nonatomic) BOOL framebufferOnly;

/*!
 @property depthStencilAttachmentTextureUsage
 @abstract The usage flags set on the depth attachment.
 @discussion This property controls the texture usage flags set on the MTKView's depth-stencil attachment on creation.  This value defaults to MTLTextureUsageRenderTarget. The recommended value for most applications is MTLTextureUsageRenderTarget. Changing this value re-creates the depth attachment, but any data currently in the depth attachment will be lost.
 */
@property (nonatomic) MTLTextureUsage depthStencilAttachmentTextureUsage API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property multisampleColorAttachmentTextureUsage
 @abstract The texture usage flags for the multisample color attachment.
 @discussion This property controls the texture usage flags set on the the multisample color attachment attachment.  This value defaults to MTLTextureUsageRenderTarget. The recommended value for most applications is MTLTextureUsageRenderTarget. Changing this value re-creates the multisample color attachment, but any data currently in the multisample color attachment will be lost.
 */
@property (nonatomic) MTLTextureUsage multisampleColorAttachmentTextureUsage API_AVAILABLE(macos(10.15), ios(13.0));


/*!
 @property presentsWithTransaction
 @abstract If the layer should be presented synchronously
 @discussion Defaults to NO. When NO, changes to the layer's render buffer appear on-screen asynchronously to normal layer updates. When YES, changes to the MTL content are sent to the screen via the standard CATransaction mechanisms.
*/
@property (nonatomic) BOOL presentsWithTransaction;

/*!
 @property colorPixelFormat
 @abstract The pixelFormat for the drawable's texture.
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
 @abstract A multisample color texture that will be resolved into the currentDrawable's texture
 @discussion The view will generate the multisample color buffer using the specified colorPixelFormat.  This will be nil if sampleCount is less than or equal to 1.
 */
@property (nonatomic, readonly, nullable) id <MTLTexture> multisampleColorTexture;

/*!
 @method releaseDrawables
 @abstract Release the depthStencilTexture and multisampleColorTexture
 @discussion Can be called by the app to release the textures in order to conserve memory when it goes into the background.   The view will recreate multisampleColorTexture or depthStencilTexture upon the next access of the respective properties.  Both multisampleColorTexture and depthStencilTexture will be recreated in the access to currentRenderPassDescriptor.
 */
- (void)releaseDrawables;

/*!
 @property currentRenderPassDescriptor
 @abstract A render pass descriptor generated from the currentDrawable's texture and the view's depth, stencil, and sample buffers and clear values.
 @discussion This is a convience property.  The view does not use this descriptor and there is no requirement for an app to use this descriptor.
 */
@property (nonatomic, readonly, nullable) MTLRenderPassDescriptor *currentRenderPassDescriptor;

/*!
 @property preferredFramesPerSecond
 @abstract The rate you want the view to redraw its contents.
 @discussion When your application sets its preferred frame rate, the view chooses a frame rate as close to that as possible based on the capabilities of the screen the view is displayed on. The actual frame rate chosen is usually a factor of the maximum refresh rate of the screen to provide a consistent frame rate. For example, if the maximum refresh rate of the screen is 60 frames per second, that is also the highest frame rate the view sets as the actual frame rate. However, if you ask for a lower frame rate, it might choose 30, 20, 15 or some other factor to be the actual frame rate. Your application should choose a frame rate that it can consistently maintain. The default value is 60 frames per second.
 */
@property(nonatomic) NSInteger preferredFramesPerSecond;

/*!
  @property enableSetNeedsDisplay
  @abstract Controls whether the view responds to setNeedsDisplay.
  @discussion If true, then the view behaves similarily to a UIView or NSView, responding to calls to setNeedsDisplay. When the view has been marked for display, the view is automatically redisplayed on each pass through the application’s event loop. Setting enableSetNeedsDisplay to true will also pause the MTKView's internal render loop and updates will instead be event driven. The default value is false.
 */
@property (nonatomic) BOOL enableSetNeedsDisplay;

/*!
 @property autoResizeDrawable
 @abstract Controls whether to resize the drawable as the view changes size.
 @discussion If true, the size of the currentDrawable's texture, depthStencilTexture, and multisampleColorTexture will automatically resize as the view resizes.  If false, these textures will take on the size of drawableSize and drawableSize will not change. The default value is true.
 */
@property (nonatomic) BOOL autoResizeDrawable;

/*!
 @property drawableSize
 @abstract The current size of drawable textures
 @discussion The size currentDrawable's texture, depthStencilTexture, and multisampleColorTexture.  If autoResizeDrawable is true this value will be updated as the view's size changes. If autoResizeDrawable is false, this can be set to fix the size of the drawable textures.
 */
@property (nonatomic) CGSize drawableSize;


/*!
 @property preferredDrawableSize
 @abstract The preferred drawable size reported by the backing NSView to match a NSView's native resolution.
 @discussion this value can be observed via key-value observation to determine if the current native drawable size has changed.
 */
@property (nonatomic, readonly) CGSize preferredDrawableSize API_AVAILABLE(macos(10.15));

/*!
 @property preferredDevice
 @abstract The preferred device is updated per-frame by the system in order to identify the most efficient GPU for presentation (e.g. the one being used for compositing).
 @discussion This value is determined by the underlying CAMetalLayer and this property is a convenience accessor for it.
 */
@property(nullable, readonly) id<MTLDevice> preferredDevice API_AVAILABLE(macos(10.15), ios(13.0));

/*!
 @property paused
 @abstract Controls whether the draw methods should countinue at preferredFramesPerSecond
 @discussion If true, the delegate will receive drawInMTKView: messages or the subclass will receive drawRect: messages at a rate of preferredFramesPerSecond based on an internal timer. The default value is false.
 */
@property (nonatomic, getter=isPaused) BOOL paused;

/*!
 @property colorspace
 @abstract The colorspace of the rendered frames. '
 @discussion If nil, no colormatching occurs.  If non-nil, the rendered content will be colormatched to the colorspace of the context containing this layer (typically the display's colorspace).  This property aliases the olorspace property or the view's CAMetalLayer
 */
@property (nonatomic, nullable) CGColorSpaceRef colorspace NS_AVAILABLE_MAC(10_12);

/*!
 @method draw
 @abstract Manually ask the view to draw new contents. This causes the view to call either the drawInMTKView (delegate) or drawRect (subclass) method.
 @discussion Manually ask the view to draw new contents. This causes the view to call either the drawInMTKView (delegate) or drawRect (subclass) method. This should be used when the view's paused proprety is set to true and enableSetNeedsDisplay is set to false.
 */
- (void)draw;

@end

/*!
 @class MTKViewDelegate
 @abstract Allows an object to render into the view and respond to resize events
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@protocol MTKViewDelegate <NSObject>

/*!
 @method mtkView:drawableSizeWillChange:
 @abstract Called whenever the drawableSize of the view will change
 @discussion Delegate can recompute view and projection matricies or regenerate any buffers to be compatible with the new view size or resolution
 @param view MTKView which called this method
 @param size New drawable size in pixels
 */
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size;

/*!
 @method drawInMTKView:
 @abstract Called on the delegate when it is asked to render into the view
 @discussion Called on the delegate when it is asked to render into the view
 */
- (void)drawInMTKView:(nonnull MTKView *)view;

@end
