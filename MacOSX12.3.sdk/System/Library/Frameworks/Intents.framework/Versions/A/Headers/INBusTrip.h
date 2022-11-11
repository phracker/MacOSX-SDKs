//
//  INBusTrip.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLPlacemark;
@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), macos(11.0), watchos(7.0))
API_UNAVAILABLE(tvos)
@interface INBusTrip : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithProvider:(nullable NSString *)provider
                         busName:(nullable NSString *)busName
                       busNumber:(nullable NSString *)busNumber
                    tripDuration:(INDateComponentsRange *)tripDuration
        departureBusStopLocation:(CLPlacemark *)departureBusStopLocation
               departurePlatform:(nullable NSString *)departurePlatform
          arrivalBusStopLocation:(CLPlacemark *)arrivalBusStopLocation
                 arrivalPlatform:(nullable NSString *)arrivalPlatform NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *provider;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *busName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *busNumber;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *tripDuration;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *departureBusStopLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *departurePlatform;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *arrivalBusStopLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *arrivalPlatform;

@end

NS_ASSUME_NONNULL_END
