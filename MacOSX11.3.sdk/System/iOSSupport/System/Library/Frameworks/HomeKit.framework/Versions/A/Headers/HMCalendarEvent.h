//  HMCalendarEvent.h
//  HomeKit
//
//  Copyright (c) 2017 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>
#import <HomeKit/HMTimeEvent.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a calendar event.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMCalendarEvent : HMTimeEvent <NSCopying, NSMutableCopying>

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief Creates a calendar event
 *
 * @param fireDateComponents The date component that specifies the time when the event is fired
 *
 * @return Instance object representing the event trigger.
 */
- (instancetype)initWithFireDateComponents:(NSDateComponents *)fireDateComponents;


/*!
 * @brief The date component that specifies the time when the event is fired
 */
@property(readonly, strong, nonatomic) NSDateComponents *fireDateComponents;

@end

/*!
 * @brief This class is used to represent a calendar event.
 */
HM_EXTERN API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMMutableCalendarEvent : HMCalendarEvent

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief The date component that specifies the time when the event is fired
 */
@property(readwrite, strong, nonatomic) NSDateComponents *fireDateComponents;

@end

NS_ASSUME_NONNULL_END
