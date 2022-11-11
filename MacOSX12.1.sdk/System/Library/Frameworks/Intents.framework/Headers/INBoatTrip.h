//
//  INBoatTrip.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CLPlacemark;
@class INDateComponentsRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0), macos(11.0), watchos(7.0))
API_UNAVAILABLE(tvos)
@interface INBoatTrip : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithProvider:(nullable NSString *)provider
                        boatName:(nullable NSString *)boatName
                      boatNumber:(nullable NSString *)boatNumber
                    tripDuration:(INDateComponentsRange *)tripDuration
   departureBoatTerminalLocation:(CLPlacemark *)departureBoatTerminalLocation
     arrivalBoatTerminalLocation:(CLPlacemark *)arrivalBoatTerminalLocation NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *provider;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *boatName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *boatNumber;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INDateComponentsRange *tripDuration;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *departureBoatTerminalLocation;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) CLPlacemark *arrivalBoatTerminalLocation;

@end

NS_ASSUME_NONNULL_END
