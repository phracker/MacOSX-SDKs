#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPasteConfigurationSupporting.h>)
//
//  UIPasteConfigurationSupporting.h
//  UIKit
//
//  Copyright © 2007-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class UIPasteConfiguration;

UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(tvos, watchos) NS_SWIFT_UI_ACTOR
@protocol UIPasteConfigurationSupporting <NSObject>

@property (nonatomic, copy, nullable) UIPasteConfiguration *pasteConfiguration;

@optional
- (void)pasteItemProviders:(NSArray<NSItemProvider *> *)itemProviders;
- (BOOL)canPasteItemProviders:(NSArray<NSItemProvider *> *)itemProviders;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPasteConfigurationSupporting.h>
#endif
