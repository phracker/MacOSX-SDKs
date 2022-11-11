//
//  VNTypes.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Vision/VNDefines.h>


typedef float VNConfidence;

typedef float VNAspectRatio;

typedef float VNDegrees;

typedef NS_ENUM(NSUInteger, VNImageCropAndScaleOption)
{
    VNImageCropAndScaleOptionCenterCrop = 0,  // scale image maintaining aspect ratio to fit on the short side and crop centered on the long side
    VNImageCropAndScaleOptionScaleFit = 1,    // scale to size required by algorithm
    VNImageCropAndScaleOptionScaleFill = 2
};

/*!
	@brief Barcode symbologies that are supported by the Vision framework.
	
	@discussion The actual set of barcode symbologies that can actually be recognized by a specific version of the Vision framework should be determined by using the VNRequestNameSupportedBarcodeSymbologies request.
*/
typedef NSString *VNBarcodeSymbology NS_STRING_ENUM;

VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyAztec NS_SWIFT_NAME(aztec) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39 NS_SWIFT_NAME(code39) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39Checksum NS_SWIFT_NAME(code39Checksum) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39FullASCII NS_SWIFT_NAME(code39FullASCII) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode39FullASCIIChecksum NS_SWIFT_NAME(code39FullASCIIChecksum) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode93 NS_SWIFT_NAME(code93) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode93i NS_SWIFT_NAME(code93i) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCode128 NS_SWIFT_NAME(code128) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyDataMatrix NS_SWIFT_NAME(dataMatrix) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyEAN8 NS_SWIFT_NAME(ean8) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyEAN13 NS_SWIFT_NAME(ean13) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyI2of5 NS_SWIFT_NAME(i2of5) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyI2of5Checksum NS_SWIFT_NAME(i2of5Checksum) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyITF14 NS_SWIFT_NAME(itf14) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyPDF417 NS_SWIFT_NAME(pdf417) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyQR NS_SWIFT_NAME(qr) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyUPCE NS_SWIFT_NAME(upce) API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0));
// Revision 2
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyCodabar NS_SWIFT_NAME(codabar) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyGS1DataBar NS_SWIFT_NAME(gs1DataBar) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyGS1DataBarExpanded NS_SWIFT_NAME(gs1DataBarExpanded) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyGS1DataBarLimited NS_SWIFT_NAME(gs1DataBarLimited) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyMicroPDF417 NS_SWIFT_NAME(microPDF417) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));
VN_EXPORT VNBarcodeSymbology const VNBarcodeSymbologyMicroQR NS_SWIFT_NAME(microQR) API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));


API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
typedef NS_ENUM(NSUInteger, VNElementType)
{
	VNElementTypeUnknown = 0,
	VNElementTypeFloat   = 1,		// IEEE 754 single-precision floating point value
	VNElementTypeDouble  = 2,		// IEEE 754 double-precision floating point value
};




typedef NSString* VNVideoProcessingOption NS_STRING_ENUM API_DEPRECATED_WITH_REPLACEMENT("VNVideoProcessorRequestProcessingOptions", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNVideoProcessingOption const VNVideoProcessingOptionFrameCadence API_DEPRECATED_WITH_REPLACEMENT("VNVideoProcessorRequestProcessingOptions", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));
VN_EXPORT VNVideoProcessingOption const VNVideoProcessingOptionTimeInterval API_DEPRECATED_WITH_REPLACEMENT("VNVideoProcessorRequestProcessingOptions", macos(11.0, 11.0), ios(14.0, 14.0), tvos(14.0, 14.0));


API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0))
typedef NS_CLOSED_ENUM(NSInteger, VNChirality)
{
    VNChiralityUnknown = 0,
    VNChiralityLeft = -1,
    VNChiralityRight = 1
};
