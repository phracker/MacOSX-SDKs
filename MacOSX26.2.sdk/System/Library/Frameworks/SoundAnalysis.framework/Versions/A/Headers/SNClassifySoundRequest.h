//
//  SNClassifySoundRequest.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/CoreML.h>
#import <CoreMedia/CoreMedia.h>

#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNTypes.h>
#import <SoundAnalysis/SNRequest.h>

NS_ASSUME_NONNULL_BEGIN

@class SNTimeDurationConstraint;

/// Configure an analyzer to perform sound classification using the provided MLModel.
///
/// When a new classification result is produced, the results observer will be called with an SNClassificationResult. Audio buffers provided to SNAudioStreamAnalyzer may vary in size, and the analyzer will reblock the audio data to the block size expected by the MLModel. By default, analysis will occur on the first audio channel in the audio stream, and the analyzer will apply sample rate conversion if the provided audio does not match the sample rate required by the MLModel.
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0), visionos(1.0))
@interface SNClassifySoundRequest : NSObject <SNRequest>

/// The overlap factor of the windows of audio data provided to the classifier, if the model operates on fixed audio block sizes.
///
/// When performing audio analysis on fixed audio block sizes, it is common for the analysis windows to overlap by some factor. Without overlapping the analysis windows (when the overlap factor is 0.0), a sound might be split across two analysis windows, which could negatively affect classification performance. Overlapping the analysis windows by 50% ensures each sound will fall near the center of at least one analysis window. The supported range is [0.0, 1.0), and the default value is 0.5. Increasing the overlap factor increases computational complexity, so values greater than 0.5 should be used with care.
@property (readwrite, assign) double overlapFactor;

/// The duration of a single analysis window.
///
/// When performing classification over an audio stream, a classifier computes each classification result based on a single 'analysis window' of audio. Analysis windows are uniformly-sized time intervals, where the size of any given window is considered that window's 'duration'. Some classifiers can operate over analysis windows which conform to one of several different duration options. Larger window durations allow classification to execute less frequently over larger contexts of audio, potentially improving classification performance. Smaller window durations allow classification to execute more frequently over smaller contexts of audio, producing results with sharper time resolution. Depending on the use-case, a larger or smaller window may be preferable. When configuring the window duration, it is important to respect the capabilities of the classifier. A classifier's supported window durations can be discovered using the `windowDurationConstraint` property. If an unsupported window duration is selected, the window duration will be automatically rounded down to the nearest supported value if possible, else rounded up.
@property (readwrite, assign) CMTime windowDuration API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// The constraints governing permitted analysis window durations.
///
/// The analysis window duration is controlled using the `windowDuration` property. If an analysis window duration is selected which does not meet the necessary constraints, it will automatically be adjusted to meet these constraints (see `windowDuration` for more information regarding how this adjustment will be applied).
@property (readonly, strong) SNTimeDurationConstraint *windowDurationConstraint NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// Lists all labels that can be produced by this request.
///
/// - Returns: An array of strings containing all sound identifiers which can be produced by this request.
@property (readonly, copy) NSArray<NSString *> *knownClassifications API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

/// Initializes a sound classification request with the provided MLModel
///
/// - Parameter mlModel: The CoreML audio classification model to be used with this request
///
/// The provided model must accept audio data as input, and output a classification dictionary containing the probability of each category.
- (nullable instancetype)initWithMLModel:(MLModel *)mlModel error:(NSError **)error;

/// Initializes a sound classification request with a known classifier.
///
/// - Parameters:
///
///   - classifierIdentifier: An identifier identifying the particular classifier to use for labeling sounds.
///
///   - error: An output parameter which, in the case of an error, will be populated with details about that error. Upon success, the contents of this output parameter are undefined. Please use the return value of this method to determine whether or not an error occurred before using the value assigned to this output parameter.
///
/// - Returns Upon failure, `nil`; upon success, an `SNClassifySoundRequest` instance which can be added to an analyzer to classify sounds using a recognized classifier.
///
/// This initializer may be used to classify sounds using Apple-provided sound classifiers. Note that Apple may add new classifiers in the future, but it commits to ensuring the consistent performance of existing classifiers.
- (nullable instancetype)initWithClassifierIdentifier:(SNClassifierIdentifier)classifierIdentifier
                                                error:(NSError **)error
    API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0), visionos(1.0));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


NS_ASSUME_NONNULL_END
