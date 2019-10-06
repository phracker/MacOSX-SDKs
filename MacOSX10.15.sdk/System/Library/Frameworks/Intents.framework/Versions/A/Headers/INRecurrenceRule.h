//
//  INRecurrenceRule.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INRecurrenceFrequency.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(ios(11.0), watchos(4.0)) API_UNAVAILABLE(macosx)
@interface INRecurrenceRule : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithInterval:(NSUInteger)interval frequency:(INRecurrenceFrequency)frequency;

@property (nonatomic, readonly) NSUInteger interval;
@property (nonatomic, readonly) INRecurrenceFrequency frequency;

@end
NS_ASSUME_NONNULL_END
