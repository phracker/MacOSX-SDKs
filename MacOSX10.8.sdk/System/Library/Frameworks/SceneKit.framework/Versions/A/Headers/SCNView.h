//
//  SCNView.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <AppKit/AppKit.h>
#import <SceneKit/SCNSceneRenderer.h>

/*!
 @class SCNView
 @abstract A SCNView is a subclass of NSView that can display a SCNScene
 */
SCENEKIT_AVAILABLE(10_7, NA)
@interface SCNView : NSView <SCNSceneRenderer>
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
 */
@property(nonatomic) BOOL allowsCameraControl;


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
 @abstract Specifies the openGL context associated with the receiver.
 @discussion You can use this property to set an openGL context that is shared with another openGLContext. This allows you to share the resources across multiple SCNView. 
 */
@property(nonatomic, retain) NSOpenGLContext *openGLContext;

/*! 
 @property pixelFormat
 @abstract Specifies the pixel format of the receiver.
 */
@property(nonatomic, retain) NSOpenGLPixelFormat *pixelFormat;

@end

