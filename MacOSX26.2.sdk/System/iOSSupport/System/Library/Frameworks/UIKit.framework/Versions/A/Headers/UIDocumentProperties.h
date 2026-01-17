#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIDocumentProperties.h>)
//
//  UIDocumentProperties.h
//  UIKit
//
//  Copyright © 2022 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

@class UIDragItem, UIActivityViewController;
@class LPLinkMetadata;
@protocol UIDragSession;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@interface UIDocumentProperties : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// When initializing with a url, UIKit will automatically lookup metadata based on the data at that url.
- (instancetype)initWithURL:(NSURL *)url;

/// Initialize with metadata directly when the item is not backed by a url.
- (instancetype)initWithMetadata:(LPLinkMetadata *)metadata;

/// The metadata to use. UIKit will generate this automatically if a url is given at initialization time.
@property (nonatomic, readwrite, copy) LPLinkMetadata *metadata;

/// To support drag & drop, assign a closure to return an array of drag items corresponding to the represented document.
@property (nonatomic, readwrite, copy, nullable) NSArray<UIDragItem *> *(^dragItemsProvider)(id<UIDragSession>);

/// To support sharing, assign a closure to return a UIActivityViewController configured to share the represented document.
@property (nonatomic, readwrite, copy, nullable) UIActivityViewController *(^activityViewControllerProvider)(void);

/// If enabled, shows an icon representation of the document in the navigation bar.
@property (nonatomic) BOOL wantsIconRepresentation;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIDocumentProperties.h>
#endif
