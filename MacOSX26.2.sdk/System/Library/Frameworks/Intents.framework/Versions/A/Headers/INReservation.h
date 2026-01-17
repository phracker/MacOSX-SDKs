//
//  INReservation.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Intents/INReservationStatus.h>

@class INReservationAction;
@class INSpeakableString;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INReservation : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INSpeakableString *itemReference;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *reservationNumber;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSDate *bookingTime;
@property (readonly, assign, NS_NONATOMIC_IOSONLY) INReservationStatus reservationStatus;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *reservationHolderName;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSArray<INReservationAction *> *actions;
@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSURL *URL API_AVAILABLE(ios(14.0), watchos(7.0));

@end

NS_ASSUME_NONNULL_END
