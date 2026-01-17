//
//  SKTextureAtlas.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKTexture.h>

SK_EXPORT @interface SKTextureAtlas : NSObject <NSCoding>

/* Atlas with .png and .plist file name*/
+ (SKTextureAtlas *)atlasNamed:(NSString *)name;

/* Individual texture for image name within the atlas */
- (SKTexture *)textureNamed:(NSString *)name;

/**
 Start a texture atlas preload operation on an array of texture atlas
 
 @param textureAtlases an array of SKTextureAtlas to be preloaded
 @param completionhandler will be called upon the preload completion
 
 */
+ (void)preloadTextureAtlases:(NSArray *)textureAtlases withCompletionHandler:(void(^)(void))completionHandler;

/**
 Request that this texture atlas be loaded into vram on the next render update, with a callback handler.
 */
- (void)preloadWithCompletionHandler:(void(^)(void))completionHandler;


/* Returns the array of valid textures in the atlas */
@property (SK_NONATOMIC_IOSONLY, readonly) NSArray *textureNames;

@end
