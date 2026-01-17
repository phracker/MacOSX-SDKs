//
//  SKTexture.h
//  SpriteKit
//
//  Copyright (c) 2011 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SpriteKit/SpriteKitBase.h>

#if __has_include(<CoreImage/CIFilter.h>)
@class CIFilter;
#endif

typedef NS_ENUM(NSInteger, SKTextureFilteringMode) {
    SKTextureFilteringNearest,
    SKTextureFilteringLinear,
} NS_ENUM_AVAILABLE(10_9, 7_0);

NS_ASSUME_NONNULL_BEGIN

/**
 A texture to be mapped onto SKSpriteNode instances.
 */
SK_EXPORT @interface SKTexture : NSObject <NSCopying, NSSecureCoding>

/**
 Create a texture from an image file. Behaves similar to imageNamed: in UIImage or NSImage
 
 @param name the name or path of the image to load.
 */
+ (instancetype)textureWithImageNamed:(NSString *)name;

/**
 Create a texture that is a subrect of an existing texture. See textureRect property for details.
 
 @param rect the source rectangle to use in creating a logical copy of the given texture.
 @param texture the existing texture to reference in the copy.
 */
+ (instancetype)textureWithRect:(CGRect)rect inTexture:(SKTexture *)texture;


/**
 Create a texture containing directional noise. The RGBA values in this
 texture can be used as a normal map or as direction possibly with length. XYZ are a three dimensional direction, and A is a magnitude.
 
 @param rect the size of the resulting texture.
 @param smoothness how similar neighboring pixels are. A value of zero is like static, one is smooth.
 */
+ (instancetype)textureVectorNoiseWithSmoothness:(CGFloat)smoothness size:(CGSize)size NS_AVAILABLE(10_10, 8_0);


/**
 Create a texture containing colored noise. The noise texture is tileable with itself.
 
 @param rect the size of the resulting texture.
 @param smoothness how similar neighboring pixels are. A value of zero is like static, one is smooth.
 @param grayscale if YES, RGB and A will all be the same. If no, RGB and A will all be different. A is not pre-multiplied, because the intent is that if you read a texel in a shader, all four values will be exactly the same value if grayscale, or four different, uncorrelated values if not grayscale.
 */
+ (instancetype)textureNoiseWithSmoothness:(CGFloat)smoothness size:(CGSize)size grayscale:(BOOL)grayscale NS_AVAILABLE(10_10, 8_0);


/**
 Create a texture from a CGImageRef.
 
 @param image the CGImageRef to create the texture from
 */
+ (instancetype)textureWithCGImage:(CGImageRef)image;

#if TARGET_OS_IPHONE
+ (instancetype)textureWithImage:(UIImage *)image;
#else
+ (instancetype)textureWithImage:(NSImage *)image;
#endif

/**
 Create new texture with bitmap RGBA data in unsigned bytes. Data is copied once, additional changes to the data does not affect the texture. All pixel data is assumed to be premultiplied alpha.
 
 @param pixelData the pixelData to read in creating the texture.
 @param size the dimensions of the pixelData given.
 */
+ (instancetype)textureWithData:(NSData *)pixelData size:(CGSize)size;
+ (instancetype)textureWithData:(NSData *)pixelData size:(CGSize)size flipped:(BOOL)flipped;

/**
 Create new texture with bitmap RGBA data in unsigned bytes using a custom row length and row alignment. Data is copied once, additional changes to the data does not affect the texture. All pixel data is assumed to be premultiplied alpha.
 
 @param pixelData the data to use
 @param size the size in texels
 @param rowLength the length of each row in pixels (allows byte row pitches greater than the width for aligned data)
 @param alignment the byte alignment of the data, provide 0 for tightly packed data.

 */
+ (instancetype)textureWithData:(NSData *)pixelData size:(CGSize)size rowLength:(unsigned int)rowLength alignment:(unsigned int)alignment;


#if __has_include(<CoreImage/CIFilter.h>)
/**
 Create new texture by applying a CIFilter to an existing one. Any CIFilter that requires only a single "inputImage" and produces an "outputImage" is allowed.
 
 @param filter the CI filter to apply in the copy.
 */
- (instancetype)textureByApplyingCIFilter:(CIFilter *)filter;
#endif


/**
 Create new texture by generating a normal map texture.
  */
- (instancetype)textureByGeneratingNormalMap NS_AVAILABLE(10_10, 8_0);


/**
 Create new texture by generating a normal map texture.
 
 @param smoothness the smooth level of the generated normal map.
 @param contrast  the scale applied to the generated normal map.
 */
- (instancetype)textureByGeneratingNormalMapWithSmoothness:(CGFloat)smoothness contrast:(CGFloat)contrast NS_AVAILABLE(10_10, 8_0);

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
@property (nonatomic) SKTextureFilteringMode filteringMode;


/**
 Request that the texture have mipmaps generated if possible. Only supported for power of 2 texture sizes.
 */
@property (nonatomic) BOOL usesMipmaps;


/**
 Convert the current SKTexture into a CGImageRef object
 */
- (CGImageRef)CGImage CF_RETURNS_RETAINED NS_AVAILABLE(10_11, 9_0);

/**
 Start a texture preload operation on an array of textures
 
 @param textures an array of SKTextures to be preloaded
 @param completionhandler will be called upon the preload completion
 
 */
+ (void)preloadTextures:(NSArray<SKTexture*> *)textures withCompletionHandler:(void(^)(void))completionHandler;

/**
 Request that this texture be loaded into vram on the next render update, with a callback handler.
 */
- (void)preloadWithCompletionHandler:(void(^)(void))completionHandler;

@end

NS_ASSUME_NONNULL_END
