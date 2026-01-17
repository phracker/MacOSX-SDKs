//
//  INCallAudioRoute.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INCallAudioRoute_h
#define INCallAudioRoute_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallAudioRoute) {
    INCallAudioRouteUnknown = 0,
    INCallAudioRouteSpeakerphoneAudioRoute,
    INCallAudioRouteBluetoothAudioRoute,
} API_AVAILABLE(ios(13.0), watchos(6.0)) API_UNAVAILABLE(macos, tvos);

#endif // INCallAudioRoute_h
