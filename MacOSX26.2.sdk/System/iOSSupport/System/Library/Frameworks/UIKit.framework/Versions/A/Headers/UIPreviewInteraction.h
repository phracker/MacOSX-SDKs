#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPreviewInteraction.h>)
//
//  UIPreviewInteraction.h
//  UIKit
//
//  Copyright (c) 2015-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIView.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@protocol UIPreviewInteractionDelegate;

UIKIT_CLASS_AVAILABLE_IOS_ONLY(10_0) NS_SWIFT_UI_ACTOR
@interface UIPreviewInteraction : NSObject

- (instancetype)initWithView:(UIView *)view NS_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly, weak) UIView *view;

- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, nullable, weak) id <UIPreviewInteractionDelegate> delegate;

- (CGPoint)locationInCoordinateSpace:(nullable id <UICoordinateSpace>)coordinateSpace; // returns the current location of the touch that started the interaction
- (void)cancelInteraction;

@end

API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UIPreviewInteractionDelegate <NSObject>

- (void)previewInteraction:(UIPreviewInteraction *)previewInteraction didUpdatePreviewTransition:(CGFloat)transitionProgress ended:(BOOL)ended UIKIT_AVAILABLE_IOS_ONLY(10_0); // transitionProgress ranges from 0 to 1
- (void)previewInteractionDidCancel:(UIPreviewInteraction *)previewInteraction UIKIT_AVAILABLE_IOS_ONLY(10_0);

@optional

- (BOOL)previewInteractionShouldBegin:(UIPreviewInteraction *)previewInteraction UIKIT_AVAILABLE_IOS_ONLY(10_0);

// If implemented, a preview interaction will also trigger haptic feedback when detecting a commit (pop). The provided transitionProgress ranges from 0 to 1.
- (void)previewInteraction:(UIPreviewInteraction *)previewInteraction didUpdateCommitTransition:(CGFloat)transitionProgress ended:(BOOL)ended UIKIT_AVAILABLE_IOS_ONLY(10_0);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPreviewInteraction.h>
#endif
