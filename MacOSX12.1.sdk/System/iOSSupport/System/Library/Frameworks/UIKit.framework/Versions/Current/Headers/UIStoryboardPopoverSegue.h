#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIStoryboardPopoverSegue.h>)
//
//  UIStoryboardPopoverSegue.h
//  UIKit
//
//  Copyright 2011-2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIStoryboardSegue.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPopoverController;

UIKIT_EXTERN API_DEPRECATED("Access destinationViewController.popoverPresentationController from your segue's performHandler or override of -perform", ios(5.0, 9.0)) NS_SWIFT_UI_ACTOR
@interface UIStoryboardPopoverSegue : UIStoryboardSegue {
}

@property (nonatomic, strong, readonly) UIPopoverController *popoverController;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIStoryboardPopoverSegue.h>
#endif
