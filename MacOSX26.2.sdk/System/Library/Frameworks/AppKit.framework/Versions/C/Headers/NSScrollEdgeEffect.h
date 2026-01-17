/*
 NSScrollEdgeEffect.h
 Application Kit
 Copyright (c) 2025, Apple Inc.
 All rights reserved.
 */

#import <AppKit/AppKitDefines.h>
#import <Foundation/Foundation.h>

APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST
NS_ASSUME_NONNULL_BEGIN

/// Styles for a scroll view’s edge effect.
NS_SWIFT_UI_ACTOR
API_AVAILABLE(macos(26.1))
__attribute__((objc_subclassing_restricted))
@interface NSScrollEdgeEffectStyle : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The automatic scroll edge effect style.
@property (class, strong, readonly) NSScrollEdgeEffectStyle *automaticStyle;

/// A scroll edge effect with a soft edge.
@property (class, strong, readonly) NSScrollEdgeEffectStyle *softStyle;

/// A scroll edge effect with a hard cutoff.
@property (class, strong, readonly) NSScrollEdgeEffectStyle *hardStyle;

@end

NS_ASSUME_NONNULL_END
API_UNAVAILABLE_END
