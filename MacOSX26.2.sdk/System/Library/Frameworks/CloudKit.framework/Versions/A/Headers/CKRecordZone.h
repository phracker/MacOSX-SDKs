//
//  CKRecordZone.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <CloudKit/CKDefines.h>

@class CKRecordZoneID, CKReference;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef NS_OPTIONS(NSUInteger, CKRecordZoneCapabilities) {
    /// This zone supports `CKFetchRecordZoneChangesOperation`
    CKRecordZoneCapabilityFetchChanges   = 1 << 0,
    /// Batched changes to this zone happen atomically
    CKRecordZoneCapabilityAtomic         = 1 << 1,
    /// Records in this zone can be shared
    CKRecordZoneCapabilitySharing        API_AVAILABLE(macos(10.12), ios(10.0), tvos(10.0)) = 1 << 2,
    /// This zone supports a single `CKShare` record that shares all records in the zone
    CKRecordZoneCapabilityZoneWideSharing API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0)) = 1 << 3,
} API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0))
typedef NS_ENUM(NSInteger, CKRecordZoneEncryptionScope) {
    /// Zone uses per-record encryption keys for any encrypted values on a record or share.
    ///
    /// This is the default encryption scope for a record zone.
    CKRecordZoneEncryptionScopePerRecord,

    /// Zone uses per-zone encryption keys for encrypted values across all records and the zone-wide share, if present.
    ///
    /// This is an optional optimization that can reduce the overall storage used by encryption keys in a zone.
    /// Note that:
    /// - Record zones using per-zone encryption only support zone-wide sharing.
    /// - Encryption scope can only be assigned at zone creation and cannot be changed for the lifetime of the zone.
    /// - The server will not return zones using per-zone encryption to device OS versions older than the corresponding API availability version.
    /// - An older OS trying to overwrite an existing zone using per-zone encryption due to a naming collision will result in a `.serverRejectedRequest` error.
    /// - On device OS upgrade, your application is responsible for fetching database changes via `CKFetchDatabaseChangesOperation` with a nil sync token to ensure it has
    /// received all the zones available to it from the server.
    CKRecordZoneEncryptionScopePerZone,
};

CK_EXTERN NSString * const CKRecordZoneDefaultName API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0));

API_AVAILABLE(macos(10.10), ios(8.0), watchos(3.0))
CK_SUBCLASSING_DEPRECATED // should not be subclassed, or Sendable may no longer apply
// NS_SWIFT_SENDABLE on macos(14.0), ios(17.0), tvos(17.0), watchos(10.0)
@interface CKRecordZone : NSObject <NSSecureCoding, NSCopying>

+ (CKRecordZone *)defaultRecordZone;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)initWithZoneName:(NSString *)zoneName;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID;

@property (readonly, copy) CKRecordZoneID *zoneID;

/// Capabilities on locally-created record zones are not valid until the record zone is saved. Capabilities on record zones fetched from the server are valid.
@property (readonly, assign) CKRecordZoneCapabilities capabilities;

/// The share property on a record zone will only be set on zones fetched from the server and only if a
/// corresponding zone-wide share record for the zone exists on the server.
///
/// You can create a zone-wide share for a zone using `-[CKShare initWithRecordZoneID:]`.
///
/// Zone-wide sharing is only supported in zones with the `CKRecordZoneCapabilityZoneWideSharing` sharing capability.
/// You cannot share a zone if it already contains shared records.
@property (nullable, readonly, copy) CKReference *share API_AVAILABLE(macos(12.0), ios(15.0), tvos(15.0), watchos(8.0));

/// The encryption scope determines the granularity at which encryption keys are stored within the zone.
///
/// Zone encryption scope defaults to `CKRecordZoneEncryptionScopePerRecord` and can only be modified before zone creation. Attempting to change the encryption
/// scope of an existing zone is invalid and will result in an error.
///
/// Zones using `CKRecordZoneEncryptionScopePerZone` can only use zone-wide sharing and are not compatible with older device OS versions. Refer to `CKRecordZoneEncryptionScope` for more info.
@property (assign) CKRecordZoneEncryptionScope encryptionScope API_AVAILABLE(macos(26.0), ios(26.0), tvos(26.0), watchos(26.0), visionos(26.0));

@end

NS_HEADER_AUDIT_END(nullability, sendability)
