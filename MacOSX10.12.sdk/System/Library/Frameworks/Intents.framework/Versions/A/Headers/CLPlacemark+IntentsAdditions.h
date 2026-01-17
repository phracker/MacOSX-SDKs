//
//  CLPlacemark+IntentsAdditions.h
//  Intents
//
//  Copyright © 2016 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CLPlacemark.h>

@class CNPostalAddress;

NS_ASSUME_NONNULL_BEGIN

@interface CLPlacemark (INIntentsAdditions)

+ (instancetype)placemarkWithLocation:(CLLocation *)location
                                 name:(nullable NSString *)name
                        postalAddress:(nullable CNPostalAddress *)postalAddress API_AVAILABLE(ios(10.0));

@end

NS_ASSUME_NONNULL_END
