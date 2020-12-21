//
//  INAmountType.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INAmountType_h
#define INAmountType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INAmountType) {
    INAmountTypeUnknown = 0,
    INAmountTypeMinimumDue,
    INAmountTypeAmountDue,
    INAmountTypeCurrentBalance,
    INAmountTypeMaximumTransferAmount API_AVAILABLE(ios(11.0), watchos(4.0)),
    INAmountTypeMinimumTransferAmount API_AVAILABLE(ios(11.0), watchos(4.0)),
    INAmountTypeStatementBalance API_AVAILABLE(ios(11.0), watchos(4.0)),
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

#endif // INAmountType_h
