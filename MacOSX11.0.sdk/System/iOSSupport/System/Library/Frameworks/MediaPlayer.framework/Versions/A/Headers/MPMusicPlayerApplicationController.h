//
//  MPMusicPlayerApplicationController.h
//  MediaPlayer
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaItem.h>
#import <MediaPlayer/MPMusicPlayerController.h>

NS_ASSUME_NONNULL_BEGIN

MP_API(ios(10.3), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@interface MPMusicPlayerControllerQueue : NSObject

MP_INIT_UNAVAILABLE

@property (nonatomic, copy, readonly) NSArray<MPMediaItem *> *items;

@end

MP_API(ios(10.3), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@interface MPMusicPlayerControllerMutableQueue : MPMusicPlayerControllerQueue

- (void)insertQueueDescriptor:(MPMusicPlayerQueueDescriptor *)queueDescriptor afterItem:(nullable MPMediaItem *)afterItem;
- (void)removeItem:(MPMediaItem *)item;

@end

MP_API(ios(10.3), tvos(14.0))
API_UNAVAILABLE(watchos, macos)
@interface MPMusicPlayerApplicationController : MPMusicPlayerController

- (void)performQueueTransaction:(void (^)(MPMusicPlayerControllerMutableQueue *queue))queueTransaction completionHandler:(void (^)(MPMusicPlayerControllerQueue *queue, NSError *_Nullable error))completionHandler;

@end

// Posted when the queue changes
MP_EXTERN NSString * const MPMusicPlayerControllerQueueDidChangeNotification
    MP_API(ios(10.3), tvos(14.0))
    API_UNAVAILABLE(watchos, macos);

NS_ASSUME_NONNULL_END
