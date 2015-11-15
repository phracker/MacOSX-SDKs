//
//  SKTextureAtlas.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKTexture.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKTextureAtlas : NSObject <NSCoding>


/* Atlas with .png and .plist file name*/
+ (instancetype)atlasNamed:(NSString *)name;

/* Create a texture atlas on the fly */
+ (instancetype)atlasWithDictionary:(NSDictionary<NSString*, id> *)properties NS_AVAILABLE(10_10, 8_0);

/* Individual texture for image name within the atlas */
- (SKTexture *)textureNamed:(NSString *)name;

/**
 Start a texture atlas preload operation on an array of texture atlas
 
 @param textureAtlases an array of SKTextureAtlas to be preloaded
 @param completionhandler will be called upon the preload completion
 
 */
+ (void)preloadTextureAtlases:(NSArray<SKTextureAtlas*> *)textureAtlases withCompletionHandler:(void(^)(void))completionHandler;

/** 
 Start a texture atlas preload operation on an array of texture atlas identifiers, error == nil if all atlases were found,
 else an NSError is returned and the user info will contain a list of the atlases that couldn't be found
 the ones that could be found are looked up and prefetched.

 @param foundAtlases is an array of the SKTextureAtlas, that were located and preloaded.
 @param error will contain which ones couldn't be found.
 */
+ (void)preloadTextureAtlasesNamed:(NSArray<NSString *> *)atlasNames withCompletionHandler:(void (^)(NSError * __nullable error, NSArray<SKTextureAtlas *> *foundAtlases))completionHandler NS_AVAILABLE(10_11, 9_0);

/**
 Request that this texture atlas be loaded into vram on the next render update, with a callback handler.
 */
- (void)preloadWithCompletionHandler:(void(^)(void))completionHandler;

/* Returns the array of valid textures in the atlas */
@property (nonatomic, readonly) NSArray<NSString*> *textureNames;

@end

NS_ASSUME_NONNULL_END
