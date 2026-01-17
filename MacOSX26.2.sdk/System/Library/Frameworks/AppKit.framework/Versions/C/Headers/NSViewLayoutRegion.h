/*
    NSViewLayoutRegion.h
    Application Kit
    Copyright (c) 2025, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSView.h>
#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

typedef NS_ENUM(NSInteger, NSViewLayoutRegionAdaptivityAxis) {
    NSViewLayoutRegionAdaptivityAxisNone,
    NSViewLayoutRegionAdaptivityAxisHorizontal,
    NSViewLayoutRegionAdaptivityAxisVertical,
} API_AVAILABLE(macos(26.0)) NS_REFINED_FOR_SWIFT;

API_AVAILABLE(macos(26.0)) NS_REFINED_FOR_SWIFT
@interface NSViewLayoutRegion : NSObject

+ (NSViewLayoutRegion *)safeAreaLayoutRegionWithCornerAdaptation:(NSViewLayoutRegionAdaptivityAxis)adaptivityAxis;
+ (NSViewLayoutRegion *)marginsLayoutRegionWithCornerAdaptation:(NSViewLayoutRegionAdaptivityAxis)adaptivityAxis;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

@interface NSView (LayoutRegions)
- (NSLayoutGuide *)layoutGuideForLayoutRegion:(NSViewLayoutRegion *)layoutRegion NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0));
- (NSEdgeInsets)edgeInsetsForLayoutRegion:(NSViewLayoutRegion *)layoutRegion NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0));
- (NSRect)rectForLayoutRegion:(NSViewLayoutRegion *)layoutRegion NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(26.0));
@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
