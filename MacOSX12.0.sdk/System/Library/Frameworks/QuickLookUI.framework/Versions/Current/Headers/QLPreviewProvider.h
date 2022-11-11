//
//  QLPreviewProvider.h
//  Quick Look
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#if !__has_include(<QuickLookSupport/QLPreviewProvider.h>)

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract Data-based preview extensions should subclass QLPreviewProvider in their principal object. The subclass should conform to QLPreviewingController.
 
 */
API_AVAILABLE(ios(15.0), macos(12.0)) API_UNAVAILABLE(watchos,tvos)  __attribute__((visibility("default")))
@interface QLPreviewProvider : NSObject <NSExtensionRequestHandling>

@end

NS_ASSUME_NONNULL_END

#else
#import <QuickLookSupport/QLPreviewProvider.h>
#endif
