/*
 * ImageIO - CGImageProperties.h
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __CGIMAGEPROPERTIES__
#define __CGIMAGEPROPERTIES__

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CGBase.h>


/* Properties that, if returned by CGImageSourceCopyProperties or 
 * CGImageSourceCopyPropertiesAtIndex, contain a dictionary of file-format 
 * or metadata-format specific key-values. */

CG_EXTERN const CFStringRef kCGImagePropertyTIFFDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGIFDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyJFIFDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyPNGDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyRawDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyCIFFDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyMakerCanonDictionary;
CG_EXTERN const CFStringRef kCGImagePropertyMakerNikonDictionary;
CG_EXTERN const CFStringRef kCGImagePropertyMakerMinoltaDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyMakerFujiDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyMakerOlympusDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyMakerPentaxDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImageProperty8BIMDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyDNGDictionary;
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxDictionary  __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/** Properties which may be returned by "CGImageSourceCopyProperties".  The
 ** values apply to the container in general but not necessarily to any
 ** individual image that it contains. **/

/* The size of the image file in bytes, if known. If present, the value of
 * this key is a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImagePropertyFileSize  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);


/** Properties which may be returned by "CGImageSourceCopyPropertiesAtIndex".
 ** The values apply to a single image of an image source file. **/

/* The number of pixels in the x- and y-dimensions. The value of these keys 
 * is a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImagePropertyPixelHeight  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyPixelWidth  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The DPI in the x- and y-dimensions, if known. If present, the value of
 * these keys is a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImagePropertyDPIHeight  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyDPIWidth  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The number of bits in each color sample of each pixel. The value of this 
 * key is a CFNumberRef. */

CG_EXTERN const CFStringRef kCGImagePropertyDepth  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The intended display orientation of the image. If present, the value 
 * of this key is a CFNumberRef with the same value as defined by the 
 * TIFF and Exif specifications.  That is:
 *   1  =  0th row is at the top, and 0th column is on the left.  
 *   2  =  0th row is at the top, and 0th column is on the right.  
 *   3  =  0th row is at the bottom, and 0th column is on the right.  
 *   4  =  0th row is at the bottom, and 0th column is on the left.  
 *   5  =  0th row is on the left, and 0th column is the top.  
 *   6  =  0th row is on the right, and 0th column is the top.  
 *   7  =  0th row is on the right, and 0th column is the bottom.  
 *   8  =  0th row is on the left, and 0th column is the bottom.  
 * If not present, a value of 1 is assumed. */ 
 
CG_EXTERN const CFStringRef kCGImagePropertyOrientation  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The value of this key is kCFBooleanTrue if the image contains floating- 
 * point pixel samples */ 
 
CG_EXTERN const CFStringRef kCGImagePropertyIsFloat  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The value of this key is kCFBooleanTrue if the image contains indexed 
 * (a.k.a. paletted) pixel samples */ 
 
CG_EXTERN const CFStringRef kCGImagePropertyIsIndexed  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The value of this key is kCFBooleanTrue if the image contains an alpha 
 * (a.k.a. coverage) channel */ 
 
CG_EXTERN const CFStringRef kCGImagePropertyHasAlpha  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The color model of the image such as "RGB", "CMYK", "Gray", or "Lab".
 * The value of this key is CFStringRef. */ 

CG_EXTERN const CFStringRef kCGImagePropertyColorModel  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* The name of the optional ICC profile embedded in the image, if known.  
 * If present, the value of this key is a CFStringRef. */

CG_EXTERN const CFStringRef kCGImagePropertyProfileName  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);


/* Possible values for kCGImagePropertyColorModel property */

CG_EXTERN const CFStringRef kCGImagePropertyColorModelRGB  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyColorModelGray  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyColorModelCMYK  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyColorModelLab  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);


/* Possible keys for kCGImagePropertyTIFFDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyTIFFCompression  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFPhotometricInterpretation  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFDocumentName  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFImageDescription  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFMake  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFModel  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFOrientation  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFXResolution  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFYResolution  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFResolutionUnit  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFSoftware  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFTransferFunction  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFDateTime  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFArtist  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFHostComputer  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFCopyright  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFWhitePoint  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyTIFFPrimaryChromaticities  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Possible keys for kCGImagePropertyJFIFDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyJFIFVersion  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyJFIFXDensity  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyJFIFYDensity  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyJFIFDensityUnit  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyJFIFIsProgressive  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);


/* Possible keys for kCGImagePropertyExifDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyExifExposureTime  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFNumber  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifExposureProgram  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSpectralSensitivity  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifISOSpeedRatings  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifOECF  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifVersion  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifDateTimeOriginal  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifDateTimeDigitized  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifComponentsConfiguration  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifCompressedBitsPerPixel  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifShutterSpeedValue  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifApertureValue  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifBrightnessValue  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifExposureBiasValue  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifMaxApertureValue  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSubjectDistance  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifMeteringMode  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifLightSource  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFlash  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalLength  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSubjectArea  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifMakerNote  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifUserComment  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSubsecTime  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeOrginal  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSubsecTimeDigitized  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFlashPixVersion  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifColorSpace  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifPixelXDimension  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifPixelYDimension  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifRelatedSoundFile  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFlashEnergy  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSpatialFrequencyResponse  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneXResolution  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneYResolution  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalPlaneResolutionUnit  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSubjectLocation  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifExposureIndex  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSensingMethod  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFileSource  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSceneType  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifCFAPattern  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifCustomRendered  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifExposureMode  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifWhiteBalance  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifDigitalZoomRatio  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifFocalLenIn35mmFilm  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSceneCaptureType  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifGainControl  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifContrast  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSaturation  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSharpness  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifDeviceSettingDescription  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifSubjectDistRange  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifImageUniqueID  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifGamma  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Possible keys for kCGImagePropertyExifAuxDictionary */
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxLensInfo	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxLensModel  __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxSerialNumber	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxLensID	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxLensSerialNumber	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxImageNumber	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxFlashCompensation	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxOwnerName	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyExifAuxFirmware	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);

/* Possible keys for kCGImagePropertyGIFDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyGIFLoopCount  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGIFDelayTime  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGIFImageColorMap  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGIFHasGlobalColorMap  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGIFUnclampedDelayTime  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

/* Possible keys for kCGImagePropertyPNGDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyPNGGamma  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyPNGInterlaceType  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyPNGXPixelsPerMeter  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyPNGYPixelsPerMeter  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyPNGsRGBIntent  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyPNGChromaticities  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Possible keys for kCGImagePropertyGPSDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyGPSVersion  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSLatitudeRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSLatitude  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSLongitudeRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSLongitude  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSAltitudeRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSAltitude  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSTimeStamp  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSSatellites  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSStatus  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSMeasureMode  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDOP  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSSpeedRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSSpeed  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSTrackRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSTrack  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSImgDirectionRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSImgDirection  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSMapDatum  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestLatitudeRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestLatitude  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestLongitudeRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestLongitude  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestBearingRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestBearing  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestDistanceRef  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDestDistance  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSProcessingMethod  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSAreaInformation  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDateStamp  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyGPSDifferental  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);

/* Possible keys for kCGImagePropertyIPTCDictionary */

CG_EXTERN const CFStringRef kCGImagePropertyIPTCObjectTypeReference  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCObjectAttributeReference  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCObjectName  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCEditStatus  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCEditorialUpdate  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCUrgency  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSubjectReference  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCategory  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSupplementalCategory  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCFixtureIdentifier  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCKeywords  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContentLocationCode  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContentLocationName  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReleaseDate  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReleaseTime  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCExpirationDate  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCExpirationTime  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSpecialInstructions  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCActionAdvised  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceService  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceDate  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCReferenceNumber  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCDateCreated  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCTimeCreated  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCDigitalCreationDate  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCDigitalCreationTime  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCOriginatingProgram  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCProgramVersion  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCObjectCycle  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCByline  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCBylineTitle  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCity  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSubLocation  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCProvinceState  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCountryPrimaryLocationCode  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCountryPrimaryLocationName  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCOriginalTransmissionReference  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCHeadline  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCredit  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCSource  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCopyrightNotice  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContact  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCaptionAbstract  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCWriterEditor  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCImageType  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCImageOrientation  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCLanguageIdentifier  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCStarRating  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCCreatorContactInfo  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);	// IPTC Core
CG_EXTERN const CFStringRef kCGImagePropertyIPTCRightsUsageTerms  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);	// IPTC Core
CG_EXTERN const CFStringRef kCGImagePropertyIPTCScene  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);				// IPTC Core

/* Possible keys for kCGImagePropertyIPTCCreatorContactInfo dictionary (part of IPTC Core - above) */

CG_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoCity  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoCountry  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoAddress  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoPostalCode  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoStateProvince  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoEmails  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoPhones  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);
CG_EXTERN const CFStringRef kCGImagePropertyIPTCContactInfoWebURLs  __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_NA);

/* Possible keys for kCGImageProperty8BIMDictionary */

CG_EXTERN const CFStringRef  kCGImageProperty8BIMLayerNames;


/* Possible keys for kCGImagePropertyDNGDictionary */

CG_EXTERN const CFStringRef  kCGImagePropertyDNGVersion;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGBackwardVersion;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGUniqueCameraModel;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGLocalizedCameraModel;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGCameraSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyDNGLensInfo;


/* Possible keys for kCGImagePropertyCIFFDictionary */

CG_EXTERN const CFStringRef  kCGImagePropertyCIFFDescription;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFFirmware;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFOwnerName;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFImageName;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFImageFileName;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFReleaseMethod;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFReleaseTiming;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFRecordID;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFSelfTimingTime;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFCameraSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFImageSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFContinuousDrive;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFFocusMode;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFMeteringMode;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFShootingMode;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFLensModel;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFLensMaxMM;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFLensMinMM;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFWhiteBalanceIndex;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFFlashExposureComp;
CG_EXTERN const CFStringRef  kCGImagePropertyCIFFMeasuredEV;


/* Possible keys for kCGImagePropertyMakerNikonDictionary */

CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonISOSetting;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonColorMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonQuality;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonWhiteBalanceMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonSharpenMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFocusMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFlashSetting;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonISOSelection;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFlashExposureComp;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonImageAdjustment;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensAdapter;
CG_EXTERN const CFStringRef	 kCGImagePropertyMakerNikonLensType;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonLensInfo;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonFocusDistance;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonDigitalZoom;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonShootingMode;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonCameraSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerNikonShutterCount;

/* Possible keys for kCGImagePropertyMakerCanonDictionary */

CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonOwnerName;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonCameraSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonImageSerialNumber;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonFlashExposureComp;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonContinuousDrive;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonLensModel;
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonFirmware	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);
CG_EXTERN const CFStringRef  kCGImagePropertyMakerCanonAspectRatioInfo	__OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


#endif	/* __CGIMAGEPROPERTIES__ */
