//
//  INMessageAttributeOptions.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INMessageAttributeOptions_h
#define INMessageAttributeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INMessageAttributeOptions) {
    INMessageAttributeOptionRead = (1UL << 0),
    INMessageAttributeOptionUnread = (1UL << 1),
    INMessageAttributeOptionFlagged = (1UL << 2),
    INMessageAttributeOptionUnflagged = (1UL << 3),
} API_AVAILABLE(macosx(10.12), ios(10.0));

#endif // INMessageAttributeOptions_h
