//
//  SCNView.h
//
//  Copyright (c) 2012-2014 Apple Inc. All rights reserved.
//

#import <AppKit/AppKit.h>

#import <SceneKit/SCNSceneRenderer.h>
#import <SceneKit/SCNTechnique.h>

/*! 
 @enum SCNAntialiasingMode
 @abstract antialiasing modes for SCNView
 */
typedef NS_ENUM(NSUInteger, SCNAntialiasingMode) {
    SCNAntialiasingModeNone,
    SCNAntialiasingModeMultisampling2X,
    SCNAntialiasingModeMultisampling4X,
    SCNAntialiasingModeMultisampling8X,
    SCNAntialiasingModeMultisampling16X
} SCENEKIT_ENUM_AVAILABLE(10_10, 8_0);


/*!
 @class SCNView
 @abstract A SCNView is a subclass of NSView that can display a SCNScene
 */
SCENEKIT_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNView : NSView <SCNSceneRenderer, SCNTechniqueSupport>
{
@private
	id _reserved;
}


/*! 
 @method initWithFrame:options:
 @abstract Initializes and returns a newly allocated SCNView object with a specified frame rectangle.
 @param frame The frame rectangle for the created view object.
 @param options An optional dictionary for future extensions.
 */
- (id)initWithFrame:(NSRect)frame options:(NSDictionary *)options;

/*! 
 @property scene
 @abstract Specifies the scene of the receiver
 */
@property(nonatomic, retain) SCNScene *scene;

/*!
 @property backgroundColor
 @abstract Specifies the background color of the receiver
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
       - pinch gesture (trackpad only) to zoom-in / zoom-out (change the fov of the camera).
 */
@property(nonatomic) BOOL allowsCameraControl;

/*!
 @property snapshot
 @abstract Draws the contents of the view and returns them as a new image object
 @discussion This method is thread-safe and may be called at any time.
 */
- (NSImage *)snapshot SCENEKIT_AVAILABLE(10_10, 8_0);

/*! 
 @functiongroup Actions
 */
/*! 
 @method play:
 @abstract This action method begins playing the scene at its current location.
 @param sender The object (such as a button or menu item) sending the message to play the scene.
 @discussion This method does not do anything if the scene is already playing.
 */
- (IBAction)play:(id)sender;

/*! 
 @method pause:
 @abstract This action method pauses the scene playback.
 @param sender The object (such as a button or menu item) sending the message to pause the scene.
 @discussion This method does not do anything if the scene is already paused.
 */
- (IBAction)pause:(id)sender;

/*! 
 @method stop:
 @abstract This action method stops the scene playback and resets the current time to the start time of the scene.
 @param sender The object (such as a button or menu item) sending the message to stop playing the scene.
 */
- (IBAction)stop:(id)sender;

/*!
 @property openGLContext
 @abstract Specifies the OpenGL context associated with the receiver.
 */
@property(nonatomic, retain) NSOpenGLContext *openGLContext;

/*!
 @property antialiasingMode
 @abstract Defaults to SCNAntialiasingModeMultisampling4X on OSX and SCNAntialiasingModeNone on iOS.
 */
@property(nonatomic) SCNAntialiasingMode antialiasingMode SCENEKIT_AVAILABLE(10_10, 8_0);

/*!
 @property pixelFormat
 @abstract Specifies the pixel format of the receiver.
 */
@property(nonatomic, retain) NSOpenGLPixelFormat *pixelFormat;

@end
