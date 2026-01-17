//
//  QLPreviewProvider.h
//  QuickLook
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#if !defined(USE_PUBLIC_QUICKLOOK_HEADERS) && !defined(USE_PUBLIC_QUICKLOOK_HEADERS_CATALYST) && __has_include(<QuickLookSupport/QLPreviewReply.h>)
#import <QuickLookSupport/QLPreviewProvider.h>
#else

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract Data-based preview extensions should subclass QLPreviewProvider in their principal object. The subclass should conform to QLPreviewingController.
 
 */
API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(watchos,tvos)  __attribute__((visibility("default")))
@interface QLPreviewProvider : NSObject <NSExtensionRequestHandling>

@end

NS_ASSUME_NONNULL_END

#endif
