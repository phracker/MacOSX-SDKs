//
//  SNAnalyzer.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNResult.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief Analyzes a stream of audio data and provides analysis results to the client
 @discussion SNAudioStreamAnalyzer should be used to analyze a stream of audio, represented by a sequence of audio buffers over time.
 */

SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNAudioStreamAnalyzer : NSObject

/*!
 @brief Creates a new analyzer
 @param format The format of the audio stream to be analyzed. Only PCM formats are supported.
 */
- (instancetype)initWithFormat:(AVAudioFormat *)format NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @brief Adds a new analysis request to the analyzer
 @param request An audio analysis request to be performed on the audio stream
 @param observer The object that will receive the analysis results for the supplied request. The observer is weakly retained by the analyzer.
 @param error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify nil for this parameter if you do not want the error information.
 @return YES if the request was successfully added, and NO otherwise.
 @discussion Requests can be added while analysis is in progress. If the analyzer cannot perform the requested analysis, an error will be returned. For example, an error could be returned if the request requires a stream format that doesn't match the analyzer's stream format.
 */
- (BOOL)addRequest:(id<SNRequest>)request withObserver:(id<SNResultsObserving>)observer error:(NSError **)error;

/*!
 @brief Removes an existing analysis request from the analyzer
 @param request An audio analysis request to be removed
 @discussion Requests can be removed while analysis is in progress. Once the removeRequest method returns, the previously registered observer will not receive any more callbacks.
 */
- (void)removeRequest:(id<SNRequest>)request;

/*!
 @brief Removes all requests from the analyzer
 */
- (void)removeAllRequests;

/*!
 @brief Provides the next buffer for analysis
 @param audioBuffer The buffer containing the audio to be processed
 @param audioFramePosition The frame position of the data in the buffer
 @discussion The framePosition should be a monotonically increasing sample timestamp. If the sample timeline is detected to be non-continuous, the analyzer's internal state may reset to account for the jump. Some types of audio analysis are performed at a fixed block size, which may differ from the buffer sizes provided for analysis. For this reason, an invocation of analyzeAudioBuffer may cause an analysis request observer to be called zero times, one time, or many times, depending on the relationship between the input buffer size, current analyzer state, and native analysis block size. Any errors produced during analysis will be provided through the request observers. This method may block as a means of indicating backpressure to the caller. These methods are not safe to call from a realtime audio context but may be called from lower priority threads (i.e. AVAudioEngine tap callback or AudioQueue callback).
 */
- (void)analyzeAudioBuffer:(AVAudioBuffer *)audioBuffer atAudioFramePosition:(AVAudioFramePosition)audioFramePosition;

/*!
 @brief Indicates that the audio stream has ended, and no more audio buffers will be analyzed
 @discussion After this method has been called, it is invalid to provide any more audio data for analysis, and any provided buffers will be ignored. This method is useful for types of analysis that may have final results to provide upon the completion of the stream.
 */
- (void)completeAnalysis;

@end


/*!
 @brief Analyzes an audio file and provides analysis results to the client
 */

SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNAudioFileAnalyzer : NSObject

/*!
 @brief Creates a new analyzer
 @param url The url for the audio file to be analyzed
 @param error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify nil for this parameter if you do not want the error information.
 */
- (nullable instancetype)initWithURL:(NSURL *)url error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @brief Adds a new analysis request to the analyzer
 @param request An audio analysis request to be performed on the audio stream
 @param observer The object that will receive the analysis results for the supplied request. The observer is weakly retained by the analyzer.
 @param error On input, a pointer to an error object. If an error occurs, this pointer is set to an actual error object containing the error information. You may specify nil for this parameter if you do not want the error information.
 @return YES if the request was successfully added, and NO otherwise.
 @discussion If addRequest is called while the file is being processed, an error will be returned.
 */
- (BOOL)addRequest:(id<SNRequest>)request withObserver:(id<SNResultsObserving>)observer error:(NSError **)error;

/*!
 @brief Removes an existing analysis request from the analyzer
 @param request An audio analysis request to be removed
 @discussion Requests can be removed while analysis is in progress. Once the removeRequest method returns, the previously registered observer will not receive any more callbacks.
 */
- (void)removeRequest:(id<SNRequest>)request;

/*!
 @brief Removes all requests from the analyzer
 */
- (void)removeAllRequests;

/*!
 @brief Analyzes the audio file synchronously
 @discussion This function executes synchronously. Any errors produced during analysis will flow downstream to the request observers. This method may block for a long period of time, so be careful to ensure this call does not block UI or other important tasks.
 */
- (void)analyze;

/*!
 @brief Analyzes the audio file asynchronously
 @discussion This function executes asynchronously, calling the completion after the entire file has completed analysis. Any errors produced during analysis will flow downstream to the request observers. If the cancelAnalysis method is called, the completionHandler will still be called, but with didReachEndOfFile set to NO.
 */
- (void)analyzeWithCompletionHandler:(void (^)(BOOL didReachEndOfFile))completionHandler;

/*!
 @brief Cancels any in-progress analysis of the audio file
 @discussion This function executes asynchronously, and will trigger the completion handler provided in the analyzeWithCompletionHandler method after the cancellation is complete.
 */
- (void)cancelAnalysis;

@end

NS_ASSUME_NONNULL_END
