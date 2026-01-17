/*
     NSWritingToolsCoordinatorAnimationParameters.h
     Application Kit
     Copyright (c) 2024, Apple Inc.
     All rights reserved.
 */

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>

@class NSAttributedString;
@class NSUUID;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// An object you use to configure additional tasks or animations to
/// run alongside the Writing Tools animations.
///
/// When Writing Tools replaces text in one of your context objects,
/// it provides an `NSWritingToolsCoordinator.AnimationParameters` object for
/// you to use to configure any additional animations. During a Writing
/// Tools session, you hide the text under evaluation and provide a
/// targeted preview of your content. Writing Tools animations changes
/// to that preview, but you might need to provide additional animations
/// for other parts of your view’s content. For example, you might
/// need to animate any layout changes caused by the insertion or
/// removal of text in other parts of your view. Use this object to
/// configure those animations.
///
/// You don’t create an `NSWritingToolsCoordinator.AnimationParameters`
/// object directly. Instead, the system creates one and passes it to the
///``NSWritingToolsCoordinator/writingToolsCoordinator(_:replaceRange:inContext:proposedText:reason:animationParameters:completion:)``
///method of your ``NSWritingToolsCoordinator/Delegate`` object. Use that
///object to specify the blocks to run during and after the system animations.
API_AVAILABLE(macos(15.2)) NS_SWIFT_SENDABLE NS_SWIFT_NAME(NSWritingToolsCoordinator.AnimationParameters)
@interface NSWritingToolsCoordinatorAnimationParameters : NSObject
- (instancetype)init NS_UNAVAILABLE;

/// The number of seconds it takes the system animations to run.
@property (readonly) CGFloat duration;

/// The number of seconds the system waits before starting its animations.
@property (readonly) CGFloat delay;

/// A custom block that runs at the same time as the system animations.
///
/// If you have animations you want to run at the same time as the system
/// animations, assign a block to this property and use it to run your
/// animations. The block you provide must have no return value and take
/// a floating-point value as a parameter. The parameter indicates the
/// current progress of the animations as a percentage value between
/// `0.0` to `1.0`. The system executes your block multiple times during
/// the course of the animations, providing an updated completion value each time.
@property (nullable, copy) void(^progressHandler)(float progress);

/// A custom block to run when the system animations finish.
///
/// Set this property to a block that you want the system to run when any
/// animations finish. The block you provide must have no return value
/// and no parameters. The system executes this block once when the current
/// animation finish.
@property (nullable, copy) void(^completionHandler)(void);
@end

NS_HEADER_AUDIT_END(nullability, sendability)
