//
//  INMediaItemType.h
//  Intents
//
//  Copyright (c) 2016-2021 Apple Inc. All rights reserved.
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
    INMediaItemTypeAlgorithmicRadioStation API_AVAILABLE(ios(13.4), watchos(6.2)),
    INMediaItemTypeNews API_AVAILABLE(ios(13.4.1), watchos(6.2.1)),
} API_AVAILABLE(ios(12.0), watchos(5.0), tvos(14.0)) API_UNAVAILABLE(macos);

#endif // INMediaItemType_h
