/*
	File:		AVAudioChannelLayout.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioTypes.h>
#import <CoreAudio/CoreAudioTypes.h>

NS_ASSUME_NONNULL_BEGIN

/*!
	@class AVAudioChannelLayout
	@abstract A description of the roles of a set of audio channels.
	@discussion
		This object is a thin wrapper for the AudioChannelLayout structure, described
		in <CoreAudio/CoreAudioTypes.h>.
*/
OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioChannelLayout : NSObject <NSSecureCoding> {
@private
	AudioChannelLayoutTag _layoutTag;
	AudioChannelLayout * _layout;
	void *_reserved;
}

- (instancetype)init NS_UNAVAILABLE;

/*!	@method initWithLayoutTag:
	@abstract Initialize from a layout tag.
	@param layoutTag
		The tag.
	@discussion
		Returns nil if the tag is either kAudioChannelLayoutTag_UseChannelDescriptions or
		kAudioChannelLayoutTag_UseChannelBitmap.
*/
- (nullable instancetype)initWithLayoutTag:(AudioChannelLayoutTag)layoutTag;

/*!	@method initWithLayout:
	@abstract Initialize from an AudioChannelLayout.
	@param layout
		The AudioChannelLayout.
	@discussion
		If the provided layout's tag is kAudioChannelLayoutTag_UseChannelDescriptions, this
		initializer attempts to convert it to a more specific tag.
*/
- (instancetype)initWithLayout:(const AudioChannelLayout *)layout NS_DESIGNATED_INITIALIZER;

/*!	@method isEqual:
	@abstract Determine whether another AVAudioChannelLayout is exactly equal to this layout.
	@param object
		The AVAudioChannelLayout to compare against.
	@discussion
		The underlying AudioChannelLayoutTag and AudioChannelLayout are compared for equality.
*/
- (BOOL)isEqual:(id)object;

/*!	@method layoutWithLayoutTag:
	@abstract Create from a layout tag.
*/
+ (instancetype)layoutWithLayoutTag:(AudioChannelLayoutTag)layoutTag;

/*!	@method layoutWithLayout:
	@abstract Create from an AudioChannelLayout
*/
+ (instancetype)layoutWithLayout:(const AudioChannelLayout *)layout;

/*!	@property layoutTag
	@abstract The layout's tag. */
@property (nonatomic, readonly) AudioChannelLayoutTag layoutTag;

/*!	@property layout
	@abstract The underlying AudioChannelLayout. */
@property (nonatomic, readonly) const AudioChannelLayout *layout;

/*! @property channelCount
	@abstract The number of channels of audio data.
*/
@property (nonatomic, readonly) AVAudioChannelCount channelCount;

@end

NS_ASSUME_NONNULL_END

