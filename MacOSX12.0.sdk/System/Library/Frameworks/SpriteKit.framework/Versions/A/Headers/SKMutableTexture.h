/**
 @header
 
 Mutable texture is a dervied SKTexture whose pixel data can be modified after creation.
 
 @copyright 2013 Apple, Inc. All rights reserved.
 
 */

#import <SpriteKit/SpriteKitBase.h>
#import <SpriteKit/SKTexture.h>

/* SKMutableTextures are not currently supported in the simulator */

SK_EXPORT API_AVAILABLE(ios(8.0), tvos(9.0), watchos(1.0), macos(10.10)) @interface SKMutableTexture : SKTexture

/**
 Create a mutable texture with a specfic size.
 
 @param size the dimension to use when creating the given texture.
 */
- (instancetype)initWithSize:(CGSize)size;

+ (instancetype)mutableTextureWithSize:(CGSize)size;

/**
 Create a mutable texture with a specfic size and type.
 
 @param size the dimension to use when creating the given texture.
 @param format the CoreVideo format type.  supported types include 'RGBA', 'RGhA', and 'RGfA' for byte, half-float, and float components.
 */
- (instancetype)initWithSize:(CGSize)size pixelFormat:(int)format;

/**
 Modify the created mutable texture.
 */
- (void)modifyPixelDataWithBlock:(void (^)(void *pixelData, size_t lengthInBytes))block;

@end
