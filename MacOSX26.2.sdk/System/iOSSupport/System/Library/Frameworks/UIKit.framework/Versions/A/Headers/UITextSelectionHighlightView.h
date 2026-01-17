#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextSelectionHighlightView.h>)
//
//  UITextSelectionHighlightView.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <UIKit/UIKitCore.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// @protocol   UITextSelectionHighlightView
/// @abstract   A view that displays a tinted highlight behind rendered text to indicate selection.
/// @discussion When a selection is ranged (i.e., length is > 0), a highlight view is shown to indicate the selected text range.
UIKIT_EXTERN API_AVAILABLE(ios(17.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@protocol UITextSelectionHighlightView <UICoordinateSpace>

/// A collection of @c UITextSelectionRects representing the geometry of the current selection. Rects are expected to be in the
/// receiver's coordinate space.
@property (nonatomic, strong) NSArray<UITextSelectionRect *> *selectionRects;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITextSelectionHighlightView.h>
#endif
