/*	NSMetadata.h
	Copyright (c) 2004-2005, Apple, Inc. All rights reserved.
*/

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

#define NSMQA1 AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER

@class NSString, NSArray, NSDictionary, NSPredicate;
@class NSMetadataItem, NSMetadataQueryAttributeValueTuple, NSMetadataQueryResultGroup;


@interface NSMetadataQuery : NSObject {
@private
    unsigned _flags;
    NSTimeInterval _interval;
    id _private[11];
    void *_reserved;
}

- (id)init;

- (id)delegate;
- (void)setDelegate:(id)delegate;

- (NSPredicate *)predicate;
- (void)setPredicate:(NSPredicate *)predicate;

- (NSArray *)sortDescriptors;
- (void)setSortDescriptors:(NSArray *)descriptors;

- (NSArray *)valueListAttributes;
- (void)setValueListAttributes:(NSArray *)attrs;

- (NSArray *)groupingAttributes;
- (void)setGroupingAttributes:(NSArray *)attrs;

- (NSTimeInterval)notificationBatchingInterval;
- (void)setNotificationBatchingInterval:(NSTimeInterval)ti;

- (NSArray *)searchScopes;
- (void)setSearchScopes:(NSArray *)scopes;
// scopes is an NSArray of NSURL objects (file URLs only) and/or string
// paths and/or the special string constants below, which specifies the
// locations to which the search is limited; an empty array means no
// limits, which is the default state.


- (BOOL)startQuery;
- (void)stopQuery;

- (BOOL)isStarted;
- (BOOL)isGathering;
- (BOOL)isStopped;

- (void)disableUpdates; // these nest
- (void)enableUpdates;


// Results are NSMetadataItems, or whatever the delegate replaces that with
- (unsigned)resultCount;
- (id)resultAtIndex:(unsigned)idx;

- (NSArray *)results;   // this is for K-V Bindings, and causes side-effects on the query

- (unsigned)indexOfResult:(id)result;

- (NSDictionary *)valueLists; // values are arrays of NSMetadataQueryAttributeValueTuple

- (NSArray *)groupedResults; // array of NSMetadataQueryResultGroups, for first grouping attribute

- (id)valueOfAttribute:(NSString *)attrName forResultAtIndex:(unsigned)idx;

@end

@interface NSObject (NSMetadataQueryDelegate)

- (id)metadataQuery:(NSMetadataQuery *)query replacementObjectForResultObject:(NSMetadataItem *)result;
- (id)metadataQuery:(NSMetadataQuery *)query replacementValueForAttribute:(NSString *)attrName value:(id)attrValue;

@end

// There is no info associated with these notifications
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidStartGatheringNotification NSMQA1;
FOUNDATION_EXPORT NSString * const NSMetadataQueryGatheringProgressNotification NSMQA1;
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidFinishGatheringNotification NSMQA1;
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidUpdateNotification NSMQA1;

FOUNDATION_EXPORT NSString * const NSMetadataQueryResultContentRelevanceAttribute NSMQA1;

// Scope constants for defined search locations
FOUNDATION_EXPORT NSString * const NSMetadataQueryUserHomeScope NSMQA1; // user home directory
FOUNDATION_EXPORT NSString * const NSMetadataQueryLocalComputerScope NSMQA1; // all local mounted volumes + user home (even if remote)
FOUNDATION_EXPORT NSString * const NSMetadataQueryNetworkScope NSMQA1; // all user-mounted remote volumes

@interface NSMetadataItem : NSObject {
@private
    id _item;
    void *_reserved;
}

- (id)valueForAttribute:(NSString *)key;
- (NSDictionary *)valuesForAttributes:(NSArray *)keys;

- (NSArray *)attributes;

@end

@interface NSMetadataQueryAttributeValueTuple : NSObject {
@private
    id _attr;
    id _value;
    unsigned _count;
    void *_reserved;
}

- (NSString *)attribute;
- (id)value;
- (unsigned)count;

@end

@interface NSMetadataQueryResultGroup : NSObject {
@private
    id _private[9];
    unsigned _private2[1];
    void *_reserved;
}

- (NSString *)attribute;
- (id)value;

- (NSArray *)subgroups; // nil if this is a leaf

- (unsigned)resultCount;
- (id)resultAtIndex:(unsigned)idx; // uncertain whether this will do anything useful for non-leaf groups

- (NSArray *)results;   // this is for K-V Bindings, and causes side-effects on the query

@end

#endif
