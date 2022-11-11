//
//  INMediaSortOrder.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INMediaSortOrder_h
#define INMediaSortOrder_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMediaSortOrder) {
    INMediaSortOrderUnknown = 0,
    INMediaSortOrderNewest,
    INMediaSortOrderOldest,
    INMediaSortOrderBest,
    INMediaSortOrderWorst,
    INMediaSortOrderPopular,
    INMediaSortOrderUnpopular,
    INMediaSortOrderTrending,
    INMediaSortOrderRecommended,
} API_AVAILABLE(ios(13.0), watchos(6.0), tvos(14.0)) API_UNAVAILABLE(macos);

#endif // INMediaSortOrder_h
