#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIContextMenuConfiguration.h>)
//
//  UIContextMenuConfiguration.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAction.h>

NS_ASSUME_NONNULL_BEGIN

@class UIViewController;

/*!
 * @abstract Return a UIAction-based UIMenu describing the desired action hierarchy.
 *
 * @param suggestedActions  An array of suggested actions gathered from the UIResponder chain. You may choose to include
 *                          some of these actions in the hierarchy returned from this block to display them in the resulting menu.
 */
typedef UIMenu * _Nullable (^UIContextMenuActionProvider)(NSArray<UIMenuElement *> *suggestedActions);

/*!
 * @abstract Return a UIViewController to be displayed as this menu's preview component.
 */
typedef UIViewController * _Nullable (^UIContextMenuContentPreviewProvider)(void);


UIKIT_EXTERN API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIContextMenuConfiguration : NSObject

@property (nonatomic, readonly) id<NSCopying> identifier;

/*!
 * @abstract Returns a UIContextMenuConfiguration.
 *
 * @param identifier       Optional unique identifier. If omitted, an NSUUID will be generated. May be used to
 *                         identify this configuration throughout the interaction's lifecycle.
 * @param previewProvider  Optional preview view controller provider block, called when the menu is about to be presented.
 * @param actionProvider   Optional action provider block, called when the menu is about to be presented.
 */
+ (instancetype)configurationWithIdentifier:(nullable id<NSCopying>)identifier
                            previewProvider:(nullable UIContextMenuContentPreviewProvider)previewProvider
                             actionProvider:(nullable UIContextMenuActionProvider)actionProvider;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIContextMenuConfiguration.h>
#endif
