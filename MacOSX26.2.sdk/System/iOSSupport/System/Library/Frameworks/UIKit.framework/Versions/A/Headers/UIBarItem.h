#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIBarItem.h>)
//
//  UIBarItem.h
//  UIKit
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAppearance.h>
#import <UIKit/UIControl.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class UIImage;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIBarItem : NSObject <NSCoding, UIAppearance>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (nullable instancetype)initWithCoder:(NSCoder *)coder NS_DESIGNATED_INITIALIZER;

@property(nonatomic,getter=isEnabled) BOOL         enabled;      // default is YES
@property(nullable, nonatomic,copy)             NSString    *title;        // default is nil
@property(nullable, nonatomic,strong)           UIImage     *image;        // default is nil
@property(nullable, nonatomic,strong)           UIImage     *landscapeImagePhone API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos); // default is nil

// Higher-resolution version of the standard image. Default is nil. Used for rendering assistive UI (e.g. for users with visual impairments who need large text). If not provided, the system may attempt to generate an image based on the standard image (for instance, by rasterizing matching PDF representations at a higher resolution).
@property(nullable, nonatomic,strong)           UIImage     *largeContentSizeImage API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos);

@property(nonatomic)                  UIEdgeInsets imageInsets;  // default is UIEdgeInsetsZero
@property(nonatomic)                  UIEdgeInsets landscapeImagePhoneInsets API_AVAILABLE(ios(5.0)) API_UNAVAILABLE(tvos);  // default is UIEdgeInsetsZero. These insets apply only when the landscapeImagePhone property is set.
@property(nonatomic)                  UIEdgeInsets largeContentSizeImageInsets API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos); // default is UIEdgeInsetsZero. These insets apply only when the largeContentSizeImage property is set.
@property(nonatomic)                  NSInteger    tag;          // default is 0

/* You may specify the font, text color, and shadow properties for the title in the text attributes dictionary, using the keys found in NSAttributedString.h.
 */
- (void)setTitleTextAttributes:(nullable NSDictionary<NSAttributedStringKey,id> *)attributes forState:(UIControlState)state API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;
- (nullable NSDictionary<NSAttributedStringKey,id> *)titleTextAttributesForState:(UIControlState)state API_AVAILABLE(ios(5.0)) UI_APPEARANCE_SELECTOR;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIBarItem.h>
#endif
