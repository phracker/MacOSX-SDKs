//
//  MPMediaQuerySection.h
//  MediaPlayer
//
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <MediaPlayer/MediaPlayerDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// An MPMediaQuerySection object represents a single section grouping for a query.
MP_API(ios(4.2))
MP_PROHIBITED(tvos, macos, watchos)
@interface MPMediaQuerySection : NSObject <NSSecureCoding, NSCopying>

// The localized title of the section grouping.
@property (nonatomic, copy, readonly) NSString *title;

// The range in the query's corresponding collections or items array represented by this section.
@property (nonatomic, assign, readonly) NSRange range;

@end

NS_ASSUME_NONNULL_END
