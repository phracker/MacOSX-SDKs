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
MP_API_IOS_AVAILABLE_MACOS_TVOS_PROHIBITED(8.4, 10.12.2, 8.4)
@interface MPPlayableContentManagerContext : NSObject

/// The number of items the content server will display when content limiting is enforced.
/// Returns NSIntegerMax if the content server will never limit the number of items.
@property (nonatomic, readonly) NSInteger enforcedContentItemsCount;

/// The depth of the navigation hierarchy the content server will allow. Exceeding this limit will result in a crash.
@property (nonatomic, readonly) NSInteger enforcedContentTreeDepth;

/// Represents whether content limits are being enforced by the content server or not.
@property (nonatomic, readonly) BOOL contentLimitsEnforced;
@property (nonatomic, readonly) BOOL contentLimitsEnabled NS_DEPRECATED_IOS(8_4, 9_0, "Use contentLimitsEnforced");

/// Represents whether the content server is available or not.
@property (nonatomic, readonly) BOOL endpointAvailable;

@end
