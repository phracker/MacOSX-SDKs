//
//  INCarAudioSource.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INCarAudioSource_h
#define INCarAudioSource_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCarAudioSource) {
    INCarAudioSourceUnknown = 0,
    INCarAudioSourceCarPlay,
    INCarAudioSourceiPod,
    INCarAudioSourceRadio,
    INCarAudioSourceBluetooth,
    INCarAudioSourceAUX,
    INCarAudioSourceUSB,
    INCarAudioSourceMemoryCard,
    INCarAudioSourceOpticalDrive,
    INCarAudioSourceHardDrive,
} API_DEPRECATED("INCarAudioSource is deprecated. There is no replacement.", ios(10.0, 15.0)) API_UNAVAILABLE(macos, watchos, tvos);

#endif // INCarAudioSource_h
