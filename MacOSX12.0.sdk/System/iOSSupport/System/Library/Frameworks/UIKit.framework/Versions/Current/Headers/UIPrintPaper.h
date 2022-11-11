#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPrintPaper.h>)
//
//  UIPrintPaper.h
//  UIKit
//
//  Copyright 2010-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(4.2))API_UNAVAILABLE(tvos) NS_SWIFT_UI_ACTOR
@interface UIPrintPaper : NSObject 

+ (UIPrintPaper *)bestPaperForPageSize:(CGSize)contentSize withPapersFromArray:(NSArray<UIPrintPaper *> *)paperList; // for use by delegate. pass in list

@property(readonly) CGSize paperSize;
@property(readonly) CGRect printableRect;

@end

//_____________________________________________

@interface UIPrintPaper(Deprecated_Nonfunctional)
- (CGRect)printRect API_UNAVAILABLE(tvos) ;
@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPrintPaper.h>
#endif
