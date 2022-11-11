//
//  SKTextureAtlas.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SKTexture.h>

NS_ASSUME_NONNULL_BEGIN

SK_EXPORT @interface SKTextureAtlas : NSObject <NSSecureCoding>


/* Atlas with .png and .plist file name*/
+ (instancetype)atlasNamed:(NSString *)name;

/* Create a texture atlas on the fly */
+ (instancetype)atlasWithDictionary:(NSDictionary<NSString*, id> *)properties API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10));

/* Individual texture for image name within the atlas */
- (SKTexture *)textureNamed:(NSString *)name;

/**
 Start a texture atlas preload operation on an array of texture atlas
 
 @param textureAtlases an array of SKTextureAtlas to be preloaded
 @param completionHandler will be called upon the preload completion
 
 */
+ (void)preloadTextureAtlases:(NSArray<SKTextureAtlas*> *)textureAtlases withCompletionHandler:(void(^)(void))completionHandler;

/** 
 Start a texture atlas preload operation on an array of texture atlas identifiers, error == nil if all atlases were found,
 else an NSError is returned and the user info will contain a list of the atlases that couldn't be found
 the ones that could be found are looked up and prefetched.

 @param atlasNames is an array of the SKTextureAtlas, that were located and preloaded.
 @param completionHandler will be called upon the preload completion.
 */
+ (void)preloadTextureAtlasesNamed:(NSArray<NSString *> *)atlasNames withCompletionHandler:(void (^)(NSError * __nullable error, NSArray<SKTextureAtlas *> *foundAtlases))completionHandler API_AVAILABLE(ios(9.0), tvos(9.0), watchos(2.0), macos(10.11));

/**
 Request that this texture atlas be loaded into vram on the next render update, with a callback handler.
 */
- (void)preloadWithCompletionHandler:(void(^)(void))completionHandler;

/* Returns the array of valid textures in the atlas */
@property (nonatomic, readonly) NSArray<NSString*> *textureNames;

@end

NS_ASSUME_NONNULL_END
