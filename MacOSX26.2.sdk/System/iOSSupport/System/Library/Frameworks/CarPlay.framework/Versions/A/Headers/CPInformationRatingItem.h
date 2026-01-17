//
//  CPInformationRatingItem.h
//  CarPlay
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CarPlay/CPInformationItem.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(macos, watchos)
@interface CPInformationRatingItem : CPInformationItem

/**
 Initializes a new  item to be used with @c CPInformationTemplate.
 
 @param rating A number incremented by 0.5 intervals between 0 and maximumRating that will be styled by the template as the rating of the item.
 @param maximumRating A whole number between 1 - 5 that will be styled by the template as the maximum rating of the item.
 @param title An optional string that will be styled by the template as the title text of the item.
 @param detail An optional string that will be styled by the template as the detail text of the item.
 */
- (instancetype)initWithRating:(nullable NSNumber *)rating maximumRating:(nullable NSNumber *)maximumRating title:(nullable NSString *)title detail:(nullable NSString *)detail NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly, nullable) NSNumber *rating;
@property (nonatomic, readonly, nullable) NSNumber *maximumRating;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
