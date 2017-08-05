//
//  INCallCapabilityOptions.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INCallCapabilityOptions_h
#define INCallCapabilityOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INCallCapabilityOptions) {
    INCallCapabilityOptionAudioCall = (1UL << 0),
    INCallCapabilityOptionVideoCall = (1UL << 1),
} API_AVAILABLE(macosx(10.12), ios(10.0));

#endif // INCallCapabilityOptions_h
