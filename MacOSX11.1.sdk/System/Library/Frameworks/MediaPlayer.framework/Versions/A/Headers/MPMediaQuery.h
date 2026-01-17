//
//  MPMediaQuery.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaPredicate;
@class MPMediaQuerySection;

typedef NS_ENUM(NSInteger, MPMediaGrouping) {
    MPMediaGroupingTitle,
    MPMediaGroupingAlbum,
    MPMediaGroupingArtist,
    MPMediaGroupingAlbumArtist,
    MPMediaGroupingComposer,
    MPMediaGroupingGenre,
    MPMediaGroupingPlaylist,
    MPMediaGroupingPodcastTitle
} MP_API(ios(3.0)) API_UNAVAILABLE(tvos, watchos, macos);

// MPMediaQuery represents a collection of items or playlists determined by a chain of MPMediaPredicate objects.
MP_API(ios(3.0))
API_UNAVAILABLE(tvos, watchos, macos)
@interface MPMediaQuery : NSObject <NSSecureCoding, NSCopying>

- (instancetype)initWithFilterPredicates:(nullable NSSet<MPMediaPredicate *> *)filterPredicates NS_DESIGNATED_INITIALIZER;
@property (nonatomic, strong, nullable) NSSet<MPMediaPredicate *> *filterPredicates;

- (void)addFilterPredicate:(MPMediaPredicate *)predicate;
- (void)removeFilterPredicate:(MPMediaPredicate *)predicate;

// Returns an array of MPMediaItems matching the query filter predicates.
// If no items match this method returns an empty array, otherwise returns nil if an error prevents the items from being fetched.
@property (nonatomic, readonly, nullable) NSArray<MPMediaItem *> *items;

// Returns an array of MPMediaItemCollections matching the query filter predicates. The collections are grouped by the groupingType.
@property (nonatomic, readonly, nullable) NSArray<MPMediaItemCollection *> *collections;

// The property used to group collections, defaults to MPMediaGroupingTitle.
@property (nonatomic) MPMediaGrouping groupingType;

// Returns an array of MPMediaQuerySection instances representing the section grouping of the query's items or collections.
// May be nil in cases where no section grouping of the items or collections is appropriate.
@property (nonatomic, readonly, nullable) NSArray<MPMediaQuerySection *> *itemSections MP_API(ios(4.2));
@property (nonatomic, readonly, nullable) NSArray<MPMediaQuerySection *> *collectionSections MP_API(ios(4.2));

// Base queries which can be used directly or as the basis for custom queries.
// The groupingType for these queries is preset to the appropriate type for the query.
+ (MPMediaQuery *)albumsQuery;
+ (MPMediaQuery *)artistsQuery;
+ (MPMediaQuery *)songsQuery;
+ (MPMediaQuery *)playlistsQuery;
+ (MPMediaQuery *)podcastsQuery;
+ (MPMediaQuery *)audiobooksQuery;
+ (MPMediaQuery *)compilationsQuery;
+ (MPMediaQuery *)composersQuery;
+ (MPMediaQuery *)genresQuery;

@end

// ------------------------------------------------------------------------
// MPMediaPredicate is an abstract class that allows filtering media in an MPMediaQuery.
// See the concrete subclass MPMediaPropertyPredicate for filtering options.

MP_API(ios(3.0))
API_UNAVAILABLE(tvos, watchos, macos)
@interface MPMediaPredicate : NSObject <NSSecureCoding> {}
@end

// ------------------------------------------------------------------------
// MPMediaPropertyPredicate allows filtering based on a specific property value of an item or collection.
// See MPMediaItem.h and MPMediaPlaylist.h for a list of properties.

typedef NS_ENUM(NSInteger, MPMediaPredicateComparison) {
    MPMediaPredicateComparisonEqualTo,
    MPMediaPredicateComparisonContains
} MP_API(ios(3.0)) API_UNAVAILABLE(tvos, watchos, macos);

MP_API(ios(3.0))
API_UNAVAILABLE(tvos, watchos, macos)
@interface MPMediaPropertyPredicate : MPMediaPredicate

+ (MPMediaPropertyPredicate *)predicateWithValue:(nullable id)value forProperty:(NSString *)property; // comparisonType is MPMediaPredicateComparisonEqualTo
+ (MPMediaPropertyPredicate *)predicateWithValue:(nullable id)value forProperty:(NSString *)property comparisonType:(MPMediaPredicateComparison)comparisonType;

@property (nonatomic, readonly, copy) NSString *property;
@property (nonatomic, readonly, copy, nullable) id value;
@property (nonatomic, readonly) MPMediaPredicateComparison comparisonType;

@end

// ------------------------------------------------------------------------
// Convenience methods to determine item properties corresponding to a given grouping type.

@interface MPMediaItem (MPMediaQueryAdditions)

// Returns the item property for a given grouping type.
// For example, [MPMediaItem persistentIDPropertyForGroupingType:MPMediaGroupingAlbum] returns MPMediaItemPropertyAlbumPersistentID.
+ (NSString *)persistentIDPropertyForGroupingType:(MPMediaGrouping)groupingType
    MP_API(ios(4.2))
    API_UNAVAILABLE(tvos, watchos, macos);

// Returns the item property to determine a title for a given grouping type.
// For example, [MPMediaItem titlePropertyForGroupingType:MPMediaGroupingAlbum] returns MPMediaItemPropertyAlbumTitle.
// Note that distinct collections will not necessarily have unique titles, e.g. an album may exist with the title "Greatest Hits" for multiple artists.
+ (NSString *)titlePropertyForGroupingType:(MPMediaGrouping)groupingType
    MP_API(ios(4.2))
    API_UNAVAILABLE(tvos, watchos, macos);

@end

NS_ASSUME_NONNULL_END
