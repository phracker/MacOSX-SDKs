//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#if TARGET_OS_IOS || TARGET_OS_MACCATALYST
#import <UIKit/UIKit.h>

/// @brief Container used for authorization UI.
typedef UIWindow *LAPresentationContext;
#else
#import <AppKit/AppKit.h>

/// @brief Container used for authorization UI.
typedef NSWindow *LAPresentationContext;
#endif // TARGET_OS_OSX
