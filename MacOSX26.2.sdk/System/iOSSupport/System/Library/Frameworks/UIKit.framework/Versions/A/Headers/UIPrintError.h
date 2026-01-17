#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<PrintKitUI/UIPrintError.h>)
//
//  UIPrintError.h
//  UIKit
//
//  Copyright 2010-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN NSErrorDomain const UIPrintErrorDomain API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(tvos, watchos);

typedef NS_ERROR_ENUM(UIPrintErrorDomain, UIPrintErrorCode) {
    UIPrintingNotAvailableError = 1,  // cannot print at this time
    UIPrintNoContentError,            // empty list of files or images
    UIPrintUnknownImageFormatError,   // unrecognized image format
    UIPrintJobFailedError,            // internal error with print job
} API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(tvos, watchos);

NS_ASSUME_NONNULL_END

#else
#import <PrintKitUI/UIPrintError.h>
#endif
