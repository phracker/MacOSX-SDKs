//
//  INCallCapability.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INCallCapability_h
#define INCallCapability_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallCapability) {
    INCallCapabilityUnknown = 0,
    INCallCapabilityAudioCall,
    INCallCapabilityVideoCall,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

#endif // INCallCapability_h
