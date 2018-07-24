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
} MP_API(ios(3.0), macos(10.12.2), watchos(5.0));

typedef NS_ENUM(NSInteger, MPRepeatType) {
    MPRepeatTypeOff,    /// Nothing is repeated during playback.
    MPRepeatTypeOne,    /// Repeat a single item indefinitely.
    MPRepeatTypeAll,    /// Repeat the current container or playlist indefinitely.
} MP_API(ios(3.0), macos(10.12.2), watchos(5.0));

typedef NS_ENUM(NSInteger, MPChangeLanguageOptionSetting) {
    MPChangeLanguageOptionSettingNone, /// No Language Option Change
    MPChangeLanguageOptionSettingNowPlayingItemOnly, /// The Language Option change applies only the the now playing item
    MPChangeLanguageOptionSettingPermanent /// The Language Option change should apply to all future playback
} MP_API(ios(9.3), macos(10.12.2), watchos(5.0));
