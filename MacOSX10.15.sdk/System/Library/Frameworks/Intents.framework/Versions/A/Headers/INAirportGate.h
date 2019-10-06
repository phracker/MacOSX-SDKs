//
//  INAirportGate.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INAirport;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), watchos(6.0))
API_UNAVAILABLE(macosx)
@interface INAirportGate : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAirport:(INAirport *)airport
                       terminal:(nullable NSString *)terminal
                           gate:(nullable NSString *)gate NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, NS_NONATOMIC_IOSONLY) INAirport *airport;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *terminal;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *gate;

@end

NS_ASSUME_NONNULL_END
