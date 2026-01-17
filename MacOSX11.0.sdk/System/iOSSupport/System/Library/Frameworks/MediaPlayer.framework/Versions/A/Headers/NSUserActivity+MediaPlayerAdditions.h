//
//  NSUserActivity+MediaPlayerAdditions.h
//  MediaPlayer
//
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSUserActivity (MediaPlayerAdditions)

/// A unique identifier relative to the app's media content catalog for the displayed media item.
@property (nonatomic, copy, nullable) NSString *externalMediaContentIdentifier MP_API(ios(10.1), tvos(10.0.1)) MP_UNAVAILABLE(watchos, macos);

@end

NS_ASSUME_NONNULL_END
