//
//  INTrainTrip.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLPlacemark;
@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INTrainTrip : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithProvider:(nullable NSString *)provider
                       trainName:(nullable NSString *)trainName
                     trainNumber:(nullable NSString *)trainNumber
                    tripDuration:(INDateComponentsRange *)tripDuration
        departureStationLocation:(CLPlacemark *)departureStationLocation
               departurePlatform:(nullable NSString *)departurePlatform
          arrivalStationLocation:(CLPlacemark *)arrivalStationLocation
                 arrivalPlatform:(nullable NSString *)arrivalPlatform NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *provider;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *trainName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *trainNumber;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *tripDuration;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *departureStationLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *departurePlatform;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *arrivalStationLocation;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *arrivalPlatform;

@end

NS_ASSUME_NONNULL_END
