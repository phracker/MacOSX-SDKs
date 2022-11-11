//
//  HMCHIPServiceRoom.h
//  HomeKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HMDefines.h>

NS_ASSUME_NONNULL_BEGIN
/*!
 * @abstract A simple room representation that can be passed back and forth between Partner Ecosystem App extensions and iOS for the purposes of CHIP accessory setup.
 */
HM_EXTERN API_AVAILABLE(ios(15.0))
@interface HMCHIPServiceRoom : NSObject <NSCopying, NSSecureCoding>

/*!
 *  @abstract   The UUID of the receiver
 */
@property (nonatomic, strong, readonly) NSUUID *uuid;

/*!
 *  @abstract   The name of the receiver
 */
@property (nonatomic, strong, readonly) NSString *name;

/*!
 *  @abstract   Initializes a new instance
 */
- (instancetype)initWithUUID:(NSUUID *)uuid name:(NSString *)name NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
