//
//  INRentalCar.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INRentalCar : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithRentalCompanyName:(NSString *)rentalCompanyName
                                     type:(nullable NSString *)type
                                     make:(nullable NSString *)make
                                    model:(nullable NSString *)model
                     rentalCarDescription:(nullable NSString *)rentalCarDescription NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *rentalCompanyName;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *type;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *make;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *model;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *rentalCarDescription;

@end

NS_ASSUME_NONNULL_END
