//
//  INBillType.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
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
} API_AVAILABLE(ios(10.3), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

#endif // INBillType_h
