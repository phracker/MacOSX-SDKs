/*
	File:		AVAudioChannelLayout.h
	Framework:	AVFoundation
	
	Copyright (c) 2014 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioTypes.h>
#import <CoreAudio/CoreAudioTypes.h>

/*!
	@class AVAudioChannelLayout
	@abstract A description of the roles of a set of audio channels.
	@discussion
		This object is a thin wrapper for the AudioChannelLayout structure, described
		in <CoreAudio/CoreAudioTypes.h>.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioChannelLayout : NSObject {
@private
	AudioChannelLayoutTag _layoutTag;
	AudioChannelLayout * _layout;
	void *_reserved;
}


/*!	@method initWithLayoutTag:
	@abstract Initialize from a layout tag.
	@param layoutTag
		The tag.
*/
- (instancetype)initWithLayoutTag:(AudioChannelLayoutTag)layoutTag;

/*!	@method initWithLayout:
	@abstract Initialize from an AudioChannelLayout.
	@param layout
		The AudioChannelLayout.
	@discussion
		If the provided layout's tag is kAudioChannelLayoutTag_UseChannelDescriptions, this
		initializer attempts to convert it to a more specific tag.
*/
- (instancetype)initWithLayout:(const AudioChannelLayout *)layout;

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
