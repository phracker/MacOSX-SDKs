//
//  INDateComponentsRange.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class EKRecurrenceRule;
@class INRecurrenceRule;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), macos(11.0), watchos(3.2), tvos(14.0))
@interface INDateComponentsRange : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithStartDateComponents:(nullable NSDateComponents *)startDateComponents
                          endDateComponents:(nullable NSDateComponents *)endDateComponents;

- (instancetype)initWithStartDateComponents:(nullable NSDateComponents *)startDateComponents
                          endDateComponents:(nullable NSDateComponents *)endDateComponents
                             recurrenceRule:(nullable INRecurrenceRule *)recurrenceRule NS_DESIGNATED_INITIALIZER API_AVAILABLE(ios(11.0), watchos(4.0));

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *startDateComponents;

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) NSDateComponents *endDateComponents;

@property (copy, readonly, nullable, NS_NONATOMIC_IOSONLY) INRecurrenceRule *recurrenceRule API_AVAILABLE(ios(11.0), watchos(4.0));

- (instancetype)initWithEKRecurrenceRule:(EKRecurrenceRule *)recurrenceRule API_AVAILABLE(ios(11.0), watchos(4.0));
- (nullable EKRecurrenceRule *)EKRecurrenceRule API_AVAILABLE(ios(11.0), watchos(4.0));

@end

NS_ASSUME_NONNULL_END
