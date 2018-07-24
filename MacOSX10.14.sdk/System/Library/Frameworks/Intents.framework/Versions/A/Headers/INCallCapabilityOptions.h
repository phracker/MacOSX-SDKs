//
//  INCallCapabilityOptions.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INCallCapabilityOptions_h
#define INCallCapabilityOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCallCapabilityOptions) {
    INCallCapabilityOptionAudioCall = (1UL << 0),
    INCallCapabilityOptionVideoCall = (1UL << 1),
} API_AVAILABLE(ios(10.0), watchos(3.2), macosx(10.12));

#endif // INCallCapabilityOptions_h
