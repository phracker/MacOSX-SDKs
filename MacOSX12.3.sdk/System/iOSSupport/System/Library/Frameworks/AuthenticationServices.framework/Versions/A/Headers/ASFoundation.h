//
//  ASFoundation.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#ifdef __cplusplus
#define AS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define AS_EXTERN extern __attribute__((visibility ("default")))
#endif

#if __has_include(<UIKit/UIKit.h>)
#import <UIKit/UIKit.h>
#if __has_include(<UIKit/UIWindow.h>)
typedef UIWindow * ASPresentationAnchor;
#endif
#if __has_include(<UIKit/UIViewController.h>) && !defined(ASViewController)
typedef UIViewController ASViewController;
#endif
typedef UIImage ASImage;
#elif __has_include(<AppKit/AppKit.h>)
#import <AppKit/AppKit.h>
typedef NSWindow * ASPresentationAnchor;
#if !defined(ASViewController)
typedef NSViewController ASViewController;
typedef NSImage ASImage;
#endif
#endif
