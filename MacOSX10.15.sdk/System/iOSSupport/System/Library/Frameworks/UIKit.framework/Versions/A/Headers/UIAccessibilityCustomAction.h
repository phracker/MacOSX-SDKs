#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityCustomAction.h>)
//
//  UIAccessibilityCustomAction.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) @interface UIAccessibilityCustomAction : NSObject

- (instancetype)initWithName:(NSString *)name target:(nullable id)target selector:(SEL)selector;
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName target:(nullable id)target selector:(SEL)selector API_AVAILABLE(ios(11.0), tvos(11.0));

typedef BOOL(^UIAccessibilityCustomActionHandler)(UIAccessibilityCustomAction *customAction);
- (instancetype)initWithName:(NSString *)name actionHandler:(UIAccessibilityCustomActionHandler)actionHandler API_AVAILABLE(ios(13.0), tvos(13.0));
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName actionHandler:(UIAccessibilityCustomActionHandler)actionHandler API_AVAILABLE(ios(13.0), tvos(13.0));

/*
 A localized name that describes the action.
 */
@property (nonatomic, copy) NSString *name;

/*
 Underlying attributed version of the "name" property. Setting this property will change the
 value of the "name" property and vice-versa.
 */
@property (nonatomic, copy) NSAttributedString *attributedName API_AVAILABLE(ios(11.0), tvos(11.0));

/*
 The object that will perform the action.
 */
@property (nullable, nonatomic, weak) id target;

/*
 The method that will be called on the target to perform the action.
 It must conform to one of the following signatures:
 - (BOOL)myPerformActionMethod;
 - (BOOL)myPerformActionMethod:(UIAccessibilityCustomAction *)action;
 */
@property (nonatomic, assign) SEL selector;

/*
 If the actionHandler is set, it will be preferred over the target/selector.
 */
@property (nonatomic, copy, nullable) UIAccessibilityCustomActionHandler actionHandler API_AVAILABLE(ios(13.0), tvos(13.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIAccessibilityCustomAction.h>
#endif
