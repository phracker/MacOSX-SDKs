//
//  INAccountType.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INAccountType_h
#define INAccountType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INAccountType) {
    INAccountTypeUnknown = 0,
    INAccountTypeChecking,
    INAccountTypeCredit,
    INAccountTypeDebit,
    INAccountTypeInvestment,
    INAccountTypeMortgage,
    INAccountTypePrepaid,
    INAccountTypeSaving,
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

#endif // INAccountType_h
