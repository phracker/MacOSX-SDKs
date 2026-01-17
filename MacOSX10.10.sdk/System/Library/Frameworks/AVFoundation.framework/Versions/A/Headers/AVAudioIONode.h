/*
	File:		AVAudioIONode.h
	Framework:	AVFoundation
	
	Copyright (c) 2014 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioNode.h>
#import <AVFoundation/AVAudioMixing.h>
#import <Foundation/NSDate.h>	// for NSTimeInterval
#import <AudioUnit/AudioUnit.h>

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

/*!	@property audioUnit
	@abstract The node's underlying AudioUnit, if any.
	@discussion
		This is only necessary for certain advanced usages.
*/
@property (nonatomic, readonly) AudioUnit audioUnit;
@end


/*! @class AVAudioInputNode
	@abstract A node that connects to the system's audio input.
	@discussion
		This node has one element. The format of the input scope reflects the audio hardware sample
		rate and channel count. The format of the output scope is initially the same as that of the
		input, but you may set it to a different format, in which case the node will convert.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioInputNode : AVAudioIONode <AVAudioMixing>
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
@end
