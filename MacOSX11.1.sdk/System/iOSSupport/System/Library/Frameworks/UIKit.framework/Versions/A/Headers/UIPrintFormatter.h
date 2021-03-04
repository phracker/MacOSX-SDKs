#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPrintFormatter.h>)
//
//  UIPrintFormatter.h
//  UIKit
//
//  Copyright 2010-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIStringDrawing.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPrintPageRenderer;
@class UIView, UIFont, UIColor;

UIKIT_EXTERN API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(tvos) @interface UIPrintFormatter : NSObject <NSCopying>

@property(nullable,nonatomic,readonly,weak) UIPrintPageRenderer *printPageRenderer API_UNAVAILABLE(tvos); // default is nil. set when formatter added to a print page renderer
- (void)removeFromPrintPageRenderer API_UNAVAILABLE(tvos);

@property(nonatomic) CGFloat      maximumContentHeight API_UNAVAILABLE(tvos);      // default is 0.0. limits content to width
@property(nonatomic) CGFloat      maximumContentWidth API_UNAVAILABLE(tvos);       // default is 0.0. limits content to height
@property(nonatomic) UIEdgeInsets contentInsets API_DEPRECATED_WITH_REPLACEMENT("perPageContentInsets", ios(4.2, 10.0)) API_UNAVAILABLE(tvos);
                                                                               // default is UIEdgeInsetsZero. from edge of printableRect. applies to whole content. bottom inset unused
                                                                               // Deprecated in favor of perPageContentInsets which produces better output
@property(nonatomic) UIEdgeInsets perPageContentInsets API_UNAVAILABLE(tvos);      // default is UIEdgeInsetsZero from edge of the page.  applies to content on each page (each edge applies to each page)

@property(nonatomic)          NSInteger startPage API_UNAVAILABLE(tvos);           // default is NSNotFound
@property(nonatomic,readonly) NSInteger pageCount API_UNAVAILABLE(tvos);           // calculated

- (CGRect)rectForPageAtIndex:(NSInteger)pageIndex API_UNAVAILABLE(tvos);                     // returns empty rect if index out of range
- (void)drawInRect:(CGRect)rect forPageAtIndex:(NSInteger)pageIndex API_UNAVAILABLE(tvos);   // override point to add custom drawing

@end

//______________________________

UIKIT_EXTERN API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(tvos) @interface UISimpleTextPrintFormatter : UIPrintFormatter {
}

- (instancetype)initWithText:(NSString *)text;
- (instancetype)initWithAttributedText:(NSAttributedString *)attributedText API_AVAILABLE(ios(7.0));

@property(nullable,nonatomic,copy)     NSString       *text;                   // cannot change once drawing started
@property(nullable,nonatomic,copy)     NSAttributedString *attributedText API_AVAILABLE(ios(7.0));
@property(nullable,nonatomic,strong)   UIFont         *font;
@property(nullable,nonatomic,strong)   UIColor        *color;
@property(nonatomic)          NSTextAlignment textAlignment;

@end

//______________________________

UIKIT_EXTERN API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(tvos) @interface UIMarkupTextPrintFormatter : UIPrintFormatter {
}

- (instancetype)initWithMarkupText:(NSString *)markupText;
@property(nullable,nonatomic,copy) NSString *markupText;                    // cannot change once drawing started

@end

//______________________________

UIKIT_EXTERN API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(tvos) @interface UIViewPrintFormatter : UIPrintFormatter 

@property(nonatomic,readonly) UIView *view;

@end

//______________________________

@interface UIView(UIPrintFormatter)

- (UIViewPrintFormatter *)viewPrintFormatter API_UNAVAILABLE(tvos);                                          // returns a new print formatter each time
- (void)drawRect:(CGRect)rect forViewPrintFormatter:(UIViewPrintFormatter *)formatter API_UNAVAILABLE(tvos);     // default calls -drawRect:

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPrintFormatter.h>
#endif
