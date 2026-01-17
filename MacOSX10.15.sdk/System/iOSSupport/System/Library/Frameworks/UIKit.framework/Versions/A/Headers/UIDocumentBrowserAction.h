#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<DocumentManager/UIDocumentBrowserAction.h>)
//
//  UIDocumentBrowserAction.h
//  UIKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class UIImage;

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSInteger, UIDocumentBrowserActionAvailability) {
    UIDocumentBrowserActionAvailabilityMenu = 1,                        // The action can be shown in the menu
    UIDocumentBrowserActionAvailabilityNavigationBar = 1 << 1,          // The action can be shown in navigation bar
} API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos) NS_SWIFT_NAME(UIDocumentBrowserAction.Availability);

/// UIDocumentBrowserAction instances are custom, contextual actions that are presented to the user by a UIDocumentBrowserViewController.
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos,tvos) @interface UIDocumentBrowserAction : NSObject

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithIdentifier:(NSString *)identifier localizedTitle:(NSString *)localizedTitle availability:(UIDocumentBrowserActionAvailability)availability handler:(void(^)(NSArray <NSURL *> *))handler NS_DESIGNATED_INITIALIZER;

@property (nonatomic, readonly) NSString *identifier;
@property (nonatomic, readonly) NSString *localizedTitle;
@property (nonatomic, readonly) UIDocumentBrowserActionAvailability availability;

@property (nonatomic, strong, nullable) UIImage *image;

/// Allows clients to restrict the action to only a specific set of content types. Default: [kUTTypeItem]
@property (nonatomic, copy) NSArray<NSString*> *supportedContentTypes;

/// If NO, the action is only available, if there is only one item selected. Default: YES.
@property (nonatomic, assign) BOOL supportsMultipleItems;

@end

NS_ASSUME_NONNULL_END

#else
#import <DocumentManager/UIDocumentBrowserAction.h>
#endif
