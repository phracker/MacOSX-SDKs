/*
    NSManagedObjectID.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>

@class NSEntityDescription;
@class NSURL;

// Managed object IDs are opaque identifiers for managed objects.
@interface NSManagedObjectID : NSObject <NSCopying> {
}

- (NSEntityDescription *)entity;    // entity for the object identified by an ID
- (id)persistentStore;    // persistent store that fetched the object identified by an ID

- (BOOL)isTemporaryID;    // indicates whether or not this ID will be replaced later, such as after a save operation (temporary IDs are assigned to newly inserted objects and replaced with permanent IDs when an object is written to a persistent store); most IDs return NO

- (NSURL *)URIRepresentation;    // URI which provides an archivable reference to the object which this ID refers

@end

#endif
