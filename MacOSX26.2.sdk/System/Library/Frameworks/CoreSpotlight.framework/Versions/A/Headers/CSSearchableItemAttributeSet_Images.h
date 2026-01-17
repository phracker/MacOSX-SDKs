//
//  CSSearchableItemAttributeSet_Images.h
//  CoreSpotlight
//
//  Copyright © 2015 Apple. All rights reserved.
//

#import <CoreSpotlight/CSSearchableItemAttributeSet.h>

NS_ASSUME_NONNULL_BEGIN

CS_AVAILABLE(10_13, 9_0) CS_TVOS_UNAVAILABLE
@interface CSSearchableItemAttributeSet (CSImages)

//The height of the item in pixels (ie Image height or Video frame height)
@property(nullable, strong) NSNumber *pixelHeight;

//The width of the item in pixels (ie Image width or Video frame width)
@property(nullable, strong) NSNumber *pixelWidth;

//The total number of pixels in the item.
@property(nullable, strong) NSNumber *pixelCount;

//What color space model is this item following (For example, "RGB", "CMYK", "YUV", "YCbCr")
@property(nullable, copy) NSString *colorSpace;

//Number of bits per sample
//For example bit depth of an image (8-bit, 16-bit etc..) or bit
//depth per audio sample of uncompressed audio data (8, 16, 24, 32, 64, etc..)
@property(nullable, strong) NSNumber *bitsPerSample;

//Indicates if the flash was used to take the picture.  Should be 1 if flash is on, 0 otherwise.
@property(nullable, strong, getter=isFlashOn) NSNumber *flashOn;

//The actual focal length of the lens in mm.
@property(nullable, strong) NSNumber *focalLength;

//Indicates if the focal length is 35mm.  Should be 1 if true, 0 otherwise
@property(nullable, strong, getter=isFocalLength35mm) NSNumber *focalLength35mm;

//Device make that was used to acquire this item
@property(nullable, copy) NSString *acquisitionMake;

//Device model that was used to acquire this item
@property(nullable, copy) NSString *acquisitionModel;

//The owner of the camera used to capture this image.
@property(nullable, copy) NSString *cameraOwner;

//The model of the lens used to capture this image.
@property(nullable, copy) NSString *lensModel;

//The ISO Speed the camera was set to when the image was taken. Examples are 100, 200, 400, etc.
@property(nullable, strong) NSNumber *ISOSpeed;

//The orientation of the data.  Should be 0 for Landscape or 1 for Portrait.
@property(nullable, strong) NSNumber *orientation;

//The names of the various layers in the file
@property(nullable, copy) NSArray<NSString*> *layerNames;

//The white balance setting of the camera when the image was acquired.  Should be 0 for Auto or 1 for Manual.
@property(nullable, strong) NSNumber *whiteBalance;

//The size of the lens aperture as a log-scale APEX value when the image was acquired.
@property(nullable, strong) NSNumber *aperture;

//Name of the color profile used for the image
@property(nullable, copy) NSString *profileName;

//Resolution width of this image in DPI
@property(nullable, strong) NSNumber *resolutionWidthDPI;

//Resolution height of this image in DPI
@property(nullable, strong) NSNumber *resolutionHeightDPI;

//Mode that was used for the exposure.  Should be 0 for AutoExposure, 1 for Manual, 2 for AutoBracket.
@property(nullable, strong) NSNumber *exposureMode;

//Time that the lens was open during exposure in seconds
@property(nullable, strong) NSNumber *exposureTime;

//The verion of the EXIF header that was used to generate the metadata
@property(nullable, copy) NSString *EXIFVersion;

//The version of GPSInfoIFD header that was used to generate the metadata
@property(nullable, copy) NSString *EXIFGPSVersion;

//Indicates if this image file has an alpha channel.  Should be 0 for no alpha channel, 1 for alpha channel.
@property(nullable, strong) NSNumber *hasAlphaChannel;

//Indicates if red-eye reduction was used to take the picture.  Should be 0 for no red-eye, 1 for red-eye
@property(nullable, strong,getter=isRedEyeOn) NSNumber *redEyeOn;

//The metering mode for the image (Average, Partial, Pattern, ...)
@property(nullable, copy) NSString *meteringMode;

//The smallest F number of the lens. The unit is the APEX
//value. Ordinarily it is given in the range of 00.00 to 99.99.
@property(nullable, strong) NSNumber *maxAperture;

//The focal length of the lens divided by the diameter of the aperture when the image was acquired.
@property(nullable, strong) NSNumber *fNumber;

//The class of the program used by the camera to set exposure when the picture is taken (Manual, Normal, Aperture Priority, ...)
@property(nullable, copy) NSString *exposureProgram;

//The time  of the exposure as a string, e.g. "1/250 seconds".
@property(nullable, copy) NSString *exposureTimeString;

@end

NS_ASSUME_NONNULL_END
