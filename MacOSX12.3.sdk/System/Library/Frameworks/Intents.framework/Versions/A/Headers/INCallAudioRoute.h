//
//  INCallAudioRoute.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INCallAudioRoute_h
#define INCallAudioRoute_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallAudioRoute) {
    INCallAudioRouteUnknown = 0,
    INCallAudioRouteSpeakerphoneAudioRoute,
    INCallAudioRouteBluetoothAudioRoute,
} API_AVAILABLE(ios(13.0), macos(12.0), watchos(6.0)) API_UNAVAILABLE(tvos);

#endif // INCallAudioRoute_h
