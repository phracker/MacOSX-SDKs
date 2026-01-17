//  HMAction.h
//  HomeKit
//
//  Copyright (c) 2014-2015 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @brief This class is used to represent a generic action.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(8.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMAction : NSObject

- (instancetype)init API_DEPRECATED("HMAction is abstract", ios(8.0, 16.4), macos(10.14, 13.3), macCatalyst(14.0, 16.4), tvos(10.0, 16.4), watchos(2.0, 9.4));
+ (instancetype)new API_DEPRECATED("HMAction is abstract", ios(8.0, 16.4), macos(10.14, 13.3), macCatalyst(14.0, 16.4), tvos(10.0, 16.4), watchos(2.0, 9.4));

/*!
 * @brief A unique identifier for the action.
 */
@property (nonatomic, readonly, copy) NSUUID *uniqueIdentifier API_AVAILABLE(ios(9.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
