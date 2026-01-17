//
//  INTicketedEvent.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INTicketedEventCategory.h>

@class CLPlacemark;
@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INTicketedEvent : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithCategory:(INTicketedEventCategory)category
                            name:(NSString *)name
                   eventDuration:(INDateComponentsRange *)eventDuration
                        location:(nullable CLPlacemark *)location NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INTicketedEventCategory category;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *name;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *eventDuration;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) CLPlacemark *location;

@end

NS_ASSUME_NONNULL_END
