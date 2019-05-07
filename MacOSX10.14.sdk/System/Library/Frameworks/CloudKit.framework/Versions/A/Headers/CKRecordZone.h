//
//  CKRecordZone.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

@class CKRecordZoneID;

NS_ASSUME_NONNULL_BEGIN
typedef NS_OPTIONS(NSUInteger, CKRecordZoneCapabilities) {
    /*! This zone supports CKFetchRecordChangesOperation */
    CKRecordZoneCapabilityFetchChanges   = 1 << 0,
    /*! Batched changes to this zone happen atomically */
    CKRecordZoneCapabilityAtomic         = 1 << 1,
    /*! Records in this zone can be shared */
    CKRecordZoneCapabilitySharing        API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 1 << 2,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

CK_EXTERN NSString * const CKRecordZoneDefaultName API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
@interface CKRecordZone : NSObject <NSSecureCoding, NSCopying>

+ (CKRecordZone *)defaultRecordZone;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithZoneName:(NSString *)zoneName;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID;

@property (nonatomic, readonly, strong) CKRecordZoneID *zoneID;

/*! Capabilities on locally-created record zones are not valid until the record zone is saved. Capabilities on record zones fetched from the server are valid. */
@property (nonatomic, readonly, assign) CKRecordZoneCapabilities capabilities;

@end
NS_ASSUME_NONNULL_END
