//
//  INReservationAction.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INReservationActionType.h>

@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INReservationAction : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithType:(INReservationActionType)type
               validDuration:(INDateComponentsRange *)validDuration
                userActivity:(NSUserActivity *)userActivity NS_DESIGNATED_INITIALIZER;

@property (readonly, assign, NS_NONATOMIC_IOSONLY) INReservationActionType type;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *validDuration;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSUserActivity *userActivity;

@end

NS_ASSUME_NONNULL_END
