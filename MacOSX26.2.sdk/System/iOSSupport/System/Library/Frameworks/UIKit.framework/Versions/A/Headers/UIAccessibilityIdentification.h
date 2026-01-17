#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityIdentification.h>)
//
//  UIAccessibilityIdentification.h
//  UIKit
//
//  Copyright 2010-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIView.h>
#import <UIKit/UIImage.h>
#import <UIKit/UIBarItem.h>
#import <UIKit/UIAlertController.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_UNAVAILABLE(watchos)
@protocol UIAccessibilityIdentification <NSObject>
@required

/*
 A string that identifies the user interface element.
 default == nil
*/
@property(nullable, nonatomic, copy) NSString *accessibilityIdentifier API_AVAILABLE(ios(5.0)) NS_SWIFT_UI_ACTOR;

@end

@interface UIView (UIAccessibility) <UIAccessibilityIdentification>
@end

@interface UIBarItem (UIAccessibility) <UIAccessibilityIdentification>
@end

@interface UIAlertAction (UIAccessibility) <UIAccessibilityIdentification>
@end

@interface UIMenuElement (UIAccessibility) <UIAccessibilityIdentification>
@end

/*
 Defaults to the filename of the image, if available.
 The default identifier for a UIImageView will be the identifier of its UIImage.
 */
API_UNAVAILABLE(watchos)
@interface UIImage (UIAccessibility) <UIAccessibilityIdentification>
@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIAccessibilityIdentification.h>
#endif
