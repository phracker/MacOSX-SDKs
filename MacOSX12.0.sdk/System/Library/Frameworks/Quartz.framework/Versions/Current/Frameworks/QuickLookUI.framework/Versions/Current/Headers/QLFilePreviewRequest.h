//
//  QLFilePreviewRequest.h
//  Quick Look
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#if !__has_include(<QuickLookSupport/QLFilePreviewRequest.h>)

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract This class contains information about the preview that should be provided.
 */
API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(watchos,tvos)  __attribute__((visibility("default")))
@interface QLFilePreviewRequest : NSObject

/**
 The url of the file for which a preview is being requested.
 */
@property (readonly) NSURL* fileURL;

@end

NS_ASSUME_NONNULL_END

#else
#import <QuickLookSupport/QLFilePreviewRequest.h>
#endif
