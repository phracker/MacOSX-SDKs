#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITextDragPreviewRenderer.h>)
//
//  UITextDragPreviewRenderer.h
//  UIKit
//
//  Copyright © 2017-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/NSLayoutManager.h>

@class UIImage;

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UITextDragPreviewRenderer : NSObject

- (instancetype)initWithLayoutManager:(NSLayoutManager*)layoutManager range:(NSRange)range;
- (instancetype)initWithLayoutManager:(NSLayoutManager*)layoutManager range:(NSRange)range unifyRects:(BOOL)unifyRects NS_DESIGNATED_INITIALIZER;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@property (nonatomic, readonly) NSLayoutManager *layoutManager;
@property (nonatomic, readonly) UIImage *image;
@property (nonatomic, readonly) CGRect firstLineRect;
@property (nonatomic, readonly) CGRect bodyRect;
@property (nonatomic, readonly) CGRect lastLineRect;

- (void)adjustFirstLineRect:(inout CGRect*)firstLineRect bodyRect:(inout CGRect*)bodyRect lastLineRect:(inout CGRect*)lastLineRect textOrigin:(CGPoint)origin;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UITextDragPreviewRenderer.h>
#endif
