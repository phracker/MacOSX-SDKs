//
//  INDateSearchType.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INDateSearchType_h
#define INDateSearchType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INDateSearchType) {
    INDateSearchTypeUnknown = 0,
    INDateSearchTypeByDueDate,
    INDateSearchTypeByModifiedDate,
    INDateSearchTypeByCreatedDate,
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

#endif // INDateSearchType_h
