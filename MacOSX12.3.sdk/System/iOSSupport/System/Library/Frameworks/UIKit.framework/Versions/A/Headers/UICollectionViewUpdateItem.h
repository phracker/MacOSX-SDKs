#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UICollectionViewUpdateItem.h>)
//
//  UICollectionViewUpdateItem.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitDefines.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, UICollectionUpdateAction) {
    UICollectionUpdateActionInsert,
    UICollectionUpdateActionDelete,
    UICollectionUpdateActionReload,
    UICollectionUpdateActionMove,
    UICollectionUpdateActionNone
};

UIKIT_EXTERN API_AVAILABLE(ios(6.0)) NS_SWIFT_UI_ACTOR
@interface UICollectionViewUpdateItem : NSObject

@property (nonatomic, readonly, nullable) NSIndexPath *indexPathBeforeUpdate; // nil for UICollectionUpdateActionInsert
@property (nonatomic, readonly, nullable) NSIndexPath *indexPathAfterUpdate; // nil for UICollectionUpdateActionDelete
@property (nonatomic, readonly) UICollectionUpdateAction updateAction;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UICollectionViewUpdateItem.h>
#endif
