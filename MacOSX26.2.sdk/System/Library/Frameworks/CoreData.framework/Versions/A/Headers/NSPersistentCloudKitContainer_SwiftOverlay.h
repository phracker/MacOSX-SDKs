/*
    NSPersistentCloudKitContainer_SwiftOverlay.h
    Core Data
    Copyright (c) 2018-2025, Apple Inc.
    All rights reserved.
*/

#import <CoreData/NSPersistentCloudKitContainer.h>

#if __swift__

NS_ASSUME_NONNULL_BEGIN

@class CKRecord;
@class CKRecordID;

API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0))
@interface NSPersistentCloudKitContainer (SwiftOverlay)

- (nullable CKRecord *)recordForManagedObjectID:(NSManagedObjectID *)managedObjectID;
- (NSDictionary<NSManagedObjectID *, CKRecord *> *)recordsForManagedObjectIDs:(NSArray<NSManagedObjectID *> *)managedObjectIDs;
- (nullable CKRecordID *)recordIDForManagedObjectID:(NSManagedObjectID *)managedObjectID;
- (NSDictionary<NSManagedObjectID *, CKRecordID *> *)recordIDsForManagedObjectIDs:(NSArray<NSManagedObjectID *> *)managedObjectIDs;

@end

NS_ASSUME_NONNULL_END

#endif // __swift
