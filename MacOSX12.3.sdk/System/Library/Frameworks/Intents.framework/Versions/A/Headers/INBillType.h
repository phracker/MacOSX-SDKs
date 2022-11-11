//
//  INBillType.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INBillType_h
#define INBillType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INBillType) {
    INBillTypeUnknown = 0,
    INBillTypeAutoInsurance,
    INBillTypeCable,
    INBillTypeCarLease,
    INBillTypeCarLoan,
    INBillTypeCreditCard,
    INBillTypeElectricity,
    INBillTypeGas,
    INBillTypeGarbageAndRecycling,
    INBillTypeHealthInsurance,
    INBillTypeHomeInsurance,
    INBillTypeInternet,
    INBillTypeLifeInsurance,
    INBillTypeMortgage,
    INBillTypeMusicStreaming,
    INBillTypePhone,
    INBillTypeRent,
    INBillTypeSewer,
    INBillTypeStudentLoan,
    INBillTypeTrafficTicket,
    INBillTypeTuition,
    INBillTypeUtilities,
    INBillTypeWater,
} API_DEPRECATED("INBillType is deprecated. There is no replacement.", ios(10.3, 15.0), watchos(3.2, 8.0)) API_UNAVAILABLE(macos, tvos);

#endif // INBillType_h
