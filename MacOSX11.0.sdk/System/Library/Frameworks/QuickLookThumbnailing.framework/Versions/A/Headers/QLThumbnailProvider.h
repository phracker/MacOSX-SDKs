//
//  QLThumbnailProvider.h
//  Mobile Quick Look
//
//  Copyright 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class QLFileThumbnailRequest, QLThumbnailReply;

API_AVAILABLE(ios(11.0), macos(10.15)) API_UNAVAILABLE(tvos, watchos) __attribute__((visibility("default")))
@interface QLThumbnailProvider : NSObject

/**
 Subclass this method to provide a QLThumbnailReply that either contains a drawing block or an image file URL.


 @param request An object which contains information about the thumbnail that should be provided. It contains the URL of the file to provide a thumbnail for.
 @param handler Call the completion handler with a QLThumbnailReply if you can provide a thumbnail, or with an NSError if you cannot.
                If an error is passed or reply is nil, no thumbnail will be drawn.
                The handler can be called asynchronously after the method has returned.
 */
- (void)provideThumbnailForFileRequest:(QLFileThumbnailRequest *)request completionHandler:(void (^)(QLThumbnailReply * _Nullable reply, NSError * _Nullable error))handler NS_SWIFT_NAME(provideThumbnail(for:_:));

@end

NS_ASSUME_NONNULL_END
