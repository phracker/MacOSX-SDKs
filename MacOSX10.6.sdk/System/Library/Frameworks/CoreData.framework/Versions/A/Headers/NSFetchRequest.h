/*
    NSFetchRequest.h
    Core Data
    Copyright (c) 2004-2009 Apple Inc.
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
	NSUInteger _offset;
	NSArray *_valuesToFetch;
    __weak NSEntityDescription *_entity;
    NSPredicate *_predicate;
    NSArray *_sortDescriptors;
    NSUInteger _batchSize;
    unsigned long _fetchLimit;
    NSArray *_affectedStores;
    NSArray *_relationshipKeyPathsForPrefetching;
    struct _fetchRequestFlags {
        unsigned int distinctValuesOnly:1;
        unsigned int includesSubentities:1;
        unsigned int includesPropertyValues:1;
        unsigned int resultType:3;
        unsigned int returnsObjectsAsFaults:1;
        unsigned int excludePendingChanges:1;
        unsigned int isInUse:1;
        unsigned int _RESERVED:23;
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
    NSManagedObjectIDResultType		= 0x01
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
    , NSDictionaryResultType		= 0x02
#endif
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


/* Results accommodate the currently unsaved changes in the NSManagedObjectContext.  When disabled, the fetch request skips checking unsaved changes and only returns objects that matched the predicate in the persistent store.  Defaults to YES.
*/
- (BOOL)includesPendingChanges AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setIncludesPendingChanges:(BOOL)flag AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns/sets if the fetch request returns only distinct values for the fields specified by valuesToFetch. This value is only used if valuesToFetch has been set. Defaults to NO. */
- (BOOL)returnsDistinctResults AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setReturnsDistinctResults:(BOOL)flag AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Specifies a collection NSPropertyDescriptions that should be returned by the result. This value is only used if resultType is set to NSDictionaryResultType. Property descriptions added to valuesToFetch may represent attributes, expressions, or to one relationships; for attribute or relationship descriptions, the name must match the name of a description on the fetch entity. Results of the fetch will be returned as dictionaries containing key/value pairs where the key is the name of the specified property description. */
- (NSArray *)propertiesToFetch AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setPropertiesToFetch:(NSArray *)values AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Allows you to specify an offset at which rows will begin being returned.  Effectively, the request will skip over 'offset' number of matching entries.  For example, given a fetch which would normally return a, b, c, and d, specifying an offset of 1 will return b, c, and d and an offset of 4  will return an empty array. Offsets are ignored in nested requests such as subqueries.  Default value is 0.  */
- (NSUInteger)fetchOffset AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setFetchOffset:(NSUInteger)offset AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* This breaks the result set into batches.  The entire request will be evaluated, and the identities of all matching objects will be recorded, but no more than batchSize objects' data will be fetched from the persistent store at a time.  The array returned from executing the request will be a subclass that transparently faults batches on demand.  For purposes of thread safety, the returned array proxy is owned by the NSManagedObjectContext the request is executed against, and should be treated as if it were a managed object registered with that context.  A batch size of 0 is treated as infinite, which disables the batch faulting behavior.  The default is 0. */

- (NSUInteger)fetchBatchSize AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setFetchBatchSize:(NSUInteger) bsize AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

#endif
