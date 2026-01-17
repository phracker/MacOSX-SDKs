//
//  VNDetectBarcodesRequest.h
//  Vision
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


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
@property (class, nonatomic, readonly, copy) NSArray<VNBarcodeSymbology> *supportedSymbologies API_DEPRECATED_WITH_REPLACEMENT("-supportedSymbologiesAndReturnError:", macos(10.13, 12.0), ios(11.0, 15.0), tvos(11.0, 15.0));


/*!
    @brief Obtain the collection of barcode symbologies that can be recognized by the request in its current configuration.
    
    @discussion    Calling this method could be a potentially expensive operation.

    @return An array of VNBarcodeSymbology objects describing the symbologies recognized by the request in its current configuration.
*/
- (nullable NSArray<VNBarcodeSymbology> *) supportedSymbologiesAndReturnError:(NSError**)error API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));


/*!
	@discussion The collection of barcode symbologies that are to be detected in the image.  The default is to scan for all possible symbologies. Setting a revision on the request will reset the symbologies to all symbologies for the specified revision.
*/
@property (readwrite, nonatomic, copy) NSArray<VNBarcodeSymbology> *symbologies;

/*!
 @discussion An option to coalesce multiple codes if applicable based on the symbology
 */
@property (readwrite, nonatomic) BOOL coalesceCompositeSymbologies API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0));


/*!
	@discussion VNBarcodeObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNBarcodeObservation*>* results;

@end


API_DEPRECATED_WITH_REPLACEMENT("VNDetectBarcodesRequestRevision3", macos(10.14, 14.0), ios(12.0, 17.0), tvos(12.0, 17.0))
static const NSUInteger VNDetectBarcodesRequestRevision1 = 1;

/*
    @brief expands the set of detected symbologies and uses updated detection methods in comparison to revision 1
 */
API_DEPRECATED_WITH_REPLACEMENT("VNDetectBarcodesRequestRevision3", macos(12.0, 15.0), ios(15.0, 18.0), tvos(15.0, 18.0))
static const NSUInteger VNDetectBarcodesRequestRevision2 = 2;

/*
    @brief uses updated detection methods in comparison to revision 1 and 2
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
static const NSUInteger VNDetectBarcodesRequestRevision3 = 3;

/*
    @brief expands set of detected symbologies, improves accuracy, offers supplemental payloads,
    adds inverted color support, and may produce observations outside image bounds in comparison to prior revisions
 */
API_AVAILABLE(macos(14.0), ios(17.0), tvos(17.0))
static const NSUInteger VNDetectBarcodesRequestRevision4 = 4;


NS_ASSUME_NONNULL_END
