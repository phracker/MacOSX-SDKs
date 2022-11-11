//
//  QLFilePreviewRequest.h
//  QuickLook
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <QuickLook/QLBase.h>

#if !defined(USE_PUBLIC_QUICKLOOK_HEADERS) && !defined(USE_PUBLIC_QUICKLOOK_HEADERS_CATALYST) && __has_include(<QuickLookSupport/QLPreviewReply.h>)
#import <QuickLookSupport/QLFilePreviewRequest.h>
#else

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract This class contains information about the preview that should be provided.
 */
API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(watchos,tvos)  __attribute__((visibility("default")))
QL_EXPORT @interface QLFilePreviewRequest : NSObject

/**
 The url of the file for which a preview is being requested.
 */
@property (readonly) NSURL* fileURL;

@end

NS_ASSUME_NONNULL_END

#endif
