//
//  MPRemoteControlTypes.h
//  MediaPlayerFramework
//
//  Copyright (c) 2016 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

typedef NS_ENUM(NSInteger, MPShuffleType) {
    MPShuffleTypeOff,           /// Nothing is shuffled during playback.
    MPShuffleTypeItems,         /// Individual items are shuffled during playback.
    MPShuffleTypeCollections,   /// Collections (e.g. albums) are shuffled during playback.
} NS_ENUM_AVAILABLE(10_12_2, 3_0);

typedef NS_ENUM(NSInteger, MPRepeatType) {
    MPRepeatTypeOff,    /// Nothing is repeated during playback.
    MPRepeatTypeOne,    /// Repeat a single item indefinitely.
    MPRepeatTypeAll,    /// Repeat the current container or playlist indefinitely.
} NS_ENUM_AVAILABLE(10_12_2, 3_0);

typedef NS_ENUM(NSInteger, MPChangeLanguageOptionSetting) {
    MPChangeLanguageOptionSettingNone, /// No Language Option Change
    MPChangeLanguageOptionSettingNowPlayingItemOnly, /// The Language Option change applies only the the now playing item
    MPChangeLanguageOptionSettingPermanent /// The Language Option change should apply to all future playback
} NS_ENUM_AVAILABLE(10_12_2, 9_4);
