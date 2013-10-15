//
//  SCNScene.h
//
//  Copyright (c) 2012-2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>
#import <SceneKit/SCNMaterialProperty.h>

@class SCNNode;
@protocol SCNSceneExportDelegate;

/*!
 @typedef SCNSceneSourceStatusHandler
 @discussion Signature of a block that will be called repeatedly while the scene is being exported.
 @param totalProgress is a floating-point number between 0 and 1. 0 means the loading process has just started and 1 that it is complete. 
 @param error Will contain information about the failure if any.
 @param stop Set *stop to YES if you want to abort the operation.
 */
typedef void (^SCNSceneExportProgressHandler)(float totalProgress, NSError *error, BOOL *stop);


/*! @group Scene writing options */

/*! @constant SCNSceneExportDestinationURL
 @abstract Specifies the final destination (as a NSURL) of the scene being exported.
 @discussion The destination URL is required if the scene is exported to a temporary directory and then moved to a final destination. This enables the exported document to get correct relative paths to referenced images.
 */
SCN_EXTERN NSString * const SCNSceneExportDestinationURL SCENEKIT_AVAILABLE(10_9, NA);


/*! @group Scene attributes
    @abstract These keys can be used with the -[SCNScene attributeForKey:] method.
 */

/*! A floating point value, encapsulated in a NSNumber, containing the start time of the scene. */
SCN_EXTERN NSString * const SCNSceneStartTimeAttributeKey;
/*! A floating point value, encapsulated in a NSNumber, containing the end time of the scene. */
SCN_EXTERN NSString * const SCNSceneEndTimeAttributeKey;
/*! A floating point value, encapsulated in a NSNumber, containing the framerate of the scene. */
SCN_EXTERN NSString * const SCNSceneFrameRateAttributeKey;

/*!
 @class SCNScene
 @abstract SCNScene is the class that describes a 3d scene. It encapsulates a node hierarchy.
 */

SCENEKIT_CLASS_AVAILABLE(10_8, NA)
@interface SCNScene : NSObject 
{
@private
	id _reserved;
}

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
 @method attributeForKey:
 @abstract Retrieves a scene attribute.
 @discussion The available keys are listed in the "Scene attributes" group.
 @param key An NSString object that specifies the attribute to be read
 */
- (id)attributeForKey:(NSString *)key;

/*! 
 @method setAttribute:forKey:
 @abstract Sets a scene attribute
 @discussion The available keys are listed in the "Scene attributes" group.
 @param attribute An object that specifies the value of the attribute to be written.
 @param key An NSString object that specifies the attribute to be written
 */
- (void)setAttribute:(id)attribute forKey:(NSString *)key;

/*!
 @property background
 @abstract Specifies the background of the receiver.
 @discussion The background is rendered before the rest of the scene. The background can be rendered as a skybox by setting a NSArray of six images to its contents (see SCNMaterialProperty.h).
 */
@property(nonatomic, readonly) SCNMaterialProperty *background SCENEKIT_AVAILABLE(10_9, NA);

/*!
 @method sceneNamed:
 @abstract Creates and returns a scene associated with the specified filename.
 @param name The name of the file. The method looks for a file with the specified name in the application’s main bundle.
 @discussion This method initializes with no options and does not check for errors. The resulting object is not cached.
 */
+ (instancetype)sceneNamed:(NSString *)name SCENEKIT_AVAILABLE(10_9, NA);

/*!
 @method sceneWithURL:options:error:
 @abstract Creates and returns a scene from the specified URL.
 @param url The URL to the 3D file.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @param error A NSError object passed by reference to get more information about the error when a nil is returned.
 @discussion This method is here for convenience. It is equivalent to initializing a SCNSceneSource with the specified
 url and options, and asking it for its scene with the same options.
 */
+ (instancetype)sceneWithURL:(NSURL *)url options:(NSDictionary *)options error:(NSError **)error;

/*!
 @method writeToURL:options:delegate:progressHandler:
 @abstract write the scene to the specified url.
 @param url the destination url to write the scene to.
 @param options A dictionary of options. The valid keys are described in the "Scene writing options" section.
 @param delegate an optional delegate to manage external references such as images.
 @param progressHandler an optional block to handle the progress of the operation.
 @return Returns YES if the operation succeeded, NO otherwise. Errors checking can be done via the "error"
 parameter of the 'progressHandler'.
 @discussion Currently only the COLLADA format is supported.
 */
- (BOOL)writeToURL:(NSURL *)url options:(NSDictionary *)options delegate:(id <SCNSceneExportDelegate>)delegate progressHandler:(SCNSceneExportProgressHandler)progressHandler SCENEKIT_AVAILABLE(10_9, NA);

@end


@protocol SCNSceneExportDelegate
@optional
/*!
 @method writeImage:withSceneDocumentURL:originalImageURL:
 @abstract Invoked on the delegate to write the referenced image and return the destination url.
 @param image The image to write.
 @param documentURL The url where the scene is currently exported to.
 @param originalImageURL The original url for the image. May be nil if the image was not previously loaded from a url.
 @return The delegate must returns the url of the image that was exported or nil if it didn't export any image. If the returned value is nil, the image will be exported to a default destination in a default format.
 */
- (NSURL *)writeImage:(NSImage *)image withSceneDocumentURL:(NSURL *)documentURL originalImageURL:(NSURL *)originalImageURL SCENEKIT_AVAILABLE(10_9, NA);

@end
