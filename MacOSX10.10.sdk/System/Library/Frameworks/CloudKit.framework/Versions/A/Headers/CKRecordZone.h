//
//  CKRecordZone.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CloudKit/CKDefines.h>

@class CKRecordZoneID;

typedef NS_OPTIONS(NSUInteger, CKRecordZoneCapabilities) {
    /* This zone supports CKFetchRecordChangesOperation */
    CKRecordZoneCapabilityFetchChanges   = 1 << 0,
    /* Batched changes to this zone happen atomically */
    CKRecordZoneCapabilityAtomic         = 1 << 1,
} NS_AVAILABLE(10_10, 8_0);

/* The default zone has no capabilities */
CK_EXTERN NSString * const CKRecordZoneDefaultName NS_AVAILABLE(10_10, 8_0);

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKRecordZone : NSObject <NSSecureCoding, NSCopying>

+ (CKRecordZone *)defaultRecordZone;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithZoneName:(NSString *)zoneName;
- (instancetype)initWithZoneID:(CKRecordZoneID *)zoneID;

@property (nonatomic, readonly, strong) CKRecordZoneID *zoneID;

/* Capabilities are not set until a record zone is saved */
@property (nonatomic, readonly, assign) CKRecordZoneCapabilities capabilities;

@end
