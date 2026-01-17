//
//  VNRecognizeTextRequest.h
//  Vision
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Vision/VNRequest.h>
#import <Vision/VNObservation.h>


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
+ (nullable NSArray<NSString *> *)supportedRecognitionLanguagesForTextRecognitionLevel:(VNRequestTextRecognitionLevel)recognitionLevel revision:(NSUInteger)requestRevision error:(NSError**)error API_DEPRECATED_WITH_REPLACEMENT("-supportedRecognitionLanguagesAndReturnError:", macos(10.15, 12.0), ios(13.0, 15.0), tvos(13.0, 15.0));


/*!
 @brief Obtain the collection of supported recognition languages.
 @discussion This method will return the collection of all possible language identifiers that are recognized by the target request based on its current state of configuration at the time of the call.

 @param error The address of the variable that will be populated with the error if the call fails.

 @return The collection of language identifiers, or nil if a failure occurs.
 */
- (nullable NSArray<NSString *> *)supportedRecognitionLanguagesAndReturnError:(NSError**)error API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0));


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

/*!
 @brief Language detection will try to automatically identify the script/langauge during the detection and use the appropiate model for recognition and language correction. This can be particularly helpful, if the nature of the content is unkown and with this flag being set it will for instance determine if text is latin vs chinese so you don't have to pick the language model in the first case. But as the language correction cannot always guarantee the correct detection, it is advisable to set the languages, if you have domain knowledge of what language to expect. The default value is NO. Also note that this feature is only available since VNRecognizeTextRequestRevision3 and is a no-op before that.
 */
@property (readwrite, nonatomic, assign) BOOL automaticallyDetectsLanguage API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0));

/*
 @brief Minimum height of the text expected to be recognized, relative to the image height (e.g. for half of the image height, use 0.5). Increasing the size will reduce the memory consumption and speed up the recognition with the trade-off that text smaller than the minimum height may not be recognized properly. If the minimum height is set to 0.0 the image gets processed at the highest possible resolution with no downscaling. With that the processing time will be the longest and the memory usage the highest but the smallest technically readable text will be recognized. The default value for this is 0.0.
 */
@property (readwrite, nonatomic, assign) float minimumTextHeight;


/*!
	@discussion VNRecognizedTextObservation results.
*/
@property (readonly, copy, nullable) NSArray<VNRecognizedTextObservation*>* results;

@end


/*
 @brief VNRecognizeTextRequestRevision1 only supports English
 */
API_DEPRECATED_WITH_REPLACEMENT("VNRecognizeTextRequestRevision3", macos(10.15, 15.0), ios(13.0, 18.0), tvos(13.0, 18.0))
static const NSUInteger VNRecognizeTextRequestRevision1 = 1;

/*
 @brief VNRecognizeTextRequestRevision2 supports English, Chinese, Portuguese, French, Italian, German and Spanish in the accurate recognition level. The fast recognition level supports English, Portuguese, French, Italian, German and Spanish. Best practice is to use supportedRecognitionLanguagesForTextRecognitionLevel to check for supported languages. As the underlying engine has changed from VNRecognizeTextRequestRevision1, results can differ but are generally more accurate. 
 */
API_DEPRECATED_WITH_REPLACEMENT("VNRecognizeTextRequestRevision3", macos(11.0, 15.0), ios(14.0, 18.0), tvos(14.0, 18.0))
static const NSUInteger VNRecognizeTextRequestRevision2 = 2;

/*
 @brief VNRecognizeTextRequestRevision3 supports all languages from previous revisions plus some new languages in the accurate recognition level. It also improves recognition capbilities for rotation and handwriting as well as support for the automatic language detection property. Best practice is to use supportedRecognitionLanguagesForTextRecognitionLevel to check for supported languages. As the underlying engine has changed from previous revsions, results can differ but are generally more accurate.
 */
API_AVAILABLE(macos(13.0), ios(16.0), tvos(16.0))
static const NSUInteger VNRecognizeTextRequestRevision3 = 3;


NS_ASSUME_NONNULL_END
