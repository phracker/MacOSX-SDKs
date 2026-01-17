//
//  INRideFeedbackTypeOptions.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#ifndef INRideFeedbackTypeOptions_h
#define INRideFeedbackTypeOptions_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_OPTIONS(NSUInteger, INRideFeedbackTypeOptions) {
    INRideFeedbackTypeOptionRate = (1UL << 0),
    INRideFeedbackTypeOptionTip = (1UL << 1),
} API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macos, tvos);

#endif // INRideFeedbackTypeOptions_h
