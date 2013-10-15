/*
    NSFetchRequest.h
    Core Data
    Copyright (c) 2004-2010 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
#import <CoreData/NSPersistentStoreRequest.h>
#else 
#ifndef NSPersistentStoreRequest
#define NSPersistentStoreRequest NSObject
#endif
#endif

@class NSEntityDescription;
@class NSManagedObjectModel;
@class NSPredicate;
@class NSString;

/* Definition of the possible result types a fetch request can return. */

enum {
    NSManagedObjectResultType		= 0x00,
    NSManagedObjectIDResultType		= 0x01
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
    , NSDictionaryResultType		= 0x02
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
	, NSCountResultType				= 0x04
#endif
};
typedef NSUInteger NSFetchRequestResultType;



NS_CLASS_AVAILABLE(10_4, 3_0)
@interface NSFetchRequest : NSPersistentStoreRequest <NSCoding> {
@private
#if MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_7
	NSArray *_reserved;
#endif
	NSArray *_groupByProperties;
	NSPredicate *_havingPredicate;
	NSUInteger _offset;
	NSArray *_valuesToFetch;
    NSEntityDescription *_entity;
    NSPredicate *_predicate;
    NSArray *_sortDescriptors;
    NSUInteger _batchSize;
    unsigned long _fetchLimit;
    NSArray *_relationshipKeyPathsForPrefetching;
    struct _fetchRequestFlags {
        unsigned int distinctValuesOnly:1;
        unsigned int includesSubentities:1;
        unsigned int includesPropertyValues:1;
        unsigned int resultType:3;
        unsigned int returnsObjectsAsFaults:1;
        unsigned int excludePendingChanges:1;
        unsigned int isInUse:1;
        unsigned int entityIsName:1;
        unsigned int refreshesRefetched:1;
        unsigned int propertiesValidated:1;
        unsigned int _RESERVED:20;
    } _flags;
}

+ (NSFetchRequest*)fetchRequestWithEntityName:(NSString*)entityName NS_AVAILABLE(10_7, NA);

- (id)init;
- (id)initWithEntityName:(NSString*)entityName NS_AVAILABLE(10_7, NA);

- (NSEntityDescription *)entity;
- (void)setEntity:(NSEntityDescription *)entity;
- (NSString*)entityName NS_AVAILABLE(10_7, NA);

- (NSPredicate *)predicate;
- (void)setPredicate:(NSPredicate *)predicate;

- (NSArray *)sortDescriptors;
- (void)setSortDescriptors:(NSArray *)sortDescriptors;

- (NSUInteger)fetchLimit;
- (void)setFetchLimit:(NSUInteger)limit;

- (NSArray *)affectedStores;
- (void)setAffectedStores:(NSArray *)stores;

/* Returns/sets the result type of the fetch request (the instance type of objects returned from executing the request.)  Setting the value to NSManagedObjectIDResultType will demote any sort orderings to "best effort" hints if property values are not included in the request.  Defaults to NSManagedObjectResultType.   
*/
- (NSFetchRequestResultType)resultType NS_AVAILABLE(10_5,3_0);
- (void)setResultType:(NSFetchRequestResultType)type NS_AVAILABLE(10_5,3_0);


/* Returns/sets if the fetch request includes subentities.  If set to NO, the request will fetch objects of exactly the entity type of the request;  if set to YES, the request will include all subentities of the entity for the request.  Defaults to YES. 
*/
- (BOOL)includesSubentities NS_AVAILABLE(10_5,3_0);
- (void)setIncludesSubentities:(BOOL)yesNo NS_AVAILABLE(10_5,3_0);


/* Returns/sets if, when the fetch is executed, property data is obtained from the persistent store.  If the value is set to NO, the request will not obtain property information, but only information to identify each object (used to create NSManagedObjectIDs.)  If managed objects for these IDs are later faulted (as a result attempting to access property values), they will incur subsequent access to the persistent store to obtain their property values.  Defaults to YES. 
*/
- (BOOL)includesPropertyValues NS_AVAILABLE(10_5,3_0);
- (void)setIncludesPropertyValues:(BOOL)yesNo NS_AVAILABLE(10_5,3_0);


/* Returns/sets if the objects resulting from a fetch request are faults.  If the value is set to NO, the returned objects are pre-populated with their property values (making them fully-faulted objects, which will immediately return NO if sent the -isFault message.)  If the value is set to YES, the returned objects are not pre-populated (and will receive a -didFireFault message when the properties are accessed the first time.)  This setting is not utilized if the result type of the request is NSManagedObjectIDResultType, as object IDs do not have property values.  Defaults to YES. 
*/
- (BOOL)returnsObjectsAsFaults NS_AVAILABLE(10_5,3_0);
- (void)setReturnsObjectsAsFaults:(BOOL)yesNo NS_AVAILABLE(10_5,3_0);


/* Returns/sets an array of relationship keypaths to prefetch along with the entity for the request.  The array contains keypath strings in NSKeyValueCoding notation, as you would normally use with valueForKeyPath.  (Prefetching allows Core Data to obtain developer-specified related objects in a single fetch (per entity), rather than incurring subsequent access to the store for each individual record as their faults are tripped.)  Defaults to an empty array (no prefetching.) 
*/
- (NSArray *)relationshipKeyPathsForPrefetching NS_AVAILABLE(10_5,3_0);
- (void)setRelationshipKeyPathsForPrefetching:(NSArray *)keys NS_AVAILABLE(10_5,3_0);


/* Results accommodate the currently unsaved changes in the NSManagedObjectContext.  When disabled, the fetch request skips checking unsaved changes and only returns objects that matched the predicate in the persistent store.  Defaults to YES.
*/
- (BOOL)includesPendingChanges NS_AVAILABLE(10_6, 3_0);
- (void)setIncludesPendingChanges:(BOOL)flag NS_AVAILABLE(10_6, 3_0);

/* Returns/sets if the fetch request returns only distinct values for the fields specified by propertiesToFetch. This value is only used for NSDictionaryResultType. Defaults to NO. */
- (BOOL)returnsDistinctResults NS_AVAILABLE(10_6, 3_0);
- (void)setReturnsDistinctResults:(BOOL)flag NS_AVAILABLE(10_6, 3_0);

/* Specifies a collection of either NSPropertyDescriptions or NSString property names that should be fetched. The collection may represent attributes, to-one relationships, or NSExpressionDescription.  If NSDictionaryResultType is set, the results of the fetch will be dictionaries containing key/value pairs where the key is the name of the specified property description.  If NSManagedObjectResultType is set, then NSExpressionDescription cannot be used, and the results are managed object faults partially pre-populated with the named properties */
- (NSArray *)propertiesToFetch NS_AVAILABLE(10_6, 3_0);
- (void)setPropertiesToFetch:(NSArray *)values NS_AVAILABLE(10_6, 3_0);

/* Allows you to specify an offset at which rows will begin being returned.  Effectively, the request will skip over 'offset' number of matching entries.  For example, given a fetch which would normally return a, b, c, and d, specifying an offset of 1 will return b, c, and d and an offset of 4  will return an empty array. Offsets are ignored in nested requests such as subqueries.  Default value is 0.  */
- (NSUInteger)fetchOffset NS_AVAILABLE(10_6, 3_0);
- (void)setFetchOffset:(NSUInteger)offset NS_AVAILABLE(10_6, 3_0);

/* This breaks the result set into batches.  The entire request will be evaluated, and the identities of all matching objects will be recorded, but no more than batchSize objects' data will be fetched from the persistent store at a time.  The array returned from executing the request will be a subclass that transparently faults batches on demand.  For purposes of thread safety, the returned array proxy is owned by the NSManagedObjectContext the request is executed against, and should be treated as if it were a managed object registered with that context.  A batch size of 0 is treated as infinite, which disables the batch faulting behavior.  The default is 0. */

- (NSUInteger)fetchBatchSize NS_AVAILABLE(10_6, 3_0);
- (void)setFetchBatchSize:(NSUInteger) bsize NS_AVAILABLE(10_6, 3_0);

- (BOOL)shouldRefreshRefetchedObjects NS_AVAILABLE(10_7, NA);
- (void)setShouldRefreshRefetchedObjects:(BOOL)flag NS_AVAILABLE(10_7, NA);

/* Specifies the way in which data should be grouped before a select statement is run in an SQL database.
 Values passed to propertiesToGroupBy must be NSPropertyDescriptions, NSExpressionDescriptions, or keypath strings; keypaths can not contain 
 any to-many steps. 
 If GROUP BY is used, then you must set the resultsType to NSDictionaryResultsType, and the SELECT values must be literals, aggregates, 
 or columns specified in the GROUP BY. Aggregates will operate on the groups specified in the GROUP BY rather than the whole table. */
- (NSArray*)propertiesToGroupBy NS_AVAILABLE(10_7, NA); 
- (void)setPropertiesToGroupBy:(NSArray *)array NS_AVAILABLE(10_7, NA); 

/* Specifies a predicate that will be used to filter rows being returned by a query containing a GROUP BY. If a having predicate is
 supplied, it will be run after the GROUP BY.  Specifying a HAVING predicate requires that a GROUP BY also be specified. */
- (NSPredicate*)havingPredicate NS_AVAILABLE(10_7, NA);
- (void)setHavingPredicate:(NSPredicate *)predicate NS_AVAILABLE(10_7, NA); 

@end
