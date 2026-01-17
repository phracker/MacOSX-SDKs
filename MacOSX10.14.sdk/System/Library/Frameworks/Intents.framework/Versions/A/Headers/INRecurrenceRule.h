//
//  INRecurrenceRule.h
//  Intents
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INRecurrenceFrequency.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE(macosx(10.13), ios(11.0), watchos(4.0))
@interface INRecurrenceRule : NSObject <NSCopying, NSSecureCoding>

- (instancetype)initWithInterval:(NSUInteger)interval frequency:(INRecurrenceFrequency)frequency;

@property (readonly) NSUInteger interval;
@property (readonly) INRecurrenceFrequency frequency;

@end
NS_ASSUME_NONNULL_END
