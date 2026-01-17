//
//  HMAccessorySetupResult.h
//  HomeKit
//
//  Created by Nick Fraioli on 7/12/21.
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(15.4)) API_UNAVAILABLE(watchos, tvos, visionos) API_UNAVAILABLE(macos, macCatalyst)
@interface HMAccessorySetupResult : NSObject<NSCopying>

/*!
 *  @abstract   The -[HMHome uniqueIdentifier] that the accessories were added to
 */
@property (readonly, copy) NSUUID *homeUniqueIdentifier;

/*!
 *  @abstract   The -[HMAccessory uniqueIdentifier] values corresponding to the accessories that were set up.
 *              Usually only one accessory is set up at a time, but adding an accessory bridge can result in
 *              multiple accessories being set up at once
 */
@property (readonly, copy) NSArray<NSUUID *> *accessoryUniqueIdentifiers;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
