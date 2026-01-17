#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISwipeActionsConfiguration.h>)
//
//  UISwipeActionsConfiguration.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIContextualAction.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos)
@interface UISwipeActionsConfiguration : NSObject

+ (instancetype)configurationWithActions:(NSArray<UIContextualAction *> *)actions;

@property (nonatomic, copy, readonly) NSArray<UIContextualAction *> *actions;
@property (nonatomic) BOOL performsFirstActionWithFullSwipe; // default YES, set to NO to prevent a full swipe from performing the first action

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UISwipeActionsConfiguration.h>
#endif
