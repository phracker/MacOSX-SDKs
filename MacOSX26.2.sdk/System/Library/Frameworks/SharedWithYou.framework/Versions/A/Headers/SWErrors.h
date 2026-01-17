//
//  SWErrors.h
//  SWErrorDomains
//
//  Copyright (c) 2021 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SharedWithYouCore/SWDefines.h>

typedef NS_ENUM(NSInteger, SWHighlightCenterErrorCode) {
    SWHighlightCenterErrorCodeNoError = 0,
    SWHighlightCenterErrorCodeInternalError,
    SWHighlightCenterErrorCodeInvalidURL,
    SWHighlightCenterErrorCodeAccessDenied,
} API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0));
