#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<ShareSheet/UIActivity.h>)
//
//  UIActivity.h
//  UIKit
//
//  Copyright 2012-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage, UIViewController;

typedef NSString * UIActivityType NS_TYPED_EXTENSIBLE_ENUM;

UIKIT_EXTERN UIActivityType const UIActivityTypePostToFacebook     API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypePostToTwitter      API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypePostToWeibo        API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;    // SinaWeibo
UIKIT_EXTERN UIActivityType const UIActivityTypeMessage            API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypeMail               API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypePrint              API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypeCopyToPasteboard   API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypeAssignToContact    API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypeSaveToCameraRoll   API_AVAILABLE(ios(6.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypeAddToReadingList   API_AVAILABLE(ios(7.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypePostToFlickr       API_AVAILABLE(ios(7.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypePostToVimeo        API_AVAILABLE(ios(7.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypePostToTencentWeibo API_AVAILABLE(ios(7.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypeAirDrop            API_AVAILABLE(ios(7.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypeOpenInIBooks       API_AVAILABLE(ios(9.0)) __TVOS_PROHIBITED;
UIKIT_EXTERN UIActivityType const UIActivityTypeMarkupAsPDF        API_AVAILABLE(ios(11.0)) __TVOS_PROHIBITED;

typedef NS_ENUM(NSInteger, UIActivityCategory) {
    UIActivityCategoryAction,
    UIActivityCategoryShare,
} NS_ENUM_AVAILABLE_IOS(7_0) __TVOS_PROHIBITED;

NS_CLASS_AVAILABLE_IOS(6_0) __TVOS_PROHIBITED @interface UIActivity : NSObject

// override methods
@property(class, nonatomic, readonly) UIActivityCategory activityCategory API_AVAILABLE(ios(7.0)); // default is UIActivityCategoryAction.

@property(nonatomic, readonly, nullable) UIActivityType activityType;       // default returns nil. subclass may override to return custom activity type that is reported to completion handler
@property(nonatomic, readonly, nullable) NSString *activityTitle;      // default returns nil. subclass must override and must return non-nil value
@property(nonatomic, readonly, nullable) UIImage *activityImage;       // default returns nil. subclass must override and must return non-nil value

- (BOOL)canPerformWithActivityItems:(NSArray *)activityItems;   // override this to return availability of activity based on items. default returns NO
- (void)prepareWithActivityItems:(NSArray *)activityItems;      // override to extract items and set up your HI. default does nothing

@property(nonatomic, readonly, nullable) UIViewController *activityViewController;   // return non-nil to have view controller presented modally. call activityDidFinish at end. default returns nil
- (void)performActivity;                        // if no view controller, this method is called. call activityDidFinish when done. default calls [self activityDidFinish:NO]

// state method

- (void)activityDidFinish:(BOOL)completed;   // activity must call this when activity is finished
@end

NS_ASSUME_NONNULL_END

#else
#import <ShareSheet/UIActivity.h>
#endif
