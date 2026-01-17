//
//  INConditionalOperator.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#ifndef INConditionalOperator_h
#define INConditionalOperator_h

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, INConditionalOperator) {
    INConditionalOperatorAll = 0,
    INConditionalOperatorAny,
    INConditionalOperatorNone,
} API_AVAILABLE(macosx(10.12), ios(10.0));

#endif // INConditionalOperator_h
