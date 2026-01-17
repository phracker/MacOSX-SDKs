#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextInteraction.h>)
//
//  UITextInteraction.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <UIKit/UIInteraction.h>
#import <UIKit/UITextInput.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UITextInteraction;

typedef NS_ENUM (NSInteger, UITextInteractionMode) {
    UITextInteractionModeEditable,
    UITextInteractionModeNonEditable,
} API_UNAVAILABLE(watchos);

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UITextInteractionDelegate <NSObject>
@optional
- (BOOL)interactionShouldBegin:(UITextInteraction *)interaction atPoint:(CGPoint)point;
- (void)interactionWillBegin:(UITextInteraction *)interaction;
- (void)interactionDidEnd:(UITextInteraction *)interaction;
@end

UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UITextInteraction : NSObject <UIInteraction>

@property (nonatomic, weak) id <UITextInteractionDelegate> delegate;
@property (nonatomic, weak) UIResponder <UITextInput> *textInput;

@property (nonatomic, readonly) UITextInteractionMode textInteractionMode;
@property (nonatomic, readonly) NSArray <UIGestureRecognizer *> *gesturesForFailureRequirements;

+ (instancetype)textInteractionForMode:(UITextInteractionMode)mode;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextInteraction.h>
#endif
