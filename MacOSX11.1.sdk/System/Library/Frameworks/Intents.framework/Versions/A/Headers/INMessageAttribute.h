//
//  INMessageAttribute.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INMessageAttribute_h
#define INMessageAttribute_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMessageAttribute) {
    INMessageAttributeUnknown = 0,
    INMessageAttributeRead,
    INMessageAttributeUnread,
    INMessageAttributeFlagged,
    INMessageAttributeUnflagged,
    INMessageAttributePlayed API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos),
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

#endif // INMessageAttribute_h
