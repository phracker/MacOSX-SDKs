//
//  VNDetectBarcodesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNTypes.h>


NS_ASSUME_NONNULL_BEGIN


/*!
	@brief A request that detects barcodes in an image.
	
	@discussion This request will return zero or more VNBarcodeObservation objects objects which describe the barcodes detected in an image.
*/
API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0))
@interface VNDetectBarcodesRequest : VNImageBasedRequest

/*!
	@brief Obtain the collection of barcode symbologies currently recognized by the Vision framework.
	
	@discussion	Calling this method could be a potentially expensive operation.

	@return An array of VNBarcodeSymbology objects describing the symbologies currently supported by the Vision framework.
*/
@property (class, nonatomic, readonly, copy) NSArray<VNBarcodeSymbology> *supportedSymbologies;


/*!
	@discussion The collection of barcode symbologies that are to be detected in the image.  The default is to scan for all possible symbologies.
*/
@property (readwrite, nonatomic, copy) NSArray<VNBarcodeSymbology> *symbologies;

@end


API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0))
static const NSUInteger VNDetectBarcodesRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
