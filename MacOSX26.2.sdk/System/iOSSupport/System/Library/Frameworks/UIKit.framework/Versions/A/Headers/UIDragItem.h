#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDragItem.h>)
//
//  UIDragItem.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIDragPreview;

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIDragItem : NSObject

- (instancetype)initWithItemProvider:(NSItemProvider *)itemProvider NS_DESIGNATED_INITIALIZER;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) __kindof NSItemProvider *itemProvider;

/**
 * Use `localObject` to attach additional information to
 * this drag item, visible only inside the app that started the drag.
 */
@property (nonatomic, strong, nullable) id localObject;

/**
 * Use `previewProvider` to change the preview for an item.
 *
 * Each item is usually given a preview when the drag begins,
 * either by the UIDragInteractionDelegate's `-dragInteraction:previewForLiftingItem:session:`
 * method, or by creating a preview from the dragging view.
 *
 * During the drag, applications may attempt to change the item's preview,
 * by setting `previewProvider` to a block that returns a preview.
 * It will be called when and if the system requests it.
 *
 * To use the default preview, set `previewProvider` to nil.
 * To hide the preview, set `previewProvider` to a block that returns nil.
 */
@property (nonatomic, copy, nullable) UIDragPreview * _Nullable (^previewProvider)(void);

/**
 * Requests for the drop preview to be updated if an active drop animation is in progress, and can handle updates.
 * If no active drop animation is in progress for the specified item, then nothing happens.
 */
- (void)setNeedsDropPreviewUpdate API_AVAILABLE(ios(17.4));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIDragItem.h>
#endif
