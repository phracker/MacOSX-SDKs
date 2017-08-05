//
//  MPPlayableContentManagerContext.h
//  MobileMusicPlayer
//
//  Copyright © 2015 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayerDefines.h>

/// MPPlayableContentManagerContext represents the current state of
/// the playable content endpoint. A context is retrievable from an instance
/// of MPPlayableContentManager.
MP_API(ios(8.4))
MP_PROHIBITED(tvos, macos)
@interface MPPlayableContentManagerContext : NSObject

/// The number of items the content server will display when content limiting is enforced.
/// Returns NSIntegerMax if the content server will never limit the number of items.
@property (nonatomic, readonly) NSInteger enforcedContentItemsCount;

/// The depth of the navigation hierarchy the content server will allow. Exceeding this limit will result in a crash.
@property (nonatomic, readonly) NSInteger enforcedContentTreeDepth;

/// Represents whether content limits are being enforced by the content server or not.
@property (nonatomic, readonly) BOOL contentLimitsEnforced;
@property (nonatomic, readonly) BOOL contentLimitsEnabled MP_DEPRECATED_WITH_REPLACEMENT("contentLimitsEnforced", ios(8.4, 9.0));

/// Represents whether the content server is available or not.
@property (nonatomic, readonly) BOOL endpointAvailable;

@end
