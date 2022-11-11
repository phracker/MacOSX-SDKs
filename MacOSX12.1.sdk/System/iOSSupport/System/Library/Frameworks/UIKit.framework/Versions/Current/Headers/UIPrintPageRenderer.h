#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPrintPageRenderer.h>)
//
//  UIPrintPageRenderer.h
//  UIKit
//
//  Copyright 2010-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPrintFormatter;

API_AVAILABLE(ios(14.5)) typedef NS_ENUM(NSInteger, UIPrintRenderingQuality) {
    /* Renders the printing at the best possible quality, regardless of speed.
     */
    UIPrintRenderingQualityBest,

    /* Sacrifices the least possible amount of rendering quality for speed to maintain a responsive user interface. This option should be used only after establishing that best quality rendering does indeed make the user interface unresponsive.
     */
    UIPrintRenderingQualityResponsive
};

UIKIT_EXTERN API_AVAILABLE(ios(4.2)) API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIPrintPageRenderer : NSObject

@property(nonatomic) CGFloat   headerHeight;   // top of contentRect from printableRect
@property(nonatomic) CGFloat   footerHeight;   // bottom of contentRect from printableRect

@property(nonatomic,readonly) CGRect paperRect;      // complete paper rect. origin is (0,0)
@property(nonatomic,readonly) CGRect printableRect;  // imageable area inside paper rect

@property(nonatomic,readonly) NSInteger numberOfPages;  // override point. page count. default is maximum page count needed for all formatters or 0

@property(nullable,atomic,copy) NSArray<UIPrintFormatter *> *printFormatters;
- (nullable NSArray<UIPrintFormatter *> *)printFormattersForPageAtIndex:(NSInteger)pageIndex;
- (void)addPrintFormatter:(UIPrintFormatter *)formatter startingAtPageAtIndex:(NSInteger)pageIndex;

/* If the print sheet is unresponsive or sluggish due to the time is takes you to fully render a page,
   you can override this method and read from requestedPrintRenderQuality to determine if the print operation prefers speed over fidelity.
   Please see the comments for UIPrintRenderingQuality. Most applications render each page fast enough and do not need to override this method.
   Return value is the quality you current actually used for the rendering.
   Returns UIPrintRenderingQualityBest by default.
 */
- (UIPrintRenderingQuality)currentRenderingQualityForRequestedRenderingQuality:(UIPrintRenderingQuality)requestedRenderingQuality NS_SWIFT_NAME(currentRenderingQuality(forRequested:)) API_AVAILABLE(ios(14.5));

- (void)prepareForDrawingPages:(NSRange)range;     // override point. default does nothing. called before requesting a set of pages to draw

- (void)drawPageAtIndex:(NSInteger)pageIndex inRect:(CGRect)printableRect;                         // override point. may be called from non-main thread.  calls the various draw methods below.
- (void)drawPrintFormatter:(UIPrintFormatter *)printFormatter forPageAtIndex:(NSInteger)pageIndex; // override point. calls each formatter to draw for that page. subclassers must call super.
- (void)drawHeaderForPageAtIndex:(NSInteger)pageIndex  inRect:(CGRect)headerRect;                  // override point. default does nothing
- (void)drawContentForPageAtIndex:(NSInteger)pageIndex inRect:(CGRect)contentRect;                 // override point. default does nothing
- (void)drawFooterForPageAtIndex:(NSInteger)pageIndex  inRect:(CGRect)footerRect;                  // override point. default does nothing

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPrintPageRenderer.h>
#endif
