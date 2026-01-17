//
//  VNRecognizeTextRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>


NS_ASSUME_NONNULL_BEGIN

/*!
 @brief    Text recognition level options to favor speed over recognition accuracy. The VNRequestTextRecognitionLevelAccurate is the default option used by VNRecognizeTextRequest.
 */
typedef NS_ENUM(NSInteger, VNRequestTextRecognitionLevel)
{
    VNRequestTextRecognitionLevelAccurate = 0,
    VNRequestTextRecognitionLevelFast
};



/*!
 @brief A request that will detect regions of text and recognize the containing text in an image.
 
 @details This request will generate VNRecognizedTextObservation objects describing the locations of text and the actual text recognized.
 */
API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
@interface VNRecognizeTextRequest : VNImageBasedRequest <VNRequestProgressProviding>

/*!
 @brief Returns all the supported languages for a given text recognition level. Note that a language supported in one recognition level might not be available in another.
 */
+ (nullable NSArray<NSString *> *)supportedRecognitionLanguagesForTextRecognitionLevel:(VNRequestTextRecognitionLevel)recognitionLevel revision:(NSUInteger)requestRevision error:(NSError**)error;

/*!
 @brief Specify the languages used for the detection. The order of the languages in the array defines the order in which languages will be used during the language processing.
 The languages are specified as ISO language codes.
 */
@property (readwrite, nonatomic, copy) NSArray<NSString *> *recognitionLanguages;

/*!
 @brief An array of strings that will be used at the word recognition stage in addition to the recognition languages. The customWords list takes precedence over the standard lexicon.
 */
@property (readwrite, nonatomic, copy) NSArray<NSString *> *customWords;

/*!
 @brief The recognition level selects which techniques will be used during the text recognition. There are trade-offs between performance and accuracy.
 */
@property (readwrite, nonatomic, assign) VNRequestTextRecognitionLevel recognitionLevel;

/*!
 @brief Determines whether language correction should be applied during the recognition process. Disabling this will return the raw recognition results providing performance benefits but less accurate results.
 */
@property (readwrite, nonatomic, assign) BOOL usesLanguageCorrection;

/*
 @brief Minimum height of the text expected to be recognized, relative to the image height (e.g. for half of the image height, use 0.5). Increasing the size will reduce the memory consumption and speed up the recognition with the trade-off that text smaller than the minimum height may not be recognized properly. If the minimum height is set to 0.0 the image gets processed at the highest possible resolution with no downscaling. With that the processing time will be the longest and the memory usage the highest but the smallest technically readable text will be recognized. The default value for this is 0.0.
 */
@property (readwrite, nonatomic, assign) float minimumTextHeight;



@end

API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0))
static const NSUInteger VNRecognizeTextRequestRevision1 = 1;


NS_ASSUME_NONNULL_END
