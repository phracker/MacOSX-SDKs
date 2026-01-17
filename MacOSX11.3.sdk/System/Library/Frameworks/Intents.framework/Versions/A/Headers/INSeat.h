//
//  INSeat.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(13.0), macos(11.0), watchos(6.0))
API_UNAVAILABLE(tvos)
@interface INSeat : NSObject <NSCopying, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithSeatSection:(nullable NSString *)seatSection
                            seatRow:(nullable NSString *)seatRow
                         seatNumber:(nullable NSString *)seatNumber
                        seatingType:(nullable NSString *)seatingType NS_DESIGNATED_INITIALIZER;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *seatSection;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *seatRow;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *seatNumber;

@property (readonly, copy, nullable, NS_NONATOMIC_IOSONLY) NSString *seatingType;

@end

NS_ASSUME_NONNULL_END
