/*	NSMetadata.h
	Copyright (c) 2004-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSMetadataAttributes.h>

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>

@class NSString, NSURL, NSArray, NSDictionary, NSPredicate, NSOperationQueue;
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

@property (assign) id<NSMetadataQueryDelegate> delegate;
@property (copy) NSPredicate *predicate;
@property (copy) NSArray *sortDescriptors;
@property (copy) NSArray *valueListAttributes;
@property (copy) NSArray *groupingAttributes;
@property NSTimeInterval notificationBatchingInterval;

@property (copy) NSArray *searchScopes;
// scopes is an NSArray of NSURL objects (file URLs only) and/or string
// paths and/or the special string constants below, which specifies the
// locations to which the search is limited; an empty array means no
// limits, which is the default state.

@property (copy) NSArray *searchItems NS_AVAILABLE(10_9, 7_0);
// items can be a mixture of NSMetadataItem, NSURL objects (file URLs only)
// and/or string paths; the getter returns the same mixture as was set

@property (retain) NSOperationQueue *operationQueue NS_AVAILABLE(10_9, 7_0);
// optional operation queue for notifications and delegate method calls

- (BOOL)startQuery;
- (void)stopQuery;

@property (readonly, getter=isStarted) BOOL started;
@property (readonly, getter=isGathering) BOOL gathering;
@property (readonly, getter=isStopped) BOOL stopped;

- (void)disableUpdates; // these nest
- (void)enableUpdates;


// Results are NSMetadataItems, or whatever the delegate replaces that with
@property (readonly) NSUInteger resultCount;
- (id)resultAtIndex:(NSUInteger)idx;

- (void)enumerateResultsUsingBlock:(void (^)(id result, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_9, 7_0);
- (void)enumerateResultsWithOptions:(NSEnumerationOptions)opts usingBlock:(void (^)(id result, NSUInteger idx, BOOL *stop))block NS_AVAILABLE(10_9, 7_0);

@property (readonly, copy) NSArray *results;   // this is for K-V Bindings, and causes side-effects on the query

- (NSUInteger)indexOfResult:(id)result;

@property (readonly, copy) NSDictionary *valueLists; // values are arrays of NSMetadataQueryAttributeValueTuple

@property (readonly, copy) NSArray *groupedResults; // array of NSMetadataQueryResultGroups, for first grouping attribute

- (id)valueOfAttribute:(NSString *)attrName forResultAtIndex:(NSUInteger)idx;

@end

@protocol NSMetadataQueryDelegate <NSObject>
@optional

- (id)metadataQuery:(NSMetadataQuery *)query replacementObjectForResultObject:(NSMetadataItem *)result;
- (id)metadataQuery:(NSMetadataQuery *)query replacementValueForAttribute:(NSString *)attrName value:(id)attrValue;

@end

// notifications
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidStartGatheringNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryGatheringProgressNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidFinishGatheringNotification NS_AVAILABLE(10_4, 5_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryDidUpdateNotification NS_AVAILABLE(10_4, 5_0);

// keys for use with notification info dictionary
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateAddedItemsKey NS_AVAILABLE(10_9, 8_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateChangedItemsKey NS_AVAILABLE(10_9, 8_0);
FOUNDATION_EXPORT NSString * const NSMetadataQueryUpdateRemovedItemsKey NS_AVAILABLE(10_9, 8_0);

FOUNDATION_EXPORT NSString * const NSMetadataQueryResultContentRelevanceAttribute NS_AVAILABLE(10_4, 5_0);

// Scope constants for defined search locations
FOUNDATION_EXPORT NSString * const NSMetadataQueryUserHomeScope NS_AVAILABLE_MAC(10_4); // user home directory
FOUNDATION_EXPORT NSString * const NSMetadataQueryLocalComputerScope NS_AVAILABLE_MAC(10_4); // all local mounted volumes + user home (even if remote)
FOUNDATION_EXPORT NSString * const NSMetadataQueryNetworkScope NS_AVAILABLE_MAC(10_4); // all user-mounted remote volumes

FOUNDATION_EXPORT NSString * const NSMetadataQueryIndexedLocalComputerScope NS_AVAILABLE_MAC(10_9); // all indexed local mounted volumes + user home (even if remote)
FOUNDATION_EXPORT NSString * const NSMetadataQueryIndexedNetworkScope NS_AVAILABLE_MAC(10_9); // all indexed user-mounted remote volumes

// -setSearchScopes: will throw an exception if the given array contains a mix of the scope constants below with constants above.
FOUNDATION_EXPORT NSString * const NSMetadataQueryUbiquitousDocumentsScope NS_AVAILABLE(10_7, 5_0); // "Documents" subdirectory in the application's Ubiquity container
FOUNDATION_EXPORT NSString * const NSMetadataQueryUbiquitousDataScope NS_AVAILABLE(10_7, 5_0); // application's Ubiquity container, excluding the "Documents" subdirectory
FOUNDATION_EXPORT NSString * const NSMetadataQueryAccessibleUbiquitousExternalDocumentsScope NS_AVAILABLE(10_10, 8_0); // documents from outside the application's container that are accessible without user interaction. NSMetadataItemURLKey attributes of results are security-scoped NSURLs.


NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataItem : NSObject {
@private
    id _item;
    __strong void *_reserved;
}

- (instancetype)initWithURL:(NSURL *)url NS_DESIGNATED_INITIALIZER NS_AVAILABLE_MAC(10_9);

- (id)valueForAttribute:(NSString *)key;
- (NSDictionary *)valuesForAttributes:(NSArray *)keys;

@property (readonly, copy) NSArray *attributes;

@end

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataQueryAttributeValueTuple : NSObject {
@private
    id _attr;
    id _value;
    NSUInteger _count;
    void *_reserved;
}

@property (readonly, copy) NSString *attribute;
@property (readonly, retain) id value;
@property (readonly) NSUInteger count;

@end

NS_CLASS_AVAILABLE(10_4, 5_0)
@interface NSMetadataQueryResultGroup : NSObject {
@private
    id _private[9];
    NSUInteger _private2[1];
    void *_reserved;
}

@property (readonly, copy) NSString *attribute;
@property (readonly, retain) id value;

@property (readonly, copy) NSArray *subgroups; // nil if this is a leaf

@property (readonly) NSUInteger resultCount;
- (id)resultAtIndex:(NSUInteger)idx; // uncertain whether this will do anything useful for non-leaf groups

@property (readonly, copy) NSArray *results;   // this is for K-V Bindings, and causes side-effects on the query

@end
