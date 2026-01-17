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

NS_CLASS_AVAILABLE(10_9, 7_0)
@interface AVPlayerMediaSelectionCriteria : NSObject {
@private
	void *_criteriaInternal;
}

/* An NSArray of NSStrings containing language identifiers, in order of desirability, that are preferred for selection. Can be nil. Languages can be indicated via BCP 47 language identifiers or via ISO 639-2/T language codes. If no option with any of the preferred languages is available, a selection will be made according to indications for the default enabling and disabling of media options as stored in the asset.
   When making selections, AVPlayer treats the preference for languages as the paramount criterion.
 */
@property (nonatomic, readonly, nullable) NSArray<NSString *> *preferredLanguages;

/* An NSArray of NSStrings indicating additional media characteristics, in order of desirability, that are preferred when selecting media with the characteristic for which the receiver is set on the AVPlayer as the selection criteria. Can be nil. See AVMediaFormat.h for declarations of media characteristics of the form AVMediaCharacteristic*. For example, desirable characteristics of legible media may include AVMediaCharacteristicTranscribesSpokenDialogForAccessibility and AVMediaCharacteristicDescribesMusicAndSoundForAccessibility. Simiarly, desirable characteristics of audible media may include AVMediaCharacteristicDescribesVideoForAccessibility.
   If no option is found that possesses all of the desired characteristics, the option that best matches the desired characteristics will be selected.
   When making automatic selections, AVPlayer treats the preference for additional media characteristics as a criterion that's secondary to language preference.
 */
@property (nonatomic, readonly, nullable) NSArray<NSString *> *preferredMediaCharacteristics;

/*!
  @method		initWithPreferredLanguages:preferredMediaCharacteristics:
  @abstract		Creates an instance of AVPlayerMediaSelectionCriteria.
  @param		preferredLanguages
				An NSArray of NSStrings containing language identifiers, in order of desirability, that are preferred for selection. Can be nil.
  @param		preferredMediaCharacteristics
				An NSArray of NSStrings indicating additional media characteristics, in order of desirability, that are preferred when selecting media with the characteristic for which the receiver is set on the AVPlayer as the selection criteria. Can be nil.
  @result		An instance of AVPlayerMediaSelectionCriteria.
*/
- (instancetype)initWithPreferredLanguages:(nullable NSArray<NSString *> *)preferredLanguages preferredMediaCharacteristics:(nullable NSArray<AVMediaCharacteristic> *)preferredMediaCharacteristics;

@end

NS_ASSUME_NONNULL_END
