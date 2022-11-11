//
//  HMEvent.h
//  HomeKit
//
//  Copyright (c) 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

@class HMHome;

NS_ASSUME_NONNULL_BEGIN

/*!
 * @brief This class is used to represent a generic HomeKit event.
 */
HM_EXTERN API_AVAILABLE(ios(9.0), watchos(2.0), tvos(10.0), macCatalyst(14.0)) API_UNAVAILABLE(macos)
@interface HMEvent : NSObject

/*!
 * @brief A unique identifier for the event.
 */
@property(readonly, copy, nonatomic) NSUUID *uniqueIdentifier;

/*!
 * @brief Specifies whether the HMEvent can be added to HMEventTrigger on the given home.
 */
+ (BOOL)isSupportedForHome:(HMHome *)home API_AVAILABLE(ios(11.0), watchos(4.0), tvos(11.0));

@end

NS_ASSUME_NONNULL_END
