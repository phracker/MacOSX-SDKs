//
//  INVisualCodeType.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#ifndef INVisualCodeType_h
#define INVisualCodeType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INVisualCodeType) {
    INVisualCodeTypeUnknown = 0,
    INVisualCodeTypeContact,
    INVisualCodeTypeRequestPayment,
    INVisualCodeTypeSendPayment,
    INVisualCodeTypeTransit API_AVAILABLE(ios(12.0), watchos(5.0)),
    INVisualCodeTypeBus API_AVAILABLE(ios(12.0), watchos(5.0)),
    INVisualCodeTypeSubway API_AVAILABLE(ios(12.0), watchos(5.0)),
} API_DEPRECATED("INVisualCodeType is deprecated. There is no replacement.", ios(11.0, 15.0), watchos(4.0, 8.0)) API_UNAVAILABLE(macos, tvos);

#endif // INVisualCodeType_h
