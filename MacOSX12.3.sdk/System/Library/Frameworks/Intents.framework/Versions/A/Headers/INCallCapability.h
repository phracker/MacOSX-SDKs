//
//  INCallCapability.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INCallCapability_h
#define INCallCapability_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallCapability) {
    INCallCapabilityUnknown = 0,
    INCallCapabilityAudioCall,
    INCallCapabilityVideoCall,
} API_AVAILABLE(ios(10.0), macos(12.0), watchos(3.2)) API_UNAVAILABLE(tvos);

#endif // INCallCapability_h
