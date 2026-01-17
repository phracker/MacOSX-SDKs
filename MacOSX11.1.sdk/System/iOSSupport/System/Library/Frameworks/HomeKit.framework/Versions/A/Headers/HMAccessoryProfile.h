//
//  HMAccessoryProfile.h
//  HomeKit
//
//  Copyright © 2015-2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

@class HMAccessory;
@class HMService;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @abstract Represents a profile implemented by an accessory.
 */
HM_EXTERN API_AVAILABLE(ios(10.0), watchos(3.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMAccessoryProfile : NSObject

- (instancetype)init NS_UNAVAILABLE;

/*!
 * @brief A unique identifier for the profile.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier;

/*!
 * @brief Collection of services representing the profile.
 */
@property(readonly, strong, nonatomic) NSArray<HMService *> *services;

/*!
 * @brief Accessory implementing the profile.
 */
@property(readonly, weak, nonatomic) HMAccessory *accessory;

@end

NS_ASSUME_NONNULL_END
