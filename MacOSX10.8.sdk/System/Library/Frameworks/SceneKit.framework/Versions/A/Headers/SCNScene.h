//
//  SCNScene.h
//
//  Copyright 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SCNAnimation.h>

@class SCNNode;


/*! @group Scene attributes
    @abstract These keys can be used with the -[SCNScene attributeForKey:] method.
 */

/*! A floating point value, encapsulated in a NSNumber, containing the start time of the scene. */
SCENEKIT_EXTERN NSString * const SCNSceneStartTimeAttributeKey;
/*! A floating point value, encapsulated in a NSNumber, containing the end time of the scene. */
SCENEKIT_EXTERN NSString * const SCNSceneEndTimeAttributeKey;
/*! A floating point value, encapsulated in a NSNumber, containing the framerate of the scene. */
SCENEKIT_EXTERN NSString * const SCNSceneFrameRateAttributeKey;

/*!
 @class SCNScene
 @abstract SCNScene is the class that describes a 3d scene. It encapsulates a node hierarchy.
 */

SCENEKIT_AVAILABLE(10_7, NA)
@interface SCNScene : NSObject 
{
@private
	id _reserved;
}

+ (SCNScene*)scene;

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
 @method sceneWithURL:options:error:
 @abstract Creates and returns a scene from the specified URL.
 @param url The URL to the 3D file.
 @param options An options dictionary. The relevant keys are documented in the SCNSceneSource class.
 @param error A NSError object passed by reference to get more information about the error when a nil is returned.
 @discussion This method is here for convenience. It is equivalent to initializing a SCNSceneSource with the specified
 url and options, and asking it for its scene with the same options.
 */
+ (SCNScene *)sceneWithURL:(NSURL *)url options:(NSDictionary *)options error:(NSError **)error;

@end

