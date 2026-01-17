#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusDebugger.h>)
//
//  UIFocusDebugger.h
//  UIKit Framework
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIFocusSystem;
@protocol UIFocusDebuggerOutput, UIFocusEnvironment, UIFocusItem;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// UIFocusDebugger provides a collection of runtime utilities for debugging issues related to focus interaction.
UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIFocusDebugger : NSObject

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

/// Simulates a fake focus update requested by the specified environment (e.g. `[focusSystem requestFocusUpdateToEnvironment:environment]`), outlining each step of the process for determining the next focused item.
///   - To use in Swift, enter `po UIFocusDebugger.simulateFocusUpdateRequest(from: <environment reference>)` when paused in lldb.
///   - To use in Objective-C, enter `po [UIFocusDebugger simulateFocusUpdateRequestFromEnvironment:<environment reference>]` when paused in lldb.
+ (id<UIFocusDebuggerOutput>)simulateFocusUpdateRequestFromEnvironment:(id<UIFocusEnvironment>)environment;

/// Outputs a diagnosis of the focus groups of the specified environment and its children.
/// Pass a focus system as the environment to get the full focus group tree for this focus system.
///  - To use in Swift, enter `po UIFocusDebugger.focusGroups(for: <environment reference>)` when paused in lldb.
///  - To use in Objective-C, enter `po [UIFocusDebugger focusGroupsForEnvironment:<environment reference>]` when paused in lldb.
+ (id<UIFocusDebuggerOutput>)focusGroupsForEnvironment:(id<UIFocusEnvironment>)environment;

/// Outputs a diagnoses of the preferred focus environments tree.
/// - To use in Swift, enter `po UIFocusDebugger.preferredFocusEnvironments(for: <environment reference>)` when paused in lldb.
/// - To use in Objective-C, enter `po [UIFocusDebugger preferredFocusEnvironmentsForEnvironment:<environment reference>]` when paused in lldb.
+ (id<UIFocusDebuggerOutput>)preferredFocusEnvironmentsForEnvironment:(id<UIFocusEnvironment>)environment;

@end

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIFocusDebuggerOutput <NSObject>
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIFocusDebugger.h>
#endif
