//
//  MPMusicPlayerQueueDescriptor.h
//  MediaPlayerFramework
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MPMediaItem, MPMediaItemCollection, MPMediaQuery;

MP_API(ios(10.1), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@interface MPMusicPlayerQueueDescriptor : NSObject
MP_INIT_UNAVAILABLE
@end

MP_API(ios(10.1))
API_UNAVAILABLE(tvos, watchos, macos)
@interface MPMusicPlayerMediaItemQueueDescriptor : MPMusicPlayerQueueDescriptor

- (instancetype)initWithQuery:(MPMediaQuery *)query;
- (instancetype)initWithItemCollection:(MPMediaItemCollection *)itemCollection;

@property (nonatomic, readonly, copy) MPMediaQuery *query;
@property (nonatomic, readonly, strong) MPMediaItemCollection *itemCollection;
@property (nonatomic, nullable, strong) MPMediaItem *startItem;

- (void)setStartTime:(NSTimeInterval)startTime forItem:(MPMediaItem *)mediaItem;
- (void)setEndTime:(NSTimeInterval)endTime forItem:(MPMediaItem *)mediaItem;

@end

MP_API(ios(10.1), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@interface MPMusicPlayerStoreQueueDescriptor : MPMusicPlayerQueueDescriptor

- (instancetype)initWithStoreIDs:(NSArray<NSString *> *)storeIDs;

@property (nonatomic, nullable, copy) NSArray<NSString *> *storeIDs;
@property (nonatomic, nullable, copy) NSString *startItemID;

- (void)setStartTime:(NSTimeInterval)startTime forItemWithStoreID:(NSString *)storeID;
- (void)setEndTime:(NSTimeInterval)endTime forItemWithStoreID:(NSString *)storeID;

@end

MP_API(ios(11.0), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@interface MPMusicPlayerPlayParameters : NSObject

- (nullable instancetype)initWithDictionary:(NSDictionary<NSString *, id> *)dictionary;

@property (nonatomic, readonly, copy) NSDictionary<NSString *, id> *dictionary;

@end

MP_API(ios(11.0), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@interface MPMusicPlayerPlayParametersQueueDescriptor : MPMusicPlayerQueueDescriptor

- (instancetype)initWithPlayParametersQueue:(NSArray<MPMusicPlayerPlayParameters *> *)playParametersQueue;

@property (nonatomic, copy) NSArray<MPMusicPlayerPlayParameters *> *playParametersQueue;
@property (nonatomic, nullable, strong) MPMusicPlayerPlayParameters *startItemPlayParameters;

- (void)setStartTime:(NSTimeInterval)startTime forItemWithPlayParameters:(MPMusicPlayerPlayParameters *)playParameters;
- (void)setEndTime:(NSTimeInterval)endTime forItemWithPlayParameters:(MPMusicPlayerPlayParameters *)playParameters;

@end

NS_ASSUME_NONNULL_END
