//
//  SNClassifySoundRequest.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/CoreML.h>
#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNRequest.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief Configure an analyzer to perform sound classification using the provided MLModel.
 @discussion When a new classification result is produced, the results observer will be called with an SNClassificationResult. Audio buffers provided to SNAudioStreamAnalyzer may vary in size, and the analyzer will reblock the audio data to the block size expected by the MLModel. By default, analysis will occur on the first audio channel in the audio stream, and the analyzer will apply sample rate conversion if the provided audio does not match the sample rate required by the MLModel.
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNClassifySoundRequest : NSObject <SNRequest>

/*!
 @brief The overlap factor of the windows of audio data provided to the classifier, if the model operates on fixed audio block sizes.
 @discussion When performing audio analysis on fixed audio block sizes, it is common for the analysis windows to overlap by some factor. Without overlapping the analysis windows (when the overlap factor is 0.0), a sound might be split across two analysis windows, which could negatively affect classification performance. Overlapping the analysis windows by 50% ensures each sound will fall near the center of at least one analysis window. The supported range is [0.0, 1.0), and the default value is 0.5. Increasing the overlap factor increases computational complexity, so values greater than 0.5 should be used with care.
 */
@property (readwrite) double overlapFactor;

/*!
 @brief Initializes a sound classification request with the provided MLModel
 @param mlModel The CoreML audio classification model to be used with this request
 @discussion The provided model must accept audio data as input, and output a classification dictionary containing the probability of each category.
 */
- (nullable instancetype)initWithMLModel:(MLModel *)mlModel error:(NSError **)error;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
