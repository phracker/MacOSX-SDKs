#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextDragURLPreviews.h>)
//
//  UITextDragURLPreviews.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIDragPreview.h>
#import <UIKit/UITargetedDragPreview.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/* Methods to create previews for dragging a URL.
 * The previews show a textual representation of the URL, and may not
 * contain the full URL string.
 * Should be used only for Internet protocol based URLs, not file URLs.
 */

@interface UIDragPreview (URLPreviews)

+ (instancetype)previewForURL:(NSURL *)url;

/* If the title is nil or empty, this is the same as `previewForURL:`.
 */
+ (instancetype)previewForURL:(NSURL *)url title:(NSString * _Nullable)title;

@end


@interface UITargetedDragPreview (URLPreviews)

+ (instancetype)previewForURL:(NSURL *)url target:(UIDragPreviewTarget*)target;

/* If the title is nil or empty, this is the same as `previewForURL:target:`.
 */
+ (instancetype)previewForURL:(NSURL *)url title:(NSString * _Nullable)title target:(UIDragPreviewTarget*)target;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextDragURLPreviews.h>
#endif
