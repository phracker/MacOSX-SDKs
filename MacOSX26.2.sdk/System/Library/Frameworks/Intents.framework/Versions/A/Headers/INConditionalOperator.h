//
//  INConditionalOperator.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#ifndef INConditionalOperator_h
#define INConditionalOperator_h

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, INConditionalOperator) {
    INConditionalOperatorAll = 0,
    INConditionalOperatorAny,
    INConditionalOperatorNone,
} API_AVAILABLE(ios(10.0), watchos(3.2)) API_UNAVAILABLE(macos, tvos);

#endif // INConditionalOperator_h
