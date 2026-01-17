#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIGraphics.h>)
//
//  UIGraphics.h
//  UIKit
//
//  Copyright (c) 2005-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage;

UIKIT_EXTERN CGContextRef __nullable UIGraphicsGetCurrentContext(void) CF_RETURNS_NOT_RETAINED API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN void UIGraphicsPushContext(CGContextRef context) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN void UIGraphicsPopContext(void) API_AVAILABLE(watchos(2.0));

UIKIT_EXTERN void UIRectFillUsingBlendMode(CGRect rect, CGBlendMode blendMode) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN void UIRectFill(CGRect rect) API_AVAILABLE(watchos(2.0));

UIKIT_EXTERN void UIRectFrameUsingBlendMode(CGRect rect, CGBlendMode blendMode) API_AVAILABLE(watchos(2.0));
UIKIT_EXTERN void UIRectFrame(CGRect rect) API_AVAILABLE(watchos(2.0));

UIKIT_EXTERN void UIRectClip(CGRect rect) API_AVAILABLE(watchos(2.0));

// UIImage context

// The following methods will only return a 8-bit per channel context in the DeviceRGB color space.
// Any new bitmap drawing code is encouraged to use UIGraphicsImageRenderer in lieu of this API.
UIKIT_EXTERN void     UIGraphicsBeginImageContext(CGSize size) API_DEPRECATED("Replace usage of UIGraphicsBeginImageContext with UIGraphicsImageRenderer.", ios(2.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
UIKIT_EXTERN void     UIGraphicsBeginImageContextWithOptions(CGSize size, BOOL opaque, CGFloat scale) API_DEPRECATED("Replace usage of UIGraphicsBeginImageContextWithOptions with UIGraphicsImageRenderer.", ios(4.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
UIKIT_EXTERN UIImage* __nullable UIGraphicsGetImageFromCurrentImageContext(void) API_DEPRECATED("Replace usage of UIGraphicsGetImageFromCurrentImageContext with UIGraphicsImageRendererContext.currentImage.", ios(2.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));
UIKIT_EXTERN void     UIGraphicsEndImageContext(void) API_DEPRECATED("UIGraphicsEndImageContext should only be used alongside UIGraphicsBeginImageContext[WithOptions].", ios(2.0, API_TO_BE_DEPRECATED), visionos(1.0, API_TO_BE_DEPRECATED), watchos(2.0, API_TO_BE_DEPRECATED));

// PDF context

UIKIT_EXTERN BOOL UIGraphicsBeginPDFContextToFile(NSString *path, CGRect bounds, NSDictionary * __nullable documentInfo) API_AVAILABLE(ios(3.2), watchos(2.0));
UIKIT_EXTERN void UIGraphicsBeginPDFContextToData(NSMutableData *data, CGRect bounds, NSDictionary * __nullable documentInfo) API_AVAILABLE(ios(3.2), watchos(2.0));
UIKIT_EXTERN void UIGraphicsEndPDFContext(void) API_AVAILABLE(ios(3.2), watchos(2.0));

UIKIT_EXTERN void UIGraphicsBeginPDFPage(void) API_AVAILABLE(ios(3.2), watchos(2.0));
UIKIT_EXTERN void UIGraphicsBeginPDFPageWithInfo(CGRect bounds, NSDictionary * __nullable pageInfo) API_AVAILABLE(ios(3.2), watchos(2.0));

UIKIT_EXTERN CGRect UIGraphicsGetPDFContextBounds(void) API_AVAILABLE(ios(3.2), watchos(2.0));

UIKIT_EXTERN void UIGraphicsSetPDFContextURLForRect(NSURL *url, CGRect rect) API_AVAILABLE(ios(3.2), watchos(2.0));
UIKIT_EXTERN void UIGraphicsAddPDFContextDestinationAtPoint(NSString *name, CGPoint point) API_AVAILABLE(ios(3.2), watchos(2.0));
UIKIT_EXTERN void UIGraphicsSetPDFContextDestinationForRect(NSString *name, CGRect rect) API_AVAILABLE(ios(3.2), watchos(2.0));

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIGraphics.h>
#endif
