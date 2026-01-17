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

/**
 An LPLinkView provides a rich visual representation of an LPLinkMetadata object.

 @see `LPLinkMetadata`
 @see `LPMetadataProvider`
 */
LP_EXTERN API_AVAILABLE(macos(10.15), ios(13.0), watchos(6.0))
#if TARGET_OS_IPHONE
@interface LPLinkView : UIView
#else
@interface LPLinkView : NSView
#endif

- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;
- (void)encodeWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

- (instancetype)initWithURL:(NSURL *)URL;
- (instancetype)initWithMetadata:(LPLinkMetadata *)metadata;

/**
 The LPLinkMetadata object with which to generate a rich presentation.

 The metadata can either be generated automatically from a URL by LPMetadataProvider,
 or manually constructed with the desired data.
 */
@property (nonatomic, copy) LPLinkMetadata *metadata;

@end

NS_ASSUME_NONNULL_END
