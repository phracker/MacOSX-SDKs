//
//  ASFoundation.h
//  AuthenticationServices Framework
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifdef __cplusplus
#define AS_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define AS_EXTERN extern __attribute__((visibility ("default")))
#endif

#ifdef NS_HEADER_AUDIT_BEGIN
#define AS_HEADER_AUDIT_BEGIN NS_HEADER_AUDIT_BEGIN
#define AS_HEADER_AUDIT_END NS_HEADER_AUDIT_END
#else
#define AS_HEADER_AUDIT_BEGIN(...) NS_ASSUME_NONNULL_BEGIN
#define AS_HEADER_AUDIT_END(...) NS_ASSUME_NONNULL_END
#endif

#ifdef NS_SWIFT_SENDABLE
#define AS_SWIFT_SENDABLE NS_SWIFT_SENDABLE
#else
#define AS_SWIFT_SENDABLE
#endif

#ifdef __AS_INTERNAL_AVAILABILITY
#define AS_API_AVAILABLE(...)
#else
#define AS_API_AVAILABLE API_AVAILABLE
#endif

#if __has_include(<UIKit/UIKit.h>)
#import <UIKit/UIKit.h>
#if __has_include(<UIKit/UIWindow.h>)
typedef UIWindow * ASPresentationAnchor API_UNAVAILABLE(watchos);
#endif
#if __has_include(<UIKit/UIViewController.h>) && !defined(ASViewController)
typedef UIViewController ASViewController API_UNAVAILABLE(watchos);
#endif
typedef UIImage ASImage API_UNAVAILABLE(watchos);
#elif __has_include(<AppKit/AppKit.h>)
#import <AppKit/AppKit.h>
typedef NSWindow * ASPresentationAnchor;
#if !defined(ASViewController)
typedef NSViewController ASViewController;
typedef NSImage ASImage;
#endif
#endif
