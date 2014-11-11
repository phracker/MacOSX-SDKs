/*
	File:		AVAudioMixerNode.h
	Framework:	AVFoundation
	
	Copyright (c) 2014 Apple Inc. All Rights Reserved.
*/

#import <AVFoundation/AVAudioNode.h>
#import <AVFoundation/AVAudioMixing.h>

/*! @class AVAudioMixerNode
	@abstract A node that mixes its inputs to a single output.
	@discussion
		Mixers may have any number of inputs.
	
		The mixer accepts input at any sample rate and efficiently combines sample rate
		conversions. It also accepts any channel count and will correctly upmix or downmix
		to the output channel count.
*/
NS_CLASS_AVAILABLE(10_10, 8_0)
@interface AVAudioMixerNode : AVAudioNode <AVAudioMixing>

/*! @property outputVolume
	@abstract The mixer's output volume.
	@discussion
		This accesses the mixer's output volume (0.0-1.0, inclusive).
*/
@property (nonatomic) float outputVolume;

/*! @property nextAvailableInputBus
	@abstract Find an unused input bus.
	@discussion
		This will find and return the first input bus to which no other node is connected.
*/
@property (nonatomic, readonly) AVAudioNodeBus nextAvailableInputBus;

@end
