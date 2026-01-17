//
//  SNResult.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNRequest.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief The base protocol to which analysis results conform
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@protocol SNResult <NSObject>
@end

/*!
 @brief The interface through which clients receive the results of an analysis request
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@protocol SNResultsObserving <NSObject>
/*!
 @brief Provides a new analysis result to the client with the specified time range
 @discussion This function will be called each time a new analysis result is available. Different types of analysis may produce results at different rates, spanning different time ranges.
 */
- (void)request:(id<SNRequest>)request didProduceResult:(id<SNResult>)result;

@optional
/*!
 @brief Informs the client of an error produced during analysis
 @discussion If an error is produced by a request, that request will not produce any more results, and is in a terminal state. The request:didFailWithError and requestDidComplete methods are mutually exclusive.
 */
- (void)request:(id<SNRequest>)request didFailWithError:(NSError *)error;

/*!
 @brief Informs the client that the analysis request was completed normally
 @discussion If an analysis request completes normally, that request will not produce any more results, and is in a terminal state. The request:didFailWithError and requestDidComplete methods are mutually exclusive.
 */
- (void)requestDidComplete:(id<SNRequest>)request;

@end

NS_ASSUME_NONNULL_END
