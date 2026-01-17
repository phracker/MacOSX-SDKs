//
//  SWAttributionView.h
//  SWAttributionView
//
//  Copyright (c) 2021 Apple. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_OSX
#import <AppKit/NSView.h>
#import <AppKit/NSMenu.h>
#else
#import <UIKit/UIView.h>
#import <UIKit/UIMenu.h>
#endif

#import <SharedWithYouCore/SWDefines.h>
#import <SharedWithYou/SWHighlight.h>

NS_ASSUME_NONNULL_BEGIN

@class SWAttributionView;
@class SWHighlight;

/*!
    @abstract The context for the content being displayed; influences future ranking of this view's SWHighlight
    @discussion Set the appropriate display context on SWAttributionView before it is added to a window. This informs the system about how the user is consuming the attributed content, and influences future relevancy ranking of the SWHighlight for this view.
 */
typedef NS_ENUM(NSInteger, SWAttributionViewDisplayContext) {
    /// The default context. Indicates that the attributed content shown along with this view is being offered to the user for consumption
    SWAttributionViewDisplayContextSummary = 0,
    /// Indicates that the attributed content shown along with this view is being actively consumed by the user
    SWAttributionViewDisplayContextDetail,
} NS_SWIFT_NAME(SWAttributionView.DisplayContext) API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0));

/*!
    @abstract The horizontal alignment of SWAttributionView's contents
 */
typedef NS_ENUM(NSInteger, SWAttributionViewHorizontalAlignment) {
    /// The default horizontal alignment, to be chosen by SWAttributionView
    SWAttributionViewHorizontalAlignmentDefault = 0,
    /// Horizontally align with the leading edge of the view (depends on the user interface layout direction)
    SWAttributionViewHorizontalAlignmentLeading,
    /// Horizontally align with the center of the view
    SWAttributionViewHorizontalAlignmentCenter,
    /// Horizontally align with the trailing edge of the view (depends on the user interface layout direction)
    SWAttributionViewHorizontalAlignmentTrailing
} NS_SWIFT_NAME(SWAttributionView.HorizontalAlignment) API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0));

/*!
    @abstract The background styling of SWAttributionView's contents
 */
typedef NS_ENUM(NSInteger, SWAttributionViewBackgroundStyle) {
    /// The default background style, to be chosen by SWAttributionView
    SWAttributionViewBackgroundStyleDefault = 0,
    /// A non-material background color for the view's contents, best when placed over monochrome backgrounds
    SWAttributionViewBackgroundStyleColor,
    /// A material background blur for the view's contents, best when placed over multicolored backgrounds
    SWAttributionViewBackgroundStyleMaterial
} NS_SWIFT_NAME(SWAttributionView.BackgroundStyle) API_AVAILABLE(ios(16.0), macos(13.0), tvos(16.0));

/*!
     @class SWAttributionView
     @abstract Displays the senders who shared a particular SWHighlight. Allows users to get back to the conversation about that content, and provides other related actions.
     @discussion Place an SWAttributionView next to the content represented by its SWHighlight. SWAttributionView displays the names/avatars within the provided horizontal space. Constrain this view's width anchor or set its frame width to control the maximum width of its contents after which truncation may occur. Do not constrain the view's height, as the height is dependent on the preferredContentSizeCategory, and the resulting font size. To provide enough vertical space around this view, reference its heightAnchor when using Auto Layout, or its intrinsicContentSize when using manual layout.
 */

#if TARGET_OS_OSX
API_AVAILABLE(macos(13.0))
SW_EXTERN @interface SWAttributionView : NSView
#else
API_AVAILABLE(ios(16.0), tvos(16.0))
SW_EXTERN @interface SWAttributionView : UIView
#endif

/*!
    @abstract The SWHighlight to use for displaying this attribution. When this property is set to a new highlight, the contents of the view will be reloaded.
 */
@property (nullable, strong, nonatomic, readwrite) SWHighlight *highlight;

/*!
    @abstract The context for the content being displayed with this view. Set this prior to adding this view to your view hierarchy.
 */
@property (assign, nonatomic, readwrite) SWAttributionViewDisplayContext displayContext;

/*!
    @abstract The horizontal alignment of the view. You should specify a value, in case the internal default ever changes.
    @discussion This value specifies the horizontal anchor for the view's contents. This only has an effect when the width of the contents are less than the available width.
 */
@property (assign, nonatomic, readwrite) SWAttributionViewHorizontalAlignment horizontalAlignment;

/*!
    @abstract The background style of the inner view containing names and avatars.
    @discussion If you do not specify a background style, one will be chosen automatically. In general, .color looks best on monochrome backgrounds, while .material looks better on colored backgrounds.
 */
@property (assign, nonatomic, readwrite) SWAttributionViewBackgroundStyle backgroundStyle;

/*!
    @abstract For use when embedding this view in a SwiftUI view representable.
    @discussion When using this view in SwiftUI, this view will constrain its contents to this width. If you are not using SwiftUI this property should not be necessary, as SWAttributionView otherwise derives the maximum width from the frame or constraints you set.
 */
@property (assign, nonatomic, readwrite) CGFloat preferredMaxLayoutWidth;

/*!
    @abstract A menu with a list of system actions specific to this SWAttributionView's SWHighlight.
    @discussion Use this menu to augment an existing menu attached to the content represented by this SWAttributionView. This allows the user to easily reply to or hide the content. This menu should be added inline with (and at the end of) the menu elements it augments.
 */
#if TARGET_OS_OSX
@property (strong, nonatomic, readonly) NSMenu *highlightMenu;
#else
@property (strong, nonatomic, readonly) UIMenu *highlightMenu;
#endif

/*!
    @abstract A custom localized string to be used as the title for the "Hide" menu item title. A nil value will result in the default title.
    @discussion SWAttributionView manages a context menu which includes the option for the user to hide the content for the SWHighlight represented by this view. Set a title to be used as the title for that context menu. An app that displays articles, for example, might set @"Hide Article", localized to the current language. The string should include the word "Hide", localized correctly with the custom content type.
 */
@property (nullable, strong, nonatomic, readwrite) NSString *menuTitleForHideAction;

/*!
    @abstract Supplemental menu to augment SWAttributionView's existing menu. Use this when there are additional actions a user can take on content represented by this view's SWHighlight. A nil value results in no supplemental menu being used.
 */
#if TARGET_OS_OSX
@property (nullable, strong, nonatomic, readwrite) NSMenuItem *supplementalMenu;
#else
@property (nullable, strong, nonatomic, readwrite) UIMenu *supplementalMenu;
#endif

/*!
    @brief Automatically enables a marquee effect if the text contents extend past the bounds of the view (tvOS only)
 */
@property (assign, nonatomic, readwrite) BOOL enablesMarquee API_UNAVAILABLE(ios, macos);

@end

NS_ASSUME_NONNULL_END
