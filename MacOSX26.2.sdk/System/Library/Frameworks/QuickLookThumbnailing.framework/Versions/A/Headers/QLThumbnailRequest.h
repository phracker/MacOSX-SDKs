//
//  QLThumbnailRequest.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract This class contains information about the thumbnail that should be provided.
 */
API_AVAILABLE(ios(11.0), macos(10.15)) API_UNAVAILABLE(watchos, tvos)  __attribute__((visibility("default")))
@interface QLFileThumbnailRequest : NSObject

/**
The maximum size of the generated thumbnail that will be accepted. This is also the preferred size, ideally either the width or the height will match the maximumSize's width or height respectively.
 */
@property (nonatomic, readonly) CGSize maximumSize;

/**
 The minimum size of the generated thumbnail that will be accepted.
 */
@property (nonatomic, readonly) CGSize minimumSize;

/**
 The scale of the requested thumbnail.
 */
@property (nonatomic, readonly) CGFloat scale;

/**
 The url of the file for which a thumbnail is being requested.
 */
@property (nonatomic, copy, readonly) NSURL* fileURL;

@end

NS_ASSUME_NONNULL_END
