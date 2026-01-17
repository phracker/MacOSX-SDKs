#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusDebugger.h>)
//
//  UIFocusDebugger.h
//  UIKit Framework
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@protocol UIFocusDebuggerOutput, UIFocusEnvironment, UIFocusItem;

NS_ASSUME_NONNULL_BEGIN

/// UIFocusDebugger provides a collection of runtime utilities for debugging issues related to focus interaction.
UIKIT_EXTERN API_AVAILABLE(ios(11.0)) @interface UIFocusDebugger : NSObject

/// Outputs an overview of all supported debugging utilities and other relevant information.
///   - To use in Swift, enter `po UIFocusDebugger.help()` when paused in lldb.
///   - To use in Objective-C, enter `po [UIFocusDebugger help]` when paused in lldb.
+ (id<UIFocusDebuggerOutput>)help;

/// Outputs information for the currently focused item.
///   - To use in Swift, enter `po UIFocusDebugger.status()` when paused in lldb.
///   - To use in Objective-C, enter `po [UIFocusDebugger status]` when paused in lldb.
+ (id<UIFocusDebuggerOutput>)status;

/// Outputs a diagnosis of the specified item's focusability, including any known issues that may be preventing focusability.
///   - To use in Swift, enter `po UIFocusDebugger.checkFocusability(for: <item reference>)` when paused in lldb.
///   - To use in Objective-C, enter `po [UIFocusDebugger checkFocusabilityForItem:<item reference>]` when paused in lldb.
+ (id<UIFocusDebuggerOutput>)checkFocusabilityForItem:(id<UIFocusItem>)item;

/// Simulates a fake focus update requested by the specified environment (e.g. `[environment setNeedsFocusUpdate]`), outlining each step of the process for determining the next focused item.
///   - To use in Swift, enter `po UIFocusDebugger.simulateFocusUpdateRequest(from: <environment reference>)` when paused in lldb.
///   - To use in Objective-C, enter `po [UIFocusDebugger simulateFocusUpdateRequestFromEnvironment:<environment reference>]` when paused in lldb.
+ (id<UIFocusDebuggerOutput>)simulateFocusUpdateRequestFromEnvironment:(id<UIFocusEnvironment>)environment;

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) @protocol UIFocusDebuggerOutput <NSObject>
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIFocusDebugger.h>
#endif
