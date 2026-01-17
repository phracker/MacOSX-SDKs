//
//  SKTexture.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

@class CIFilter;

typedef NS_ENUM(NSInteger, SKTextureFilteringMode) {
    SKTextureFilteringNearest,
    SKTextureFilteringLinear,
} NS_ENUM_AVAILABLE(10_9, 7_0);

/**
 A texture to be mapped onto SKSpriteNode instances.
 */
SK_EXPORT @interface SKTexture : NSObject <NSCopying, NSCoding>

/**
 Create a texture from an image file. Behaves similar to imageNamed: in UIImage or NSImage
 
 @param name the name or path of the image to load.
 */
+ (SKTexture *)textureWithImageNamed:(NSString *)name;

/**
 Create a texture that is a subrect of an existing texture. See textureRect property for details.
 
 @param rect the source rectangle to use in creating a logical copy of the given texture.
 @param texture the existing texture to reference in the copy.
 */
+ (SKTexture *)textureWithRect:(CGRect)rect inTexture:(SKTexture *)texture;


/**
 Create a texture from a CGImageRef.
 
 @param image the CGImageRef to create the texture from
 */
+ (SKTexture *)textureWithCGImage:(CGImageRef)image;

#if TARGET_OS_IPHONE
+ (SKTexture *)textureWithImage:(UIImage *)image;
#else
+ (SKTexture *)textureWithImage:(NSImage *)image;
#endif

/**
 Create new texture with bitmap RGBA data in unsigned bytes. Data is copied once, additional changes to the data does not affect the texture. All pixel data is assumed to be premultiplied alpha.
 
 @param pixelData the pixelData to read in creating the texture.
 @param size the dimensions of the pixelData given.
 */
+ (SKTexture *)textureWithData:(NSData *)pixelData size:(CGSize)size;

/**
 Create new texture with bitmap RGBA data in unsigned bytes using a custom row length and row alignment. Data is copied once, additional changes to the data does not affect the texture. All pixel data is assumed to be premultiplied alpha.
 
 @param pixelData the data to use
 @param size the size in texels
 @param rowLength the length of each row in pixels (allows byte row pitches greater than the width for aligned data)
 @param alignment the byte alignment of the data, provide 0 for tightly packed data.

 */
+ (SKTexture *)textureWithData:(NSData *)pixelData size:(CGSize)size rowLength:(unsigned int)rowLength alignment:(unsigned int)alignment;

/**
 Create new texture by applying a CIFilter to an existing one. Any CIFilter that requires only a single "inputImage" and produces an "outputImage" is allowed.
 
 @param filter the CI filter to apply in the copy.
 */
- (SKTexture *)textureByApplyingCIFilter:(CIFilter *)filter;

/**
 Used to choose the area of the texture you want to display. The origin and size should both be in the range 0.0 - 1.0, values outside of this range produces unpredictable results. Defaults to the entire texture {(0,0) (1,1)}.
 */
- (CGRect)textureRect;

/**
 The size of the texture's bitmap data in points.
 */
- (CGSize)size;

/**
 The filtering mode the texture should use when not drawn at native size. Defaults to SKTextureFilteringLinear.
 */
@property (SK_NONATOMIC_IOSONLY) SKTextureFilteringMode filteringMode;


/**
 Request that the texture have mipmaps generated if possible. Only supported for power of 2 texture sizes.
 */
@property (SK_NONATOMIC_IOSONLY) BOOL usesMipmaps;

/**
 Start a texture preload operation on an array of textures
 
 @param textures an array of SKTextures to be preloaded
 @param completionhandler will be called upon the preload completion
 
 */
+ (void)preloadTextures:(NSArray *)textures withCompletionHandler:(void(^)(void))completionHandler;

/**
 Request that this texture be loaded into vram on the next render update, with a callback handler.
 */
- (void)preloadWithCompletionHandler:(void(^)(void))completionHandler;

@end
