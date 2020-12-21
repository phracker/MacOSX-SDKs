//
//  AVFAudio.h
//  Copyright © 2015 Apple. All rights reserved.
//

#import <AVFAudio/AVAudioBuffer.h>
#import <AVFAudio/AVAudioChannelLayout.h>
#import <AVFAudio/AVAudioConnectionPoint.h>
#import <AVFAudio/AVAudioConverter.h>
#import <AVFAudio/AVAudioEngine.h>
#import <AVFAudio/AVAudioEnvironmentNode.h>
#import <AVFAudio/AVAudioFile.h>
#import <AVFAudio/AVAudioFormat.h>
#import <AVFAudio/AVAudioIONode.h>
#import <AVFAudio/AVAudioMixerNode.h>
#import <AVFAudio/AVAudioMixing.h>
#import <AVFAudio/AVAudioNode.h>
#import <AVFAudio/AVAudioPlayer.h>
#import <AVFAudio/AVAudioPlayerNode.h>
#if !0
#import <AVFAudio/AVAudioRecorder.h>
#endif
#import <AVFAudio/AVAudioSequencer.h>
#import <AVFAudio/AVAudioSettings.h>
#import <AVFAudio/AVAudioSinkNode.h>
#import <AVFAudio/AVAudioSourceNode.h>
#import <AVFAudio/AVAudioTime.h>
#import <AVFAudio/AVAudioTypes.h>
#import <AVFAudio/AVAudioUnit.h>
#import <AVFAudio/AVAudioUnitComponent.h>
#import <AVFAudio/AVAudioUnitDelay.h>
#import <AVFAudio/AVAudioUnitDistortion.h>
#import <AVFAudio/AVAudioUnitEQ.h>
#import <AVFAudio/AVAudioUnitEffect.h>
#import <AVFAudio/AVAudioUnitGenerator.h>
#import <AVFAudio/AVAudioUnitMIDIInstrument.h>
#import <AVFAudio/AVAudioUnitReverb.h>
#import <AVFAudio/AVAudioUnitSampler.h>
#import <AVFAudio/AVAudioUnitTimeEffect.h>
#import <AVFAudio/AVAudioUnitTimePitch.h>
#import <AVFAudio/AVAudioUnitVarispeed.h>
#import <AVFAudio/AVMIDIPlayer.h>

#if !0
#import <AVFAudio/AVSpeechSynthesis.h>
#endif

#if TARGET_OS_IPHONE && !0
#import <AVFAudio/AVAudioSession.h>
#import <AVFAudio/AVAudioSessionRoute.h>
#import <AVFAudio/AVAudioSessionTypes.h>
#import <AVFAudio/AVAudioSessionDeprecated.h>
#endif

#if TARGET_OS_OSX
#import <AVFAudio/AVAudioRoutingArbiter.h>
#endif

