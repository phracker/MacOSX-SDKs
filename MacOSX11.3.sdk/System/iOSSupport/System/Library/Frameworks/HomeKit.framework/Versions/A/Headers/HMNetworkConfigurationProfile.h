//
//  HMNetworkConfigurationProfile.h
//  HomeKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <HomeKit/HMAccessoryProfile.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol HMNetworkConfigurationProfileDelegate;

HM_EXTERN API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMNetworkConfigurationProfile : HMAccessoryProfile

/*!
 *  @abstract   The delegate of the receiver.
 */
@property (nonatomic, weak) id<HMNetworkConfigurationProfileDelegate> delegate;

/*!
 *  @abstract   Indicates if the associated accessory's access to the network is restricted.
 */
@property (nonatomic, readonly, assign, getter=isNetworkAccessRestricted) BOOL networkAccessRestricted;

@end

API_AVAILABLE(ios(13.0), watchos(6.0), tvos(13.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@protocol HMNetworkConfigurationProfileDelegate <NSObject>

@optional

/*!
 * @brief Informs the delegate that the network access mode has updated.
 *
 * @param profile Sender of the message.
 */
- (void)profileDidUpdateNetworkAccessMode:(HMNetworkConfigurationProfile *)profile;

@end

NS_ASSUME_NONNULL_END
