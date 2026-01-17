//
//  INRidePartySizeOption.h
//  Intents
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class INPriceRange;

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(10.0), watchos(3.0))
API_UNAVAILABLE(macosx)
@interface INRidePartySizeOption : NSObject <NSCopying, NSSecureCoding>

// A single party size in a set of party size selections. Each size may have a different price range.
- (instancetype)initWithPartySizeRange:(NSRange)partySizeRange sizeDescription:(NSString *)sizeDescription priceRange:(nullable INPriceRange *)priceRange NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;

@property (readonly, NS_NONATOMIC_IOSONLY) NSRange partySizeRange; // The number of people allowed, e.g. NSMakeRange(1, 0) for one person, or NSMakeRange(1, 2) for 1 to 3 people.
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *sizeDescription; // e.g. "1 passenger" or "1-3 passengers".
@property (readonly, nullable, NS_NONATOMIC_IOSONLY) INPriceRange *priceRange; // the price range for this party size, which may be different from the indicative price range for the ride. If nil, the price range for the associated ride is valid instead.

@end

NS_ASSUME_NONNULL_END

