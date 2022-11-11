//
//  INAirport.h
//  Intents
//
//  Copyright (c) 2016-2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INAirport : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithName:(nullable NSString *)name
                    iataCode:(nullable NSString *)iataCode
                    icaoCode:(nullable NSString *)icaoCode NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *name;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *iataCode;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *icaoCode;

@end

NS_ASSUME_NONNULL_END
