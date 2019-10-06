//
//  MPMediaPlaylist.h
//  MediaPlayer
//
//  Copyright 2008 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaItemCollection.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem;

// A playlist may have any number of MPMediaPlaylistAttributes associated.
typedef NS_OPTIONS(NSUInteger, MPMediaPlaylistAttribute) {
    MPMediaPlaylistAttributeNone    = 0,
    MPMediaPlaylistAttributeOnTheGo = (1 << 0), // if set, the playlist was created on a device rather than synced from iTunes
    MPMediaPlaylistAttributeSmart   = (1 << 1),
    MPMediaPlaylistAttributeGenius  = (1 << 2)
} MP_API(ios(3.0)) MP_PROHIBITED(tvos, macos, watchos);

// An MPMediaPlaylist is a collection of related MPMediaItems in an MPMediaLibrary.
// Playlists have a unique identifier which persists across application launches.
MP_API(ios(3.0))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaPlaylist : MPMediaItemCollection

#pragma mark - Properties

// Properties marked filterable can also be used to build MPMediaPropertyPredicates (see MPMediaQuery.h).

MP_EXTERN NSString * const MPMediaPlaylistPropertyPersistentID;                             // filterable
@property (nonatomic, readonly) MPMediaEntityPersistentID persistentID MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaPlaylistPropertyName;                                     // filterable
@property (nonatomic, readonly, nullable) NSString *name MP_API(ios(7.0));

MP_EXTERN NSString * const MPMediaPlaylistPropertyPlaylistAttributes;                       // filterable
@property (nonatomic, readonly) MPMediaPlaylistAttribute playlistAttributes MP_API(ios(7.0));

// For playlists with attribute MPMediaPlaylistAttributeGenius, the seedItems are the MPMediaItems which were used to the generate the playlist.
// Returns nil for playlists without MPMediaPlaylistAttributeGenius set.
MP_EXTERN NSString * const MPMediaPlaylistPropertySeedItems;
@property (nonatomic, readonly, nullable) NSArray<MPMediaItem *> *seedItems MP_API(ios(8.0));

MP_EXTERN NSString * const MPMediaPlaylistPropertyDescriptionText MP_API(ios(9.3));
@property (nonatomic, readonly, nullable) NSString *descriptionText MP_API(ios(9.3));

MP_EXTERN NSString * const MPMediaPlaylistPropertyAuthorDisplayName MP_API(ios(9.3));
@property (nonatomic, readonly, nullable) NSString *authorDisplayName MP_API(ios(9.3));

- (void)addItemWithProductID:(NSString *)productID completionHandler:(nullable void (^)(NSError * __nullable error))completionHandler MP_API(ios(9.3));
- (void)addMediaItems:(NSArray<MPMediaItem *> *)mediaItems completionHandler:(nullable void (^)(NSError * __nullable error))completionHandler MP_API(ios(9.3));

@end

MP_API(ios(9.3))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaPlaylistCreationMetadata : NSObject

- (id)init NS_UNAVAILABLE;
- (instancetype)initWithName:(NSString *)name NS_DESIGNATED_INITIALIZER;

/// The display name of the playlist.
@property (nonatomic, readonly, copy) NSString *name;
/// Defaults to the requesting app's display name.
@property (null_resettable, nonatomic, copy) NSString *authorDisplayName;
@property (nonatomic, copy) NSString *descriptionText;

@end

NS_ASSUME_NONNULL_END
