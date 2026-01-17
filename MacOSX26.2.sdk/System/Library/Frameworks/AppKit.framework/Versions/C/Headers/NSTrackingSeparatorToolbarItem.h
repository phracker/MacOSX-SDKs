/*
        NSTrackingSeparatorToolbarItem.h
        Application Kit
        Copyright (c) 2019-2024, Apple Inc.
        All rights reserved.
*/

#import <AppKit/NSToolbarItem.h>

@class NSSplitView;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

API_AVAILABLE(macos(11.0)) API_UNAVAILABLE(ios)
@interface NSTrackingSeparatorToolbarItem : NSToolbarItem

/**
 Creates a new `NSTrackingSeparatorToolbarItem` and configures it to attempt to visually align with the specified divider of the `splitView`.
 The `splitView` must be in the same window as the toolbar containing this item by the time the toolbar is shown.
 Only vertical `splitViews` are supported.
 */
+ (instancetype)trackingSeparatorToolbarItemWithIdentifier:(NSToolbarItemIdentifier)identifier splitView:(NSSplitView *)splitView dividerIndex:(NSInteger)dividerIndex API_UNAVAILABLE(ios);

/**
 The `splitView` must be in the same window as the toolbar containing this item by the time the toolbar is shown.
 Only vertical `splitViews` are supported.
*/
@property (strong) NSSplitView *splitView API_UNAVAILABLE(ios);

/**
 The specific divider of the `splitView` which will be tracked.
*/
@property NSInteger dividerIndex API_UNAVAILABLE(ios);

@end

NS_HEADER_AUDIT_END(nullability, sendability)
