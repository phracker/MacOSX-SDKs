//
//  HMAccessoryCategory.h
//  HomeKit
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMAccessoryCategoryTypes.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent an accessory category.
 */
HM_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMAccessoryCategory : NSObject

/*!
 * @brief A type identifier that represents the category.
 */
@property(readonly, copy) NSString *categoryType;

/*!
 * @brief The localized description of the category.
 */
@property(readonly, copy) NSString *localizedDescription;

@end

NS_ASSUME_NONNULL_END
