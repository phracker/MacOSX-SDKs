/*!
 @header MDLTexture.h
 @framework ModelIO
 @abstract Representation of textures for use in rendering
 @copyright Copyright © 2015 Apple, Inc. All rights reserved.
 */


#pragma once

#import <Foundation/Foundation.h>
#import <ModelIO/ModelIOExports.h>
#import <ModelIO/MDLTypes.h>
#import <ModelIO/MDLObject.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreGraphics/CGImage.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN


@class NSURL;
@class NSString;

/**
 The enoding of texel channel elements
 */

typedef NS_ENUM(NSInteger, MDLTextureChannelEncoding) {
    MDLTextureChannelEncodingUInt8 = 1,
    MDLTextureChannelEncodingUint8 = 1,
    MDLTextureChannelEncodingUInt16 = 2,
    MDLTextureChannelEncodingUint16 = 2,
    MDLTextureChannelEncodingUInt24 = 3,
    MDLTextureChannelEncodingUint24 = 3,
    MDLTextureChannelEncodingUInt32 = 4,
    MDLTextureChannelEncodingUint32 = 4,
    MDLTextureChannelEncodingFloat16 = 0x102,
    MDLTextureChannelEncodingFloat32 = 0x104,
};

/**
 MDLTexture
 @summary a description of texels provided by a texture object.
 
 @discussion A texture optionally generates or loads texels
             through an access to the data property, or one of the other 
             properties, otherwise the texture object is a lightweight descriptor 
             only.
 
 @property data 
           Texel data that will exist when referenced; it may or may not exist 
           before
 @property dimensions
           texel width and height of the texture
 @property rowStride
           The number of bytes from the first texel in a row to the first texel 
           in the next row. A rowStride of zero indicates that interleaved x,y 
           addressing of texels is not possible. This might be the case if the
           texture was compressed in some manner, for example.
 @property channelCount
           The number of channels incoded in a single texel. For example, an RGB 
           texture has 3 channels. All channels must have the same encoding.
 @property channelEncoding
           The encoding of a channel in a single texel.
 @property isCube
           The texture encodes a cube map. If YES, then the layout of the cube 
           map is deduced as a vertical strip if dimension.y is six times 
           dimension.x. Other layouts are possible in the future.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLTexture : NSObject<MDLNamed>

- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 Creates a texture from a source in the main bundle named in a manner matching
  name.
 */
+ (nullable instancetype)textureNamed:(NSString *)name;
+ (nullable instancetype)textureNamed:(NSString *)name bundle:(nullable NSBundle*)bundleOrNil;

/**
  Creates a cube texture map image using 6 faces of the same dimensions, 
  ordered +X,-X,+Y,-Y,+Z,-Z If the data is read back the image will be compacted 
  into a single vertical stack where dimensions.y = 6 * dimensions.x
  isCube will return YES
 
  @param names a collection of mosaiced images in a cross formation or column or row.
  - If 6 individual images are given they are assumed to be in order and will be 
    loaded as is.
  - if 3 images of double height or width are given they will be treated as 
    pairs of + and - in each axis, the order is must be x, then y, then z.
  - if 2 images of triple height or width are given they will be treates as a 
    positive set and a negative set in the order +x, +y, +z, then -x, -y, -z.
  - if a single image is given it will be used without conversion if in column 
    orientation and demosaiced in all other instances.
 */
+ (nullable instancetype)textureCubeWithImagesNamed:(NSArray<NSString *> *)names;
+ (nullable instancetype)textureCubeWithImagesNamed:(NSArray<NSString *> *)names
                                             bundle:(nullable NSBundle*)bundleOrNil;

+ (instancetype)irradianceTextureCubeWithTexture:(MDLTexture*)texture
                                            name:(nullable NSString*)name
                                      dimensions:(vector_int2)dimensions;

+ (instancetype)irradianceTextureCubeWithTexture:(MDLTexture*)texture
                                            name:(nullable NSString*)name
                                      dimensions:(vector_int2)dimensions
                                       roughness:(float)roughness;

- (instancetype)initWithData:(nullable NSData *)pixelData
               topLeftOrigin:(BOOL)topLeftOrigin
                        name:(nullable NSString*)name
                  dimensions:(vector_int2)dimensions
                   rowStride:(NSInteger)rowStride
                channelCount:(NSUInteger)channelCount
             channelEncoding:(MDLTextureChannelEncoding)channelEncoding
                      isCube:(BOOL)isCube NS_DESIGNATED_INITIALIZER;

/** writeToURL, deducing type from path extension */
- (BOOL)writeToURL:(NSURL *)URL;

/** writeToURL using a specific UT type */
- (BOOL)writeToURL:(NSURL *)nsurl type:(CFStringRef)type;

- (nullable CGImageRef)imageFromTexture;

- (nullable NSData *)texelDataWithTopLeftOrigin;
- (nullable NSData *)texelDataWithBottomLeftOrigin;

- (nullable NSData *)texelDataWithTopLeftOriginAtMipLevel:(NSInteger)level create:(BOOL)create;
- (nullable NSData *)texelDataWithBottomLeftOriginAtMipLevel:(NSInteger)level create:(BOOL)create;

@property (nonatomic, readonly) vector_int2 dimensions;
@property (nonatomic, readonly) NSInteger rowStride;
@property (nonatomic, readonly) NSUInteger channelCount;
@property (nonatomic, readonly) NSUInteger mipLevelCount;
@property (nonatomic, readonly) MDLTextureChannelEncoding channelEncoding;
@property (nonatomic) BOOL isCube;

/**
 hasAlphaValues
 @summary
 Can be overridden. If not overridden, hasAlpha will be NO if the texture does not
 have an alpha channel. It wil be YES if the texture has an alpha channel and
 there is at least one non-opaque texel in it.
 */
@property (nonatomic) BOOL hasAlphaValues;

@end

/** 
 MDLURLTexture
 @summary a texture provider initialized with a URL or file path.
 @discussion if any of the properties of the texture, such as data, are referenced,
             then the texture may be loaded, otherwise, the MDLURLTexture is merely
             a lightweight reference to something that could be loaded
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLURLTexture : MDLTexture

- (instancetype)initWithURL:(NSURL*)URL name:(nullable NSString*)name;

@property (nonatomic, copy) NSURL* URL;

@end

/** 
MDLCheckerboardTexture
 A two color checkboard with a certain number of divisions
 
 @discussion the texture will be created if data is referenced, otherwise, this
             object is merely a description
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLCheckerboardTexture : MDLTexture

- (instancetype)initWithDivisions:(float)divisions
                             name:(nullable NSString*)name
                       dimensions:(vector_int2)dimensions
                     channelCount:(int)channelCount
                  channelEncoding:(MDLTextureChannelEncoding)channelEncoding
                           color1:(CGColorRef)color1
                           color2:(CGColorRef)color2;

@property (nonatomic, assign) float divisions;
@property (nullable, nonatomic) CGColorRef color1;
@property (nullable, nonatomic) CGColorRef color2;

@end

/**
MDLSkyCubeTexture
 @summary A physically realistic sky as a cube texture
 
 @property sunElevation A value of zero is at the zenith, 0.5 is at the horizon,
           1.0 is at the nadir. Use in conjunction with turbidity to give a dawn, 
           dusk, or noon look.
 @property turbidity A value of zero simulates the effect of a clear sky, the sun
           will impart very little color to the sky. A value of one simulates a
           great deal of dust and moisture in the sky, and will cause the sun's
           color to spread across the atmosphere.
 @property upperAtmosphereScattering A value of zero will give very dusky colors,
           a value of one will give noon-ish saturated colors.
 @property groundAlbedo controls the amount of light that bounces back up into
           the sky from the ground. A value of zero will yield a clear sky, a
           value of one will reduce the contrast of the sky, making it a bit foggy.
 
 @property horizonElevation If the lower half of the environment is being replaced
           by a color, horizonElevation is angle, in radians, below which the
           replacement should occur. Negative values are below the horizon.

 @property groundColor If this value is set, the environment will be replaced with
           the color below the horizonElevation value.
 
 @property gamma Modifies the amount of gamma correction applied during
           tone mapping.
 @property exposure Modifies the exposure applied during tone mapping.
 @property brighness Modifies the brightness of the image during tone mapping.
 @property contrast Modifies the contrast of the image during tone mapping.
 @property saturation Modifes the saturation of the image during tone mapping.
 @property highDynamicRangeCompression values below the x component of this value 
           are not compressed during tone mapping. Values between the x component
           and y component are compressed to the maximum brightness value during
           tone mapping. Values above the limit are clamped.
 
 @discussion the texture will be created if data is referenced, otherwise, this
 object is merely a description. All parameters have legal values between zero and one.
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLSkyCubeTexture : MDLTexture

- (instancetype)initWithName:(nullable NSString*)name
             channelEncoding:(MDLTextureChannelEncoding)channelEncoding
           textureDimensions:(vector_int2)textureDimensions   // the size of one cube face
                   turbidity:(float)turbidity                 // the clearness of the sky
                sunElevation:(float)sunElevation              // from 0 to 1 zenith to nadir
   upperAtmosphereScattering:(float)upperAtmosphereScattering // how intense the sun looks, 0 to 1
                groundAlbedo:(float)groundAlbedo;             // how much sky color is reflected from the Earth

/**
 Call updateTexture if parameters have been changed and a new sky is required.
 */
- (void)updateTexture;

@property (nonatomic, assign) float turbidity;
@property (nonatomic, assign) float sunElevation;
@property (nonatomic, assign) float upperAtmosphereScattering;
@property (nonatomic, assign) float groundAlbedo;

@property (nonatomic, assign) float horizonElevation;
@property (nullable, nonatomic) CGColorRef groundColor;

@property (nonatomic, assign) float gamma;
@property (nonatomic, assign) float exposure;
@property (nonatomic, assign) float brightness;
@property (nonatomic, assign) float contrast;
@property (nonatomic, assign) float saturation;
@property (nonatomic, assign) vector_float2 highDynamicRangeCompression;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLColorSwatchTexture : MDLTexture

/**
 Create a color gradient from one color temperature to another. The units are 
 blackbody temperatures. The gradient will be vertical.
 */

- (instancetype) initWithColorTemperatureGradientFrom:(float)colorTemperature1
                                   toColorTemperature:(float)colorTemperature2
                                                 name:(nullable NSString*)name
                                    textureDimensions:(vector_int2)textureDimensions;

/**
 Create a color gradient from one color to another. The color will interpolate 
 according to hue. The gradient will be vertical.
 */

- (instancetype) initWithColorGradientFrom:(CGColorRef)color1
                                   toColor:(CGColorRef)color2
                                      name:(nullable NSString*)name
                         textureDimensions:(vector_int2)textureDimensions;

@end


/**
 MDLNoiseTexture
 @summary a noise texture containing vector or scalar noise
 @discussion the texture will be created if data is referenced, otherwise, this
 object is merely a description
 */

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLNoiseTexture : MDLTexture


/**
 Create a four channel texture containing directional noise. The RGBA values in this
 texture can be used as a normal map or as direction possibly with length. XYZ are a 
 three dimensional direction, and A is a magnitude.
 
 @param smoothness how similar neighboring pixels are. A value of zero is like static, 
 one is smooth.
 */
- (instancetype)initVectorNoiseWithSmoothness:(float)smoothness
                                         name:(nullable NSString*)name
                            textureDimensions:(vector_int2)textureDimensions
                              channelEncoding:(MDLTextureChannelEncoding)channelEncoding;

/**
 Create a texture containing colored noise. The noise texture is tileable with itself.
 
 @param smoothness how similar neighboring pixels are. A value of zero is like 
        static, one is smooth.
 @param grayscale if YES, RGB and A will all be the same. If no, RGB and A will 
        all be different. A is not pre-multiplied, because the intent is that if 
        you read a texel in a shader, all four values will be exactly the same 
        value if grayscale, or four different, uncorrelated values if not grayscale.
 */
- (instancetype)initScalarNoiseWithSmoothness:(float)smoothness
                                         name:(nullable NSString*)name
                            textureDimensions:(vector_int2)textureDimensions
                                 channelCount:(int)channelCount
                              channelEncoding:(MDLTextureChannelEncoding)channelEncoding
                                    grayscale:(BOOL)grayscale;

/**
 Create a texture containing cellular noise. 
 
 @param frequency How large the cells will be
 */
- (instancetype)initCellularNoiseWithFrequency:(float)frequency
                                          name:(nullable NSString*)name
                             textureDimensions:(vector_int2)textureDimensions
                               channelEncoding:(MDLTextureChannelEncoding)channelEncoding;

@end

NS_CLASS_AVAILABLE(10_11, 9_0)
MDL_EXPORT
@interface MDLNormalMapTexture : MDLTexture

- (instancetype)initByGeneratingNormalMapWithTexture:(MDLTexture*)sourceTexture
                                                name:(nullable NSString*)name
                                          smoothness:(float)smoothness
                                            contrast:(float)contrast;

@end

NS_ASSUME_NONNULL_END

