//
//  INTemporalEventTrigger.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macosx)
@interface INTemporalEventTrigger : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithDateComponentsRange:(INDateComponentsRange *)dateComponentsRange NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *dateComponentsRange;

@end

NS_ASSUME_NONNULL_END
