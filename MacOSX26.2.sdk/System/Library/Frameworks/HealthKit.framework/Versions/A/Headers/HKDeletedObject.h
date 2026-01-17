//
//  HKDeletedObject.h
//  HealthKit
//
//  Copyright (c) 2015-2022 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <HealthKit/HKDefines.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @class         HKDeletedObject
 @abstract      A class representing an HKObject that was deleted from the HealtKit database.
 */
HK_EXTERN
NS_SWIFT_SENDABLE
API_AVAILABLE(ios(9.0), watchos(2.0), macCatalyst(13.0), macos(13.0))
@interface HKDeletedObject : NSObject <NSSecureCoding>

/*!
 @property      UUID
 @abstract      The unique identifier of the HKObject that was deleted from the HealthKit database.
 */
@property (readonly, strong) NSUUID *UUID;

/*!
 @property      metadata
 @abstract      Extra information describing properties of the receiver.
 @discussion    Metadata retained from the deleted HKObject.
                Available keys: HKMetadataKeySyncIdentifier, HKMetadataKeySyncVersion
 */
@property (readonly, copy, nullable) NSDictionary<NSString *, id> *metadata API_AVAILABLE(ios(11.0), watchos(4.0), macCatalyst(13.0), macos(13.0));

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
