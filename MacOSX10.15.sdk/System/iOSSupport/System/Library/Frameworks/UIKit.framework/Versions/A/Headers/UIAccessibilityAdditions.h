#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIAccessibilityAdditions.h>)
//
//  UIAccessibilityAdditions.h
//  UIKit
//
//  Copyright (c) 2009-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIPickerView.h>
#import <UIKit/UIScrollView.h>

NS_ASSUME_NONNULL_BEGIN

/* 
  Optionally implement the following methods in a UIPickerView delegate
  in order to provide accessibility information per component. 
  See UIAccessibility.h for more information about hints and labels.
*/

API_UNAVAILABLE(tvos)
@protocol UIPickerViewAccessibilityDelegate <UIPickerViewDelegate>

@optional
- (nullable NSString *)pickerView:(UIPickerView *)pickerView accessibilityLabelForComponent:(NSInteger)component;
- (nullable NSString *)pickerView:(UIPickerView *)pickerView accessibilityHintForComponent:(NSInteger)component;
- (NSArray<NSString *> *)pickerView:(UIPickerView *)pickerView accessibilityUserInputLabelsForComponent:(NSInteger)component API_AVAILABLE(ios(13.0));

// If an object adopting this protocol responds to these methods, the system will try sending them before sending their non-attributed versions.
- (nullable NSAttributedString *)pickerView:(UIPickerView *)pickerView accessibilityAttributedLabelForComponent:(NSInteger)component API_AVAILABLE(ios(11.0));
- (nullable NSAttributedString *)pickerView:(UIPickerView *)pickerView accessibilityAttributedHintForComponent:(NSInteger)component API_AVAILABLE(ios(11.0));
- (NSArray<NSAttributedString *> *)pickerView:(UIPickerView *)pickerView accessibilityAttributedUserInputLabelsForComponent:(NSInteger)component API_AVAILABLE(ios(13.0));

@end

/*
 Provide a custom status string when VoiceOver scrolls with accessibilityScroll:
 For example, in a bookcase user interface that displays a list of books, you can implement 
 this protocol to announce "Showing books 10 through 20".
 By default, VoiceOver will announce "Page X of Y" when scrolling. 
 */
@protocol UIScrollViewAccessibilityDelegate <UIScrollViewDelegate>

@optional
- (nullable NSString *)accessibilityScrollStatusForScrollView:(UIScrollView *)scrollView;

// If an object adopting this protocol responds to this method, the system will try sending it before sending its non-attributed version.
- (nullable NSAttributedString *)accessibilityAttributedScrollStatusForScrollView:(UIScrollView *)scrollView API_AVAILABLE(ios(11.0), tvos(11.0));

@end

/* Invert Colors is often used by those with light or color sensitivities to make bright
   colors darker. However, this has a destructive effect on content like images and videos.
  
   Set accessibilityIgnoresInvertColors to YES on a view that contains content that should
   not be inverted. This effect will apply to the entire subview hierarchy of a view.

   If a view already uses a dark themed design, it may also be appropriate to set this
   property.
 */
@interface UIView (UIAccessibilityInvertColors)
@property(nonatomic) BOOL accessibilityIgnoresInvertColors API_AVAILABLE(ios(11_0), tvos(11_0));
@end


NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIAccessibilityAdditions.h>
#endif
