/*	NSMetadata.h
	Copyright (c) 2004-2012, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSString, NSArray, NSDictionary, NSPredicate;
@class NSMetadataItem, NSMetadataQueryAttributeValueTuple, NSMetadataQueryResultGroup;
@protocol NSMetadataQueryDelegate;

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataQuery : NSObject {
@private
    NSUInteger _flags;
    NSTimeInterval _interval;
    id _private[11];
    __strong void *_reserved;
}

- (id)init;

- (id <NSMetadataQueryDelegate>)delegate;
- (void)setDelegate:(id <NSMetadataQueryDelegate>)delegate;

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
- (NSUInteger)resultCount;
- (id)resultAtIndex:(NSUInteger)idx;

- (NSArray *)results;   // this is for K-V Bindings, and causes side-effects on the query

- (NSUInteger)indexOfResult:(id)result;

- (NSDictionary *)valueLists; // values are arrays of NSMetadataQueryAttributeValueTuple

- (NSArray *)groupedResults; // array of NSMetadataQueryResultGroups, for first grouping attribute

- (id)valueOfAttribute:(NSString *)attrName forResultAtIndex:(NSUInteger)idx;

@end

@protocol NSMetadataQueryDelegate <NSObject>
@optional

- (id)metadataQuery:(NSMetadataQuery *)query replacementObjectForResultObject:(NSMetadataItem *)result;
- (id)metadataQuery:(NSMetadataQuery *)query replacementValueForAttribute:(NSString *)attrName value:(id)attrValue;

@end

// There is no info associated with these notifications
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidStartGatheringNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryGatheringProgressNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidFinishGatheringNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidUpdateNotification NS_AVAILABLE(10_4, 5_0);

FOUNDATION_EXPORT NSString * const NSMetadataQueryResultContentRelevanceAttribute NS_AVAILABLE(10_4, 5_0);

// Scope constants for defined search locations
FOUNDATION_EXPORT NSString * const NSMetadataQueryUserHomeScope NS_AVAILABLE_MAC(10_4); // user home directory
FOUNDATION_EXPORT NSString * const NSMetadataQueryLocalComputerScope NS_AVAILABLE_MAC(10_4); // all local mounted volumes + user home (even if remote)
FOUNDATION_EXPORT NSString * const NSMetadataQueryNetworkScope NS_AVAILABLE_MAC(10_4); // all user-mounted remote volumes

// -setSearchScopes: will throw an exception if the given array contains a mix of the scope constants below with constants above.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUbiquitousDocumentsScope NS_AVAILABLE(10_7, 5_0); // "Documents" subdirectory in the application's Ubiquity container
FOUNDATION_EXPORT NSString * const NSMetadataQueryUbiquitousDataScope NS_AVAILABLE(10_7, 5_0); // application's Ubiquity container, excluding the "Documents" subdirectory


NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataItem : NSObject {
@private
    id _item;
    __strong void *_reserved;
}

- (id)valueForAttribute:(NSString *)key;
- (NSDictionary *)valuesForAttributes:(NSArray *)keys;

- (NSArray *)attributes;

@end

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataQueryAttributeValueTuple : NSObject {
@private
    id _attr;
    id _value;
    NSUInteger _count;
    void *_reserved;
}

- (NSString *)attribute;
- (id)value;
- (NSUInteger)count;

@end

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataQueryResultGroup : NSObject {
@private
    id _private[9];
    NSUInteger _private2[1];
    void *_reserved;
}

- (NSString *)attribute;
- (id)value;

- (NSArray *)subgroups; // nil if this is a leaf

- (NSUInteger)resultCount;
- (id)resultAtIndex:(NSUInteger)idx; // uncertain whether this will do anything useful for non-leaf groups

- (NSArray *)results;   // this is for K-V Bindings, and causes side-effects on the query

@end

// The following NSMetadataItem attributes are available on Mac OS and iOS. See <Metadata/MDItem.h> for more attribute names on Mac OS.
FOUNDATION_EXPORT NSString * const NSMetadataItemFSNameKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemDisplayNameKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemURLKey NS_AVAILABLE(10_7, 5_0); // NSURL
FOUNDATION_EXPORT NSString * const NSMetadataItemPathKey NS_AVAILABLE(10_7, 5_0); // NSString
FOUNDATION_EXPORT NSString * const NSMetadataItemFSSizeKey NS_AVAILABLE(10_7, 5_0); // file size in bytes; unsigned long long NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataItemFSCreationDateKey NS_AVAILABLE(10_7, 5_0); // NSDate
FOUNDATION_EXPORT NSString * const NSMetadataItemFSContentChangeDateKey NS_AVAILABLE(10_7, 5_0); // NSDate

FOUNDATION_EXPORT NSString * const NSMetadataItemIsUbiquitousKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber

FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemHasUnresolvedConflictsKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsDownloadedKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsDownloadingKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsUploadedKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemIsUploadingKey NS_AVAILABLE(10_7, 5_0); // boolean NSNumber
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemPercentDownloadedKey NS_AVAILABLE(10_7, 5_0); // double NSNumber; range [0..100]
FOUNDATION_EXPORT NSString * const NSMetadataUbiquitousItemPercentUploadedKey NS_AVAILABLE(10_7, 5_0); // double NSNumber; range [0..100]
