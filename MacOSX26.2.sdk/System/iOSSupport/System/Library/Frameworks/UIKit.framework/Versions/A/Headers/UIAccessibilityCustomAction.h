#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityCustomAction.h>)
//
//  UIAccessibilityCustomAction.h
//  UIKit
//
//  Copyright (c) 2014-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIImage.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIAccessibilityCustomAction : NSObject

- (instancetype)initWithName:(NSString *)name target:(nullable id)target selector:(SEL)selector;
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName target:(nullable id)target selector:(SEL)selector API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);
- (instancetype)initWithName:(NSString *)name image:(nullable UIImage *)image target:(nullable id)target selector:(SEL)selector API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName image:(nullable UIImage *)image target:(nullable id)target selector:(SEL)selector API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);


typedef BOOL(^UIAccessibilityCustomActionHandler)(UIAccessibilityCustomAction *customAction) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR;
- (instancetype)initWithName:(NSString *)name actionHandler:(UIAccessibilityCustomActionHandler)actionHandler API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName actionHandler:(UIAccessibilityCustomActionHandler)actionHandler API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);
- (instancetype)initWithName:(NSString *)name image:(nullable UIImage *)image actionHandler:(UIAccessibilityCustomActionHandler)actionHandler API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName image:(nullable UIImage *)image actionHandler:(UIAccessibilityCustomActionHandler)actionHandler API_AVAILABLE(ios(14.0), tvos(14.0)) API_UNAVAILABLE(watchos);


/*
 A localized name that describes the action.
 */
@property (nonatomic, copy) NSString *name;

/*
 An image representing the action to be shown with some assistive technologies such as Switch Control.
 */
@property (nullable, nonatomic, strong) UIImage *image;

/*
 Underlying attributed version of the "name" property. Setting this property will change the
 value of the "name" property and vice-versa.
 */
@property (nonatomic, copy) NSAttributedString *attributedName API_AVAILABLE(ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

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
@property (nonatomic, copy, nullable) UIAccessibilityCustomActionHandler actionHandler API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(watchos);

/*
 A localized name that describes the action's category. If nil, the category will be the default "Actions" category
 */
@property (nullable, nonatomic, copy) NSString *category API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos);

@end

UIKIT_EXTERN NSString *const UIAccessibilityCustomActionCategoryEdit API_AVAILABLE(ios(18.0), tvos(18.0), visionos(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_NAME(UIAccessibilityCustomAction.editCategory) NS_SWIFT_NONISOLATED;

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIAccessibilityCustomAction.h>
#endif
