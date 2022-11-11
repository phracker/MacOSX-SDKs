//
//  CLPlacemark+IntentsAdditions.h
//  Intents
//
//  Copyright (c) 2016-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLPlacemark.h>

@class CNPostalAddress;

NS_ASSUME_NONNULL_BEGIN

@interface CLPlacemark (INIntentsAdditions)

+ (instancetype)placemarkWithLocation:(CLLocation *)location
                                 name:(nullable NSString *)name
                        postalAddress:(nullable CNPostalAddress *)postalAddress API_AVAILABLE(ios(10.0), watchos(3.2), macos(11.0)) API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END
