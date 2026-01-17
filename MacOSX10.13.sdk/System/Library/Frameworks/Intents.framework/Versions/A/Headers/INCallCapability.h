//
//  INCallCapability.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallCapability_h
#define INCallCapability_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INCallCapability) {
    INCallCapabilityUnknown = 0,
    INCallCapabilityAudioCall,
    INCallCapabilityVideoCall,
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INCallCapability_h
