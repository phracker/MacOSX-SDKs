//
//  INRecurrenceRule.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INRecurrenceFrequency.h>
#import <Intents/INDayOfWeekOptions.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(ios(11.0), watchos(4.0))
API_UNAVAILABLE(macos, tvos)
@interface INRecurrenceRule : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithInterval:(NSUInteger)interval frequency:(INRecurrenceFrequency)frequency;
- (instancetype)initWithInterval:(NSUInteger)interval frequency:(INRecurrenceFrequency)frequency weeklyRecurrenceDays:(INDayOfWeekOptions)weeklyRecurrenceDays NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);

@property (nonatomic, readonly) NSUInteger interval;
@property (nonatomic, readonly) INRecurrenceFrequency frequency;
@property (nonatomic, readonly) INDayOfWeekOptions weeklyRecurrenceDays API_AVAILABLE(ios(14.0), watchos(7.0)) API_UNAVAILABLE(macos, tvos);

@end
NS_ASSUME_NONNULL_END
