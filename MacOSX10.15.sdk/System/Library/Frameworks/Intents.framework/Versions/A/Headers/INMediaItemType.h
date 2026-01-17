//
//  INMediaItemType.h
//  Intents
//
//  Copyright (c) 2016-2019 Apple Inc. All rights reserved.
//

#ifndef INMediaItemType_h
#define INMediaItemType_h

#import <Foundation/Foundation.h>
#import <Intents/IntentsDefines.h>

typedef NS_ENUM(NSInteger, INMediaItemType) {
    INMediaItemTypeUnknown = 0,
    INMediaItemTypeSong,
    INMediaItemTypeAlbum,
    INMediaItemTypeArtist,
    INMediaItemTypeGenre,
    INMediaItemTypePlaylist,
    INMediaItemTypePodcastShow,
    INMediaItemTypePodcastEpisode,
    INMediaItemTypePodcastPlaylist,
    INMediaItemTypeMusicStation,
    INMediaItemTypeAudioBook,
    INMediaItemTypeMovie,
    INMediaItemTypeTVShow,
    INMediaItemTypeTVShowEpisode,
    INMediaItemTypeMusicVideo,
    INMediaItemTypePodcastStation API_AVAILABLE(ios(13.0), watchos(6.0)),
    INMediaItemTypeRadioStation API_AVAILABLE(ios(13.0), watchos(6.0)),
    INMediaItemTypeStation API_AVAILABLE(ios(13.0), watchos(6.0)),
    INMediaItemTypeMusic API_AVAILABLE(ios(13.0), watchos(6.0)),
} API_AVAILABLE(ios(12.0), watchos(5.0)) API_UNAVAILABLE(macosx);

#endif // INMediaItemType_h
