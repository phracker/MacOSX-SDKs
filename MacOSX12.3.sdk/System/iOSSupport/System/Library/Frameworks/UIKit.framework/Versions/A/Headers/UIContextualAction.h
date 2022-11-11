#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContextualAction.h>)
//
//  UIContextualAction.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>

NS_ASSUME_NONNULL_BEGIN

@class UIContextualAction;

// call the completionHandler to reset the context to its normal state (e.g. when swiping, resets to unswiped state)
// pass YES to the completionHandler if the action was actually performed, to show a visual indication of the successful completion
typedef void (^UIContextualActionHandler)(UIContextualAction *action, __kindof UIView *sourceView, void(^completionHandler)(BOOL actionPerformed));

typedef NS_ENUM(NSInteger, UIContextualActionStyle) {
    UIContextualActionStyleNormal,
    UIContextualActionStyleDestructive
} NS_SWIFT_NAME(UIContextualAction.Style) API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos);

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIContextualAction : NSObject

+ (instancetype)contextualActionWithStyle:(UIContextualActionStyle)style title:(nullable NSString *)title handler:(UIContextualActionHandler)handler;

@property (nonatomic, readonly) UIContextualActionStyle style;
@property (nonatomic, copy, readonly) UIContextualActionHandler handler;

@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, null_resettable) UIColor *backgroundColor; // a default background color is set from the action style
@property (nonatomic, copy, nullable) UIImage *image;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIContextualAction.h>
#endif
