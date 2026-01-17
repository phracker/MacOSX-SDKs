/*
	File:		AVAudioIONode.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioNode.h>
#import <AVFAudio/AVAudioMixing.h>
#if __has_include(<AudioUnit/AudioUnit.h>)
#define AVAUDIOIONODE_HAVE_AUDIOUNIT 1
#import <AudioUnit/AudioUnit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

/*!	@class AVAudioIONode
	@abstract Base class for a node that connects to the system's audio input or output.
	@discussion
		On OS X, AVAudioInputNode and AVAudioOutputNode communicate with the system's default
		input and output devices. On iOS, they communicate with the devices appropriate to
		the app's AVAudioSession category and other configuration, also considering the user's
		actions such as connecting/disconnecting external devices.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioIONode : AVAudioNode

/*!	@property presentationLatency
	@abstract The presentation, or hardware, latency.
	@discussion
		This corresponds to kAudioDevicePropertyLatency and kAudioStreamPropertyLatency.
		See <CoreAudio/AudioHardwareBase.h>.
*/
@property (nonatomic, readonly) NSTimeInterval presentationLatency;

#if AVAUDIOIONODE_HAVE_AUDIOUNIT
/*!	@property audioUnit
	@abstract The node's underlying AudioUnit, if any.
	@discussion
		This is only necessary for certain advanced usages.
*/
@property (nonatomic, readonly, nullable) AudioUnit audioUnit;
#endif

@end


/*! @class AVAudioInputNode
	@abstract A node that connects to the system's audio input.
	@discussion
		This node has one element. The format of the input scope reflects the audio hardware sample
		rate and channel count. The format of the output scope is initially the same as that of the
		input, but you may set it to a different format, in which case the node will convert.
*/


NS_CLASS_AVAILABLE(10_10, 8_0) __TVOS_PROHIBITED __WATCHOS_PROHIBITED
@interface AVAudioInputNode : AVAudioIONode <AVAudioMixing>
- (instancetype)init NS_UNAVAILABLE; // create instances via -[AVAudioEngine inputNode].
@end

/*! @class AVAudioOutputNode
	@abstract A node that connects to the system's audio input.
	@discussion
		This node has one element. The format of the output scope reflects the audio hardware sample
		rate and channel count. The format of the input scope is initially the same as that of the
		output, but you may set it to a different format, in which case the node will convert.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioOutputNode : AVAudioIONode
- (instancetype)init NS_UNAVAILABLE; // create instances via -[AVAudioEngine outputNode].
@end

NS_ASSUME_NONNULL_END
