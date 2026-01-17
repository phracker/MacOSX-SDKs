//
//  SCNScene.h
//
//  Copyright (c) 2012-2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNMaterialProperty.h>

NS_ASSUME_NONNULL_BEGIN

@class SCNNode;
@class SCNPhysicsWorld;
@protocol SCNSceneExportDelegate;

/*!
 @typedef SCNSceneSourceStatusHandler
 @discussion Signature of a block that will be called repeatedly while the scene is being exported.
 @param totalProgress is a floating-point number between 0 and 1. 0 means the loading process has just started and 1 that it is complete. 
 @param error Will contain information about the failure if any.
 @param stop Set *stop to YES if you want to abort the operation.
 */
typedef void (^SCNSceneExportProgressHandler)(float totalProgress, NSError * __nullable error, BOOL *stop);


/*! @group Scene writing options */

/*! @constant SCNSceneExportDestinationURL
 @abstract Specifies the final destination (as a NSURL) of the scene being exported.
 @discussion The destination URL is required if the scene is exported to a temporary directory and then moved to a final destination. This enables the exported document to get correct relative paths to referenced images.
 */
SCN_EXTERN NSString * const SCNSceneExportDestinationURL NS_AVAILABLE(10_9, 8_0);


/*! @group Scene attributes
    @abstract These keys can be used with the -[SCNScene attributeForKey:] method.
 */

/*! A floating point value, encapsulated in a NSNumber, containing the start time of the scene. */
SCN_EXTERN NSString * const SCNSceneStartTimeAttributeKey;
/*! A floating point value, encapsulated in a NSNumber, containing the end time of the scene. */
SCN_EXTERN NSString * const SCNSceneEndTimeAttributeKey;
/*! A floating point value, encapsulated in a NSNumber, containing the framerate of the scene. */
SCN_EXTERN NSString * const SCNSceneFrameRateAttributeKey;
/*! A vector3 value, encapsulated in a NSValue, containing the up axis of the scene. This is just for information, setting the up axis as no effect */
SCN_EXTERN NSString * const SCNSceneUpAxisAttributeKey NS_AVAILABLE(10_10, 8_0);

/*!
 @class SCNScene
 @abstract SCNScene is the class that describes a 3d scene. It encapsulates a node hierarchy.
 */

NS_CLASS_AVAILABLE(10_8, 8_0)
@interface SCNScene : NSObject <NSSecureCoding>

+ (instancetype)scene;

/*! 
 @property root
 @abstract Specifies the root node of the node hierarchy.
 @discussion Note that we have only one root node, whereas some file formats might have many nodes
 at the root of their hierarchies. The root node(s) of the imported files will therefore be children
 of the SCNScene's root node.
 */
@property(nonatomic, readonly) SCNNode *rootNode;

/*!
 @property physicsWorld
 @abstract Specifies the physics world of the receiver.
 @discussion Every scene automatically creates a physics world object to simulate physics on nodes in the scene. You use this property to access the scene’s global physics properties, such as gravity. To add physics to a particular node, see physicsBody.
 */
@property(nonatomic, readonly) SCNPhysicsWorld *physicsWorld NS_AVAILABLE(10_10, 8_0);

/*!
 @method attributeForKey:
 @abstract Retrieves a scene attribute.
 @discussion The available keys are listed in the "Scene attributes" group.
 @param key An NSString object that specifies the attribute to be read
 */
- (nullable id)attributeForKey:(NSString *)key;

/*! 
 @method setAttribute:forKey:
 @abstract Sets a scene attribute
 @discussion The available keys are listed in the "Scene attributes" group.
 @param attribute An object that specifies the value of the attribute to be written.
 @param key An NSString object that specifies the attribute to be written
 */
- (void)setAttribute:(nullable id)attribute forKey:(NSString *)key;

/*!
 @property background
 @abstract Specifies the background of the receiver.
 @discussion The background is rendered before the rest of the scene. The background can be rendered as a skybox by setting a NSArray of six images to its contents (see SCNMaterialProperty.h). Setting a color will have no effect (use SCNView's backgroundColor instead).
 */
@property(nonatomic, readonly) SCNMaterialProperty *background NS_AVAILABLE(10_9, 8_0);


#pragma mark - Loading

/*!
 @method sceneNamed:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (nullable instancetype)sceneNamed:(NSString *)name NS_AVAILABLE(10_9, 8_0);

/*!
 @method sceneNamed:options:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @param directory The name of the bundle sub-directory to search into.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (nullable instancetype)sceneNamed:(NSString *)name inDirectory:(nullable NSString *)directory options:(nullable NSDictionary<NSString *, id> *)options NS_AVAILABLE(10_10, 8_0);

/*!
 @method sceneWithURL:options:error:
 @abstract Creates and returns a scene from the specified URL.
 @param url The URL to the 3D file.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @param error A NSError object passed by reference to get more information about the error when a nil is returned.
 @discussion This method is here for convenience. It is equivalent to initializing a SCNSceneSource with the specified
 url and options, and asking it for its scene with the same options.
 */
+ (nullable instancetype)sceneWithURL:(NSURL *)url options:(nullable NSDictionary<NSString *, id> *)options error:(NSError **)error;

#pragma mark - Writing

/*!
 @method writeToURL:options:delegate:progressHandler:
 @abstract write the scene to the specified url.
 @param url the destination url to write the scene to.
 @param options A dictionary of options. The valid keys are described in the "Scene writing options" section.
 @param delegate an optional delegate to manage external references such as images.
 @param progressHandler an optional block to handle the progress of the operation.
 @return Returns YES if the operation succeeded, NO otherwise. Errors checking can be done via the "error"
 parameter of the 'progressHandler'.
 @discussion Currently only exporting to .dae files is supported.
 */
- (BOOL)writeToURL:(NSURL *)url options:(nullable NSDictionary<NSString *, id> *)options delegate:(nullable id <SCNSceneExportDelegate>)delegate progressHandler:(nullable SCNSceneExportProgressHandler)progressHandler NS_AVAILABLE(10_9, NA);

#pragma mark - Fog

/*!
 @property fogStartDistance
 @abstract Specifies the receiver's fog start distance. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat fogStartDistance NS_AVAILABLE(10_10, 8_0);

/*!
 @property fogEndDistance
 @abstract Specifies the receiver's fog end distance. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat fogEndDistance NS_AVAILABLE(10_10, 8_0);

/*!
 @property fogDensityExponent
 @abstract Specifies the receiver's fog power exponent. Animatable. Defaults to 1.
 @discussion Controls the attenuation between the start and end fog distances. 0 means a constant fog, 1 a linear fog and 2 a quadratic fog, but any positive value will work.
 */
@property(nonatomic) CGFloat fogDensityExponent NS_AVAILABLE(10_10, 8_0);

/*!
 @property fogColor
 @abstract Specifies the receiver's fog color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor.
 */
@property(nonatomic, retain) id fogColor NS_AVAILABLE(10_10, 8_0);


#pragma mark - Pause

/*!
 @property paused
 @abstract Controls whether or not the scene is paused. Defaults to NO.
 @discussion Pausing a scene will pause animations, actions, particles and physics.
 */
@property(nonatomic, getter=isPaused) BOOL paused NS_AVAILABLE(10_10, 8_0);


@end

@protocol SCNSceneExportDelegate <NSObject>
@optional
/*!
 @method writeImage:withSceneDocumentURL:originalImageURL:
 @abstract Invoked on the delegate to write the referenced image and return the destination url.
 @param image The image to write.
 @param documentURL The url where the scene is currently exported to.
 @param originalImageURL The original url for the image. May be nil if the image was not previously loaded from a url.
 @return The delegate must returns the url of the image that was exported or nil if it didn't export any image. If the returned value is nil, the image will be exported to a default destination in a default format.
 */
- (nullable NSURL *)writeImage:(NSImage *)image withSceneDocumentURL:(NSURL *)documentURL originalImageURL:(nullable NSURL *)originalImageURL NS_AVAILABLE(10_9, NA);

@end

NS_ASSUME_NONNULL_END
