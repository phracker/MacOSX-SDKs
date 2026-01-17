/*
    NSPersistentCloudKitContainerOptions.h
    Core Data
    Copyright (c) 2018-2019, Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>


NS_ASSUME_NONNULL_BEGIN

/**
 NSPersistentCloudKitContainerOptions provides customization of how NSPersistentCloudKitContainer aligns a given instance of NSPersistentStoreDescription with a CloudKit database.
 */
API_AVAILABLE(macosx(10.15),ios(13.0),tvos(13.0),watchos(6.0))
@interface NSPersistentCloudKitContainerOptions : NSObject
/**
 The container identifier of the CKContainer to use with a given instance of NSPersistentStoreDescription
 */
@property(readonly, copy) NSString *containerIdentifier;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithContainerIdentifier:(NSString *)containerIdentifier NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END

