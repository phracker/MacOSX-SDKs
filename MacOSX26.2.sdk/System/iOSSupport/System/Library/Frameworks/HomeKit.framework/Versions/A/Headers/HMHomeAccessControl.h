//
//  HMHomeAccessControl.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <HomeKit/HMAccessControl.h>
#import <HomeKit/HMDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @brief Represents the access control of a user associated with a home.
 */
HM_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0))
API_UNAVAILABLE(macos)
@interface HMHomeAccessControl : HMAccessControl

/*!
 * @brief Specifies if the user has administrative privileges for the home.
 */
@property (nonatomic, readonly, getter=isAdministrator) BOOL administrator;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)
