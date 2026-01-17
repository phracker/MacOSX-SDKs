//
//  HMEvent.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

@class HMHome;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/*!
 * @brief This class is used to represent a generic HomeKit event.
 */
HM_EXTERN NS_SWIFT_SENDABLE API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMEvent : NSObject

- (instancetype)init API_DEPRECATED("HMEvent is abstract", ios(9.0, 16.4), macos(10.14, 13.3), macCatalyst(14.0, 16.4), tvos(10.0, 16.4), watchos(2.0, 9.4));
+ (instancetype)new API_DEPRECATED("HMEvent is abstract", ios(9.0, 16.4), macos(10.14, 13.3), macCatalyst(14.0, 16.4), tvos(10.0, 16.4), watchos(2.0, 9.4));

/*!
 * @brief A unique identifier for the event.
 */
@property (nonatomic, readonly, copy) NSUUID *uniqueIdentifier;

/*!
 * @brief Specifies whether the HMEvent can be added to HMEventTrigger on the given home.
 */
+ (BOOL)isSupportedForHome:(HMHome *)home API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
