//
//  SCNView.h
//  SceneKit
//
//  Copyright © 2012-2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

@class SCNCameraController;

NS_ASSUME_NONNULL_BEGIN

typedef NSString * SCNViewOption NS_STRING_ENUM;

/*!
 @constant SCNViewOptionPreferredDevice Specifies the preferred Metal device to be used by the renderer.
 @discussion The value is directly a id <MTLDevice>.
 */
SCN_EXPORT SCNViewOption const SCNPreferredDeviceKey API_AVAILABLE(macos(10.11), ios(9.0));

/*!
 @constant SCNViewOptionPreferLowPowerDevice Specifies if the renderer should prefer a low power Metal device.
 @discussion The value is a NSNumber wrapping a BOOL. Defaults to NO.
 */
SCN_EXPORT SCNViewOption const SCNPreferLowPowerDeviceKey API_AVAILABLE(macos(10.11), ios(9.0));

#define SCNViewOptionPreferredDevice       SCNPreferredDeviceKey
#define SCNViewOptionPreferLowPowerDevice  SCNPreferLowPowerDeviceKey

API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0))
@protocol SCNCameraControlConfiguration <NSObject>

@property(nonatomic, assign) BOOL autoSwitchToFreeCamera;
@property(nonatomic, assign) BOOL allowsTranslation;
@property(nonatomic, assign) CGFloat flyModeVelocity; // in m/s
@property(nonatomic, assign) CGFloat panSensitivity;
@property(nonatomic, assign) CGFloat truckSensitivity;
@property(nonatomic, assign) CGFloat rotationSensitivity;

@end

/*!
 @class SCNView
 @abstract A SCNView is a subclass of NSView that can display a SCNScene
 */
API_UNAVAILABLE(watchos)
SCN_EXPORT
@interface SCNView : UIView <SCNSceneRenderer, SCNTechniqueSupport>

/*! 
 @method initWithFrame:options:
 @abstract Initializes and returns a newly allocated SCNView object with a specified frame rectangle.
 @param frame The frame rectangle for the created view object.
 @param options An optional dictionary. See "View initialization options" above.
 */
- (instancetype)initWithFrame:(CGRect)frame options:(nullable NSDictionary<NSString *, id> *)options;

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain, nullable) SCNScene *scene;

/*!
 @property rendersContinuously
 @abstract When set to YES, the view continously redraw at the display link frame rate. When set to NO the view will only redraw when something change or animates in the receiver's scene. Defaults to NO.
 */
@property(nonatomic, assign) BOOL rendersContinuously;


/*! 
 @property allowsCameraControl
 @abstract A Boolean value that determines whether the user can manipulate the point of view used to render the scene. 
 @discussion  When set to YES, a defaultCameraController is created and the view will handle UI events to pilot it so the user can manipulate the current point of view with the mouse or the trackpad. The scene graph and existing cameras won't be modified by this action. The default value of this property is NO.
     Note that the default event handling provided by the view may not suite your needs. You may want to implement you own evnet handler.
     The built-in camera controller let you:
       - pan with 1 finger to rotate the camera around the scene.
       - pan with 2 fingers to translate the camera on its local X,Y plan.
       - pan with 3 fingers vertically to move the the camera forward/backward.
       - double tap to switch to the next camera in the scene.
       - rotate with two fingers to roll the camera (rotation on the Z axis).
       - pinch to zoom-in / zoom-out (change the fov of the camera).
 */
@property(nonatomic) BOOL allowsCameraControl;

/*! 
 @property cameraControlConfiguration
 @abstract An object describing the current configuration of the event handler which pilot the default camera controller.
 @discussion This object will be used to configure the event handler when allowCameraControl is set to YES.
 */
@property(nonatomic, readonly) id <SCNCameraControlConfiguration> cameraControlConfiguration API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property defaultCameraController
 @abstract Returns the default SCNCameraController used to drive the current point of view when allowCameraController is set to YES.
 */
@property(nonnull, nonatomic, readonly) SCNCameraController* defaultCameraController API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0), watchos(4.0));

/*!
 @property snapshot
 @abstract Draws the contents of the view and returns them as a new image object
 @discussion This method is thread-safe and may be called at any time.
 */
- (UIImage *)snapshot API_AVAILABLE(macos(10.10));

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
@property(nonatomic) NSInteger preferredFramesPerSecond API_AVAILABLE(macos(10.12));


#if SCN_ENABLE_OPENGL

/*!
 @property eaglContext
 @abstract Specifies the EAGL context associated with the receiver.
 @discussion This property returns nil and has no effect if the current API is Metal.
 */
@property(nonatomic, retain, nullable) EAGLContext *eaglContext SCN_GL_DEPRECATED_IOS(8_0, 12_0); // SCN_GL_DEPRECATED(ios(8.0, 12.0), tvos(9.0, 12.0));

#endif

/*!
 @property antialiasingMode
 @abstract Defaults to SCNAntialiasingModeMultisampling4X on macOS and SCNAntialiasingModeNone on iOS.
 */
@property(nonatomic) SCNAntialiasingMode antialiasingMode API_AVAILABLE(macos(10.10));



@end

NS_ASSUME_NONNULL_END
