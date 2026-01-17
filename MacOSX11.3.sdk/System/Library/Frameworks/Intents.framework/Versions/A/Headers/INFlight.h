//
//  INFlight.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INAirline;
@class INAirportGate;
@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INFlight : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAirline:(INAirline *)airline
                   flightNumber:(NSString *)flightNumber
                   boardingTime:(nullable INDateComponentsRange *)boardingTime
                 flightDuration:(INDateComponentsRange *)flightDuration
           departureAirportGate:(INAirportGate *)departureAirportGate
             arrivalAirportGate:(INAirportGate *)arrivalAirportGate NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INAirline *airline;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *flightNumber;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) INDateComponentsRange *boardingTime;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *flightDuration;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INAirportGate *departureAirportGate;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INAirportGate *arrivalAirportGate;

@end

NS_ASSUME_NONNULL_END
