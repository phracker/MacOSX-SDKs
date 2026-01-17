//
//  SCNScene.h
//  SceneKit
//
//  Copyright © 2012-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNSceneSource.h>
#import <SceneKit/SCNMaterialProperty.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;
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
typedef void (^SCNSceneExportProgressHandler)(float totalProgress, NSError * _Nullable error, BOOL *stop);


/*! @group Scene writing options */

/*! @constant SCNSceneExportDestinationURL
 @abstract Specifies the final destination (as a NSURL) of the scene being exported.
 @discussion The destination URL is required if the scene is exported to a temporary directory and then moved to a final destination. This enables the exported document to get correct relative paths to referenced images.
 */
SCN_EXPORT NSString * const SCNSceneExportDestinationURL API_AVAILABLE(macos(10.9));


/*! @group Scene attributes
    @abstract These keys can be used with the -[SCNScene attributeForKey:] method.
 */

typedef NSString * SCNSceneAttribute NS_STRING_ENUM;
SCN_EXPORT SCNSceneAttribute const SCNSceneStartTimeAttributeKey;                          // A floating point value, encapsulated in a NSNumber, containing the start time of the scene.
SCN_EXPORT SCNSceneAttribute const SCNSceneEndTimeAttributeKey;                            // A floating point value, encapsulated in a NSNumber, containing the end time of the scene.
SCN_EXPORT SCNSceneAttribute const SCNSceneFrameRateAttributeKey;                          // A floating point value, encapsulated in a NSNumber, containing the framerate of the scene.
SCN_EXPORT SCNSceneAttribute const SCNSceneUpAxisAttributeKey API_AVAILABLE(macos(10.10)); // A vector3 value, encapsulated in a NSValue, containing the up axis of the scene. This is just for information, setting the up axis as no effect.

#define SCNSceneAttributeStartTime SCNSceneStartTimeAttributeKey
#define SCNSceneAttributeEndTime   SCNSceneEndTimeAttributeKey
#define SCNSceneAttributeFrameRate SCNSceneFrameRateAttributeKey
#define SCNSceneAttributeUpAxis    SCNSceneUpAxisAttributeKey

/*!
 @class SCNScene
 @abstract SCNScene is the class that describes a 3d scene. It encapsulates a node hierarchy.
 */

SCN_EXPORT
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
@property(nonatomic, readonly) SCNPhysicsWorld *physicsWorld API_AVAILABLE(macos(10.10));

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
 @discussion The background is rendered before the rest of the scene.
             The background can be rendered as a skybox by setting a cube map as described in SCNMaterialProperty.h
             Colors are supported starting in macOS 10.12 and iOS 10. Prior to that you can use SCNView.backgroundColor.
             MDLSkyCubeTexture is supported starting in macOS 10.13 and iOS 11.
 */
@property(nonatomic, readonly) SCNMaterialProperty *background API_AVAILABLE(macos(10.9));

/*!
 @property lightingEnvironment
 @abstract Specifies the receiver's environment for image-based lighting (IBL).
 @discussion The environment should be a cube map as described in SCNMaterialProperty.h.
             MDLSkyCubeTexture is supported starting in macOS 10.13 and iOS 11.
 */
@property(nonatomic, readonly) SCNMaterialProperty *lightingEnvironment API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0));


#pragma mark - Loading

/*!
 @method sceneNamed:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (nullable instancetype)sceneNamed:(NSString *)name API_AVAILABLE(macos(10.9));

/*!
 @method sceneNamed:options:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @param directory The name of the bundle sub-directory to search into.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (nullable instancetype)sceneNamed:(NSString *)name inDirectory:(nullable NSString *)directory options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options API_AVAILABLE(macos(10.10));

/*!
 @method sceneWithURL:options:error:
 @abstract Creates and returns a scene from the specified URL.
 @param url The URL to the 3D file.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @param error A NSError object passed by reference to get more information about the error when a nil is returned.
 @discussion This method is here for convenience. It is equivalent to initializing a SCNSceneSource with the specified
 url and options, and asking it for its scene with the same options.
 */
+ (nullable instancetype)sceneWithURL:(NSURL *)url options:(nullable NSDictionary<SCNSceneSourceLoadingOption, id> *)options error:(NSError **)error;

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
 @discussion macOS 10.10 and lower only supports exporting to .dae files.
             Starting macOS 10.11 exporting supports .dae, .scn as well as file all formats supported by Model I/O.
             Starting iOS 10 exporting supports .scn as well as all file formats supported by Model I/O.
 */
- (BOOL)writeToURL:(NSURL *)url options:(nullable NSDictionary<NSString *, id> *)options delegate:(nullable id <SCNSceneExportDelegate>)delegate progressHandler:(nullable SCNSceneExportProgressHandler)progressHandler API_AVAILABLE(macos(10.9), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

#pragma mark - Fog

/*!
 @property fogStartDistance
 @abstract Specifies the receiver's fog start distance. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat fogStartDistance API_AVAILABLE(macos(10.10));

/*!
 @property fogEndDistance
 @abstract Specifies the receiver's fog end distance. Animatable. Defaults to 0.
 */
@property(nonatomic) CGFloat fogEndDistance API_AVAILABLE(macos(10.10));

/*!
 @property fogDensityExponent
 @abstract Specifies the receiver's fog power exponent. Animatable. Defaults to 1.
 @discussion Controls the attenuation between the start and end fog distances. 0 means a constant fog, 1 a linear fog and 2 a quadratic fog, but any positive value will work.
 */
@property(nonatomic) CGFloat fogDensityExponent API_AVAILABLE(macos(10.10));

/*!
 @property fogColor
 @abstract Specifies the receiver's fog color (NSColor or CGColorRef). Animatable. Defaults to white.
 @discussion The initial value is a NSColor.
 */
@property(nonatomic, retain) id fogColor API_AVAILABLE(macos(10.10));

#pragma mark - SSR

/*!
 @property wantsScreenSpaceReflection
 @abstract Determines if the scene use screen space reflection.
 @discussion Defaults to NO.
 */
@property(nonatomic) BOOL wantsScreenSpaceReflection API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property screenSpaceReflectionSampleCount
 @abstract Determines the sample count of the screen space reflection.
 @discussion Defaults to 64.
 */
@property(nonatomic) NSInteger screenSpaceReflectionSampleCount API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property screenSpaceReflectionMaximumDistance
 @abstract Determines the maximum distance in world units.
 @discussion Defaults to 1000.
 */
@property(nonatomic) CGFloat screenSpaceReflectionMaximumDistance API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

/*!
 @property screenSpaceReflectionStride
 @abstract Raytracing step size in pixel. The lower the better, the higher the faster.
 @discussion Defaults to 8.
 */
@property(nonatomic) CGFloat screenSpaceReflectionStride API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0));

#pragma mark - Pause

/*!
 @property paused
 @abstract Controls whether or not the scene is paused. Defaults to NO.
 @discussion Pausing a scene will pause animations, actions, particles and physics.
 */
@property(nonatomic, getter=isPaused) BOOL paused API_AVAILABLE(macos(10.10));

@end

API_AVAILABLE(macos(10.9), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos)
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
- (nullable NSURL *)writeImage:(UIImage *)image withSceneDocumentURL:(NSURL *)documentURL originalImageURL:(nullable NSURL *)originalImageURL API_AVAILABLE(macos(10.9), ios(10.0), tvos(10.0)) API_UNAVAILABLE(watchos);

@end

NS_ASSUME_NONNULL_END
