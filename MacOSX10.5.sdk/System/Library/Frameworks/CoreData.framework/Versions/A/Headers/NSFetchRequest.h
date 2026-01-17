/*
    NSFetchRequest.h
    Core Data
    Copyright (c) 2004-2007 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

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
    __weak NSEntityDescription *_entity;
    NSPredicate *_predicate;
    NSArray *_sortDescriptors;
    unsigned long _inUseCounter;
    unsigned long _fetchLimit;
    NSArray *_affectedStores;
    NSArray *_relationshipKeyPathsForPrefetching;
    struct _fetchRequestFlags {
        unsigned int autoDistinct:1;
        unsigned int includesSubentities:1;
        unsigned int includesPropertyValues:1;
        unsigned int resultType:3;
        unsigned int returnsObjectsAsFaults:1;
        unsigned int excludePendingChanges:1;
        unsigned int _RESERVED:24;
    } _flags;
}

- (NSEntityDescription *)entity;
- (void)setEntity:(NSEntityDescription *)entity;

- (NSPredicate *)predicate;
- (void)setPredicate:(NSPredicate *)predicate;

- (NSArray *)sortDescriptors;
- (void)setSortDescriptors:(NSArray *)sortDescriptors;

- (NSUInteger)fetchLimit;
- (void)setFetchLimit:(NSUInteger)limit;

- (NSArray *)affectedStores;
- (void)setAffectedStores:(NSArray *)stores;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

/* Definition of the possible result types a fetch request can return. */

enum {
    NSManagedObjectResultType		= 0x00,
    NSManagedObjectIDResultType		= 0x01,
};
typedef NSUInteger NSFetchRequestResultType;


/* Returns/sets the result type of the fetch request (the instance type of objects returned from executing the request.)  Setting the value to NSManagedObjectIDResultType will demote any sort orderings to "best effort" hints if property values are not included in the request.  Defaults to NSManagedObjectResultType.   
*/
- (NSFetchRequestResultType)resultType;
- (void)setResultType:(NSFetchRequestResultType)type;


/* Returns/sets if the fetch request includes subentities.  If set to NO, the request will fetch objects of exactly the entity type of the request;  if set to YES, the request will include all subentities of the entity for the request.  Defaults to YES. 
*/
- (BOOL)includesSubentities;
- (void)setIncludesSubentities:(BOOL)yesNo;


/* Returns/sets if, when the fetch is executed, property data is obtained from the persistent store.  If the value is set to NO, the request will not obtain property information, but only information to identify each object (used to create NSManagedObjectIDs.)  If managed objects for these IDs are later faulted (as a result attempting to access property values), they will incur subsequent access to the persistent store to obtain their property values.  Defaults to YES. 
*/
- (BOOL)includesPropertyValues;
- (void)setIncludesPropertyValues:(BOOL)yesNo;


/* Returns/sets if the objects resulting from a fetch request are faults.  If the value is set to NO, the returned objects are pre-populated with their property values (making them fully-faulted objects, which will immediately return NO if sent the -isFault message.)  If the value is set to YES, the returned objects are not pre-populated (and will receive a -didFireFault message when the properties are accessed the first time.)  This setting is not utilized if the result type of the request is NSManagedObjectIDResultType, as object IDs do not have property values.  Defaults to YES. 
*/
- (BOOL)returnsObjectsAsFaults;
- (void)setReturnsObjectsAsFaults:(BOOL)yesNo;


/* Returns/sets an array of relationship keypaths to prefetch along with the entity for the request.  The array contains keypath strings in NSKeyValueCoding notation, as you would normally use with valueForKeyPath.  (Prefetching allows Core Data to obtain developer-specified related objects in a single fetch (per entity), rather than incurring subsequent access to the store for each individual record as their faults are tripped.)  Defaults to an empty array (no prefetching.) 
*/
- (NSArray *)relationshipKeyPathsForPrefetching;
- (void)setRelationshipKeyPathsForPrefetching:(NSArray *)keys;

#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

@end

#endif
