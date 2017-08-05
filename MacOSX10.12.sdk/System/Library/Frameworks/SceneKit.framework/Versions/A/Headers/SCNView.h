//
//  SCNView.h
//
//  Copyright (c) 2012-2016 Apple Inc. All rights reserved.
//

#import <AppKit/AppKit.h>

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

NS_ASSUME_NONNULL_BEGIN

#if defined(SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH) && SWIFT_SDK_OVERLAY2_SCENEKIT_EPOCH >= 3
typedef NSString * SCNViewOption NS_STRING_ENUM;
#else
typedef NSString * SCNViewOption;
#endif

/*!
 @constant SCNViewOptionPreferredRenderingAPI Specifies the preferred rendering API to be used by the renderer.
 @discussion Pass it as the key in the options dictionary given to initWithFrame:options:. The value is a NSNumber wrapping a SCNRenderingAPI. You can also select the preferred rendering API directly from the SCNView inspector in InterfaceBuilder.
 */
FOUNDATION_EXTERN SCNViewOption const SCNPreferredRenderingAPIKey API_AVAILABLE(macosx(10.11), ios(9.0)) __WATCHOS_UNAVAILABLE;

/*!
 @constant SCNViewOptionPreferredDevice Specifies the preferred metal device to be used by the renderer.
 @discussion The value is directly a id <MTLDevice>.
 */
FOUNDATION_EXTERN SCNViewOption const SCNPreferredDeviceKey API_AVAILABLE(macosx(10.11), ios(9.0));

/*!
 @constant SCNViewOptionPreferLowPowerDevice Specifies if the renderer should prefer a low power metal device.
 @discussion The value is a NSNumber wrapping a BOOL. Defaults to NO.
 */
FOUNDATION_EXTERN SCNViewOption const SCNPreferLowPowerDeviceKey API_AVAILABLE(macosx(10.11), ios(9.0));

#define SCNViewOptionPreferredRenderingAPI SCNPreferredRenderingAPIKey
#define SCNViewOptionPreferredDevice       SCNPreferredDeviceKey
#define SCNViewOptionPreferLowPowerDevice  SCNPreferLowPowerDeviceKey

/*!
 @class SCNView
 @abstract A SCNView is a subclass of NSView that can display a SCNScene
 */
@interface SCNView : NSView <SCNSceneRenderer, SCNTechniqueSupport>

/*! 
 @method initWithFrame:options:
 @abstract Initializes and returns a newly allocated SCNView object with a specified frame rectangle.
 @param frame The frame rectangle for the created view object.
 @param options An optional dictionary. See "View initialization options" above.
 */
- (instancetype)initWithFrame:(NSRect)frame options:(nullable NSDictionary<NSString *, id> *)options;

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @property backgroundColor
 @abstract Specifies the background color of the receiver. Defaults to opaque white.
 */
@property(nonatomic, copy) NSColor *backgroundColor;

/*! 
 @property allowsCameraControl
 @abstract A Boolean value that determines whether the user can manipulate the point of view used to render the scene. 
 @discussion  When set to YES, the user can manipulate the current point of view with the mouse or the trackpad. The scene graph and existing cameras won't be modified by this action. The default value of this property is NO.
     Note that the primary purpose of this property is to aid in debugging your application. You may want to implement you own camera controller suitable for your application.
     The built-in camera controller let you:
       - drag the mouse to rotate the camera around the scene.
       - drag+cmd to rotate the camera in local space
       - drag+shift to rotate using sticky axis
       - use the scroll wheel or alt+drag the mouse to translate the camera on its local X,Y plan.
       - alt+scroll wheel to move the camera forward/backward
       - rotate gesture (trackpad only) to roll the camera (rotation on the Z axis).
       - pinch gesture (trackpad only) move the camera forward/backward.
       - alt + pinch gesture (trackpad only) to zoom-in / zoom-out (change the fov of the camera).
 */
@property(nonatomic) BOOL allowsCameraControl;

/*!
 @property snapshot
 @abstract Draws the contents of the view and returns them as a new image object
 @discussion This method is thread-safe and may be called at any time.
 */
- (NSImage *)snapshot API_AVAILABLE(macosx(10.10));

/*! 
 @functiongroup Actions
 */
/*! 
 @method play:
 @abstract This action method begins playing the scene at its current location.
 @param sender The object (such as a button or menu item) sending the message to play the scene.
 @discussion This method does not do anything if the scene is already playing.
 */
- (IBAction)play:(nullable id)sender;

/*! 
 @method pause:
 @abstract This action method pauses the scene playback.
 @param sender The object (such as a button or menu item) sending the message to pause the scene.
 @discussion This method does not do anything if the scene is already paused.
 */
- (IBAction)pause:(nullable id)sender;

/*! 
 @method stop:
 @abstract This action method stops the scene playback and resets the current time to the start time of the scene.
 @param sender The object (such as a button or menu item) sending the message to stop playing the scene.
 */
- (IBAction)stop:(nullable id)sender;

/*!
 @property preferredFramesPerSecond
 @abstract The rate you want the view to redraw its contents.
 @discussion When your application sets its preferred frame rate, the view chooses a frame rate as close to that as possible based on the capabilities of the screen the view is displayed on. The actual frame rate chosen is usually a factor of the maximum refresh rate of the screen to provide a consistent frame rate. For example, if the maximum refresh rate of the screen is 60 frames per second, that is also the highest frame rate the view sets as the actual frame rate. However, if you ask for a lower frame rate, it might choose 30, 20, 15 or some other factor to be the actual frame rate. Your application should choose a frame rate that it can consistently maintain.
             The default value is 0 which means the display link will fire at the native cadence of the display hardware.
 */
@property(nonatomic) NSInteger preferredFramesPerSecond API_AVAILABLE(macosx(10.12));

/*!
 @property openGLContext
 @abstract Specifies the OpenGL context associated with the receiver.
 @discussion This property returns nil and has no effect if the current API is Metal.
 */
@property(nonatomic, retain, nullable) NSOpenGLContext *openGLContext;

/*!
 @property antialiasingMode
 @abstract Defaults to SCNAntialiasingModeMultisampling4X on macOS and SCNAntialiasingModeNone on iOS.
 */
@property(nonatomic) SCNAntialiasingMode antialiasingMode API_AVAILABLE(macosx(10.10));

/*!
 @property pixelFormat
 @abstract Specifies the pixel format of the receiver.
 @discussion This property returns nil and has no effect if the current API is Metal.
 */
@property(nonatomic, retain, nullable) NSOpenGLPixelFormat *pixelFormat;

@end

NS_ASSUME_NONNULL_END
