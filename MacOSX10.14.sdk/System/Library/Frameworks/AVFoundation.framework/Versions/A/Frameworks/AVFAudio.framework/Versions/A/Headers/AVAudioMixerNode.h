/*
	File:		AVAudioMixerNode.h
	Framework:	AVFoundation
	
	Copyright (c) 2014-2015 Apple Inc. All Rights Reserved.
*/

#import <AVFAudio/AVAudioNode.h>
#import <AVFAudio/AVAudioMixing.h>

NS_ASSUME_NONNULL_BEGIN

/*! @class AVAudioMixerNode
	@abstract A node that mixes its inputs to a single output.
	@discussion
		Mixers may have any number of inputs.
	
		The mixer accepts input at any sample rate and efficiently combines sample rate
		conversions. It also accepts any channel count and will correctly upmix or downmix
		to the output channel count.
*/
OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioMixerNode : AVAudioNode <AVAudioMixing>

- (instancetype)init NS_DESIGNATED_INITIALIZER;

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

NS_ASSUME_NONNULL_END
