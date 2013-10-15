/*
    NSFetchRequest.h
    Core Data
    Copyright (c) 2004-2005 Apple Computer, Inc.
    All rights reserved.
*/

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#import <Foundation/NSObject.h>

@class NSArray;
@class NSEntityDescription;
@class NSManagedObjectModel;
@class NSPredicate;
@class NSString;

@interface NSFetchRequest : NSObject <NSCoding, NSCopying> {
@private
	void *_reserved;
	void *_reserved2;
	void *_reserved3;
	void *_reserved4;
    NSEntityDescription *_entity;
    NSPredicate *_predicate;
    NSArray *_sortDescriptors;
    unsigned int _inUseCounter;
    unsigned int _fetchLimit;
    NSArray *_affectedStores;
    NSArray *_prefetchRelationshipKeys;
    struct _fetchRequestFlags {
        unsigned int autoDistinct:1;
        unsigned int shallow:1;
        unsigned int fetchRowData:1;
        unsigned int resultsAsObjectIDs:1;
        unsigned int _RESERVED:28;
    } _flags;
}

- (NSEntityDescription *)entity;
- (void)setEntity:(NSEntityDescription *)entity;
- (NSPredicate *)predicate;
- (void)setPredicate:(NSPredicate *)predicate;
- (NSArray *)sortDescriptors;
- (void)setSortDescriptors:(NSArray *)sortDescriptors;
- (unsigned int)fetchLimit;
- (void)setFetchLimit:(unsigned int)limit;
- (NSArray *)affectedStores;
- (void)setAffectedStores:(NSArray *)stores;

@end

#endif
