//
//  INLocationSearchType.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#ifndef INLocationSearchType_h
#define INLocationSearchType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INLocationSearchType) {
    INLocationSearchTypeUnknown = 0,
    INLocationSearchTypeByLocationTrigger,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx);

#endif // INLocationSearchType_h
