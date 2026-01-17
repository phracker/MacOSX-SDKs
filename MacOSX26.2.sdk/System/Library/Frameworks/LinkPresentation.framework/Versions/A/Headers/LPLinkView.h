//
//  LinkPresentation
//  Copyright © 2015-2019 Apple Inc. All rights reserved.
//

#import <LinkPresentation/LPFoundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

NS_ASSUME_NONNULL_BEGIN

@class LPLinkMetadata;

LP_EXTERN API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0))
#if TARGET_OS_IPHONE
/// A rich visual representation of a link.
///
/// ``LPLinkView`` presents a link based on its available metadata. Use it to
/// show a link’s title and icon, associated images, inline audio, video
/// playback, and maps in a familiar and consistent style.
///
/// ## Present a rich link
///
/// To present a rich link in your app, create an ``LPLinkView``, passing an
/// ``LPLinkMetadata`` instance into its initializer. Then add the
/// ``LPLinkView`` to your view.
///
/// For example, to present links in a table view, add an ``LPLinkView``
/// instance as a subview when populating each cell.
///
/// ```swift
/// let linkView = LPLinkView(metadata: metadata)
/// cell.contentView.addSubview(linkView)
/// linkView.sizeToFit()
/// ```
///
/// ``LPLinkView`` has an intrinsic size, but it also responds to
/// <doc://com.apple.documentation/documentation/uikit/uiview/1622630-sizetofit>
/// to present a layout at any size.
@interface LPLinkView : UIView
#else
/// A rich visual representation of a link.
///
/// ``LPLinkView`` presents a link based on its available metadata. Use it to
/// show a link’s title and icon, associated images, inline audio, video
/// playback, and maps in a familiar and consistent style.
///
/// ## Present a rich link
///
/// To present a rich link in your app, create an ``LPLinkView``, passing an
/// ``LPLinkMetadata`` instance into its initializer. Then add the
/// ``LPLinkView`` to your view.
///
/// For example, to present links in a table view, add an ``LPLinkView``
/// instance as a subview when populating each cell.
///
/// ```swift
/// let linkView = LPLinkView(metadata: metadata)
/// cell.contentView.addSubview(linkView)
/// linkView.sizeToFit()
/// ```
///
/// ``LPLinkView`` has an intrinsic size, but it also responds to
/// <doc://com.apple.documentation/documentation/uikit/uiview/1622630-sizetofit>
/// to present a layout at any size.
@interface LPLinkView : NSView
#endif

- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;
- (void)encodeWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

/// Initializes a placeholder link view without metadata for a given URL.
- (instancetype)initWithURL:(NSURL *)URL;

/// Initializes a link view with specified metadata.
- (instancetype)initWithMetadata:(LPLinkMetadata *)metadata;

/// The metadata from which to generate a rich presentation.
///
/// This can either be generated automatically from a URL by LPMetadataProvider,
/// or manually constructed with the desired data.
@property (nonatomic, copy) LPLinkMetadata *metadata;

@end

NS_ASSUME_NONNULL_END
