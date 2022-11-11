//
//  SNClassificationResult.h
//  SoundAnalysis
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import <SoundAnalysis/SNDefines.h>
#import <SoundAnalysis/SNTypes.h>
#import <SoundAnalysis/SNResult.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @brief The likelihood of a sound belonging to identified class
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNClassification : NSObject

/*!
 @brief The identifier of a classification request. An example classification could be a string like 'laughter' or 'applause'. The string is defined in the model that was used for the classification. Usually these are technical labels that are not localized and not meant to be used directly to be presented to an end user in the UI.
 */
@property (readonly, copy) NSString *identifier;

/*!
 @brief The level of confidence normalized to [0, 1], where 1 is most confident
 */
@property (readonly, assign) double confidence;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/*!
 @brief A result containing the most likely classification candidates in the time range specified
 */
SN_EXPORT API_AVAILABLE(macos(10.15), ios(13.0), tvos(13.0), watchos(6.0))
@interface SNClassificationResult : NSObject <SNResult>

/*!
 @brief All classification candidates, sorted with highest confidence first.
 */
@property (readonly, copy) NSArray<SNClassification *> *classifications;

/*!
 @brief The time range in the client-provided audio stream to which this classification result corresponds
 @discussion Each CMTime contains of a value (audio frame count) and timescale (client sample rate). This enables the client to precisely identify the frame range in the original audio stream to which this result corresponds. Time ranges will often be in the past compared to the frame count of the most recent audio buffer provided to the analyzer, due to the inherent audio buffering operations required to deliver a full block of audio to an MLModel.
 */
@property (readonly) CMTimeRange timeRange;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @brief Retrieves the classification candidate with the specified identifier.
 @param identifier An identifier on which to query for a particular classification candidate. The query will match to any classification candidate whose `identifier` property (see `identifier` property of `SNClassification`) contains a value equal to the provided argument.
 @result The classification candidate which has the specified identifier, if it exists. If no such candidate exists, `nil` will be returned.
 */
- (nullable SNClassification *)classificationForIdentifier:(NSString *)identifier
    API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

@end

NS_ASSUME_NONNULL_END
