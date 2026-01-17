/*
	File:  AVPlayerMediaSelectionCriteria.h
 
	Framework:  AVFoundation
 
	Copyright 2012-2016 Apple Inc. All rights reserved.
 
 */

/*!
	@class		AVPlayerMediaSelectionCriteria
	
	@abstract	The AVPlayerMediaSelectionCriteria class specifies the preferred languages and media characteristics for an AVPlayer instance.
 
	@discussion
		The languages and media characteristics of assets containing media selection options that an AVPlayer instance should attempt to select automatically when preparing and playing items. The languages and media characteristics are specified in the preferred order.
*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVMediaFormat.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.9), ios(7.0), tvos(9.0), watchos(1.0))
@interface AVPlayerMediaSelectionCriteria : NSObject {
@private
	void *_criteriaInternal;
}

/* An NSArray of NSStrings containing language identifiers, in order of desirability, that are preferred for selection. Can be nil. Languages can be indicated via BCP 47 language identifiers or via ISO 639-2/T language codes.
	If no option in a media selection group with any of the preferred languages is available, the default option in the group will be considered the best match.
   When making selections, AVPlayer treats language preferences as criteria that supersede preferred media characteristics.
 */
@property (nonatomic, readonly, nullable) NSArray<NSString *> *preferredLanguages;

/* An NSArray of AVMediaCharacteristics indicating additional media characteristics, in order of desirability, that are preferred when selecting media with the characteristic for which the receiver is set on the AVPlayer as the selection criteria. Can be nil. See AVMediaFormat.h for declarations of media characteristics of the form AVMediaCharacteristic*. For example, desirable characteristics of legible media may include AVMediaCharacteristicTranscribesSpokenDialogForAccessibility and AVMediaCharacteristicDescribesMusicAndSoundForAccessibility. Simiarly, desirable characteristics of audible media may include AVMediaCharacteristicDescribesVideoForAccessibility.
   When making automatic selections, AVPlayer treats preferred media characteristics as criteria that are superseded by language preferences.
 */
@property (nonatomic, readonly, nullable) NSArray<AVMediaCharacteristic> *preferredMediaCharacteristics;

/* An NSArray of AVMediaCharacteristics indicating media characteristics that are considered essential when selecting media with the characteristic for which the receiver is set on the AVPlayer as the selection criteria. Can be nil. See AVMediaFormat.h for declarations of media characteristics of the form AVMediaCharacteristic*. For example, principal characteristics of audible media may include AVMediaCharacteristicIsOriginalContent.
   If no option in a media selection group that possesses all of the principal media characteristics is available, the default option in the group will be considered the best match.
   When making automatic selections, AVPlayer treats principal media characteristics as criteria that supersede both language preferences and preferred media characteristics. Use principal media characteristics with caution; use cases in support of accessibility features are normally satisfied via the use of a combination of language preferences and preferred characteristics, not via the use of principal media characteristics.
 */
@property (nonatomic, readonly, nullable) NSArray<AVMediaCharacteristic> *principalMediaCharacteristics API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

/*!
  @method		initWithPreferredLanguages:preferredMediaCharacteristics:
  @abstract		Creates an instance of AVPlayerMediaSelectionCriteria.
  @param		preferredLanguages
				An NSArray of NSStrings containing language identifiers, in order of desirability, that are preferred for selection. Can be nil.
  @param		preferredMediaCharacteristics
				An NSArray of AVMediaCharacteristics indicating additional media characteristics, in order of desirability, that are preferred when selecting media with the characteristic for which the receiver is set on the AVPlayer as the selection criteria. Can be nil.
  @result		An instance of AVPlayerMediaSelectionCriteria.
*/
- (instancetype)initWithPreferredLanguages:(nullable NSArray<NSString *> *)preferredLanguages preferredMediaCharacteristics:(nullable NSArray<AVMediaCharacteristic> *)preferredMediaCharacteristics;

/*!
  @method		initWithPrincipalMediaCharacteristics:principalMediaCharacteristics:preferredLanguages:preferredMediaCharacteristics:
  @abstract		Creates an instance of AVPlayerMediaSelectionCriteria.
  @param		principalMediaCharacteristics
				An NSArray of AVMediaCharacteristics indicating media characteristics that are considered essential when selecting media with the characteristic for which the receiver is set on the AVPlayer as the selection criteria. Can be nil.
  @param		preferredLanguages
				An NSArray of NSStrings containing language identifiers, in order of desirability, that are preferred for selection. Can be nil.
  @param		preferredMediaCharacteristics
				An NSArray of AVMediaCharacteristics indicating additional media characteristics, in order of desirability, that are preferred when selecting media with the characteristic for which the receiver is set on the AVPlayer as the selection criteria. Can be nil.
   @result		An instance of AVPlayerMediaSelectionCriteria.
   @discussion  Note that even though principal media characteristics, when present, will override language preferences when making a selection within a specific media selection group, language preferences may still pertain to selections in other groups. For example, language preferences for the group that corresponds to the audible characteristic may be considered when choosing whether or not to select non-forced subtitles for translation purposes.
*/
- (instancetype)initWithPrincipalMediaCharacteristics:(nullable NSArray<AVMediaCharacteristic> *)principalMediaCharacteristics preferredLanguages:(nullable NSArray<NSString *> *)preferredLanguages preferredMediaCharacteristics:(nullable NSArray<AVMediaCharacteristic> *)preferredMediaCharacteristics API_AVAILABLE(macos(10.14), ios(12.0), tvos(12.0), watchos(5.0));

@end

NS_ASSUME_NONNULL_END
