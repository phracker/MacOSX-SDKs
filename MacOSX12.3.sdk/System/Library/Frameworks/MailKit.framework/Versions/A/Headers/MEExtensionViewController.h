//
//  MEExtensionViewController.h
//  Email/MailKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.

#if TARGET_OS_OSX && !TARGET_OS_WATCH
#import <AppKit/AppKit.h>
#elif TARGET_OS_IOS && !TARGET_OS_MACCATALYST
#import <UIKit/UIKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class NSViewController;

#if TARGET_OS_OSX && !TARGET_OS_WATCH
API_AVAILABLE(macos(12.0)) API_UNAVAILABLE(ios, watchos, tvos, macCatalyst)
@interface MEExtensionViewController : NSViewController

@end
#elif TARGET_OS_IOS && !TARGET_OS_MACCATALYST
@interface MEExtensionViewController : UIViewController

@end
#endif

NS_ASSUME_NONNULL_END


