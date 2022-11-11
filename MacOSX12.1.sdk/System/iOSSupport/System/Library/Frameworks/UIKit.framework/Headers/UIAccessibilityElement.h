#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityElement.h>)
//
//  UIAccessibilityElement.h
//  UIAccessibility
//
//  Copyright (c) 2008-2018 Apple Inc. All rights reserved.
//

#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIAccessibilityConstants.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIAccessibilityIdentification.h>

NS_ASSUME_NONNULL_BEGIN

/*
 UIAccessibilityElement
 
 Instances of this class can be used as "fake" accessibility elements.
 An accessibility container (see UIAccessibility.h) can create and vend instances
 of UIAccessibilityElement to cover for user interface items that are not
 backed by a UIView (for example: painted text or icon).
 */

UIKIT_EXTERN API_AVAILABLE(ios(3.0)) NS_SWIFT_UI_ACTOR
@interface UIAccessibilityElement : UIResponder<UIAccessibilityIdentification>

// initialize with the accessibility container that contains this element
- (instancetype)initWithAccessibilityContainer:(id)container;

@property (nullable, nonatomic, weak) id accessibilityContainer;
@property (nonatomic, assign) BOOL isAccessibilityElement;
@property (nullable, nonatomic, strong) NSString *accessibilityLabel;
@property (nullable, nonatomic, strong) NSString *accessibilityHint;
@property (nullable, nonatomic, strong) NSString *accessibilityValue;
@property (nonatomic, assign) CGRect accessibilityFrame;
@property (nonatomic, assign) UIAccessibilityTraits accessibilityTraits;

// When set, -[UIAccessibilityElement accessibilityFrame] will automatically adjust for the container's frame.
// This can be useful when the element is a descendant of a scroll view, for instance.
@property (nonatomic, assign) CGRect accessibilityFrameInContainerSpace API_AVAILABLE(ios(10.0));

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIAccessibilityElement.h>
#endif
