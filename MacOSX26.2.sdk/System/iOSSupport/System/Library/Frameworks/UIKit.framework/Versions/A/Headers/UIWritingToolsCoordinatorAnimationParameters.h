#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIWritingToolsCoordinatorAnimationParameters.h>)
//
//  UIWritingToolsCoordinatorAnimationParameters.h
//  UIKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object you use to configure additional tasks or animations to
/// run alongside the Writing Tools animations.
///
/// When Writing Tools replaces text in one of your context objects,
/// it provides a `UIWritingToolsCoordinator.AnimationParameters` object for
/// you to use to configure any additional animations. During a Writing
/// Tools session, you hide the text under evaluation and provide a
/// targeted preview of your content. Writing Tools animations changes
/// to that preview, but you might need to provide additional animations
/// for other parts of your view’s content. For example, you might
/// need to animate any layout changes caused by the insertion or
/// removal of text in other parts of your view. Use this object to
/// configure those animations.
///
/// You don’t create a `UIWritingToolsCoordinator.AnimationParameters`
/// object directly. Instead, the system creates one and passes it to the
///``UIWritingToolsCoordinator/writingToolsCoordinator(_:replaceRange:inContext:proposedText:reason:animationParameters:completion:)``
///method of your ``UIWritingToolsCoordinatorDelegate`` object. Use that
///object to specify the blocks to run during and after the system animations.
UIKIT_EXTERN API_AVAILABLE(ios(18.2), visionos(2.4)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_SENDABLE NS_SWIFT_NAME(UIWritingToolsCoordinator.AnimationParameters)
@interface UIWritingToolsCoordinatorAnimationParameters : NSObject
- (instancetype)init NS_UNAVAILABLE;

/// The number of seconds it takes the system animations to run.
@property(nonatomic,readonly) CGFloat duration;

/// The number of seconds the system waits before starting its animations.
@property(nonatomic,readonly) CGFloat delay;

/// A custom block that runs at the same time as the system animations.
///
/// If you have animations you want to run at the same time as the system
/// animations, assign a block to this property and use it to run your
/// animations. The block you provide must have no return value and take
/// a floating-point value as a parameter. The parameter indicates the
/// current progress of the animations as a percentage value between
/// `0.0` to `1.0`. The system executes your block multiple times during
/// the course of the animations, providing an updated completion value each time.
@property(nonatomic,nullable,copy) void(^progressHandler)(float progress);

/// A custom block to run when the system animations finish.
///
/// Set this property to a block that you want the system to run when any
/// animations finish. The block you provide must have no return value
/// and no parameters. The system executes this block once when the current
/// animation finish.
@property(nonatomic,nullable,copy) void(^completionHandler)(void);
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIWritingToolsCoordinatorAnimationParameters.h>
#endif
