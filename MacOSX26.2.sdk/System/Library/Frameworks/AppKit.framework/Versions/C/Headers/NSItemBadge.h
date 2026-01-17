//
/*
        NSItemBadge.h
        Application Kit
        Copyright (c) 2025, Apple Inc.
        All rights reserved.
*/

#import <AppKit/AppKit.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

@class NSView;

/**
 `NSItemBadge` represents a badge that can be attached to an `NSToolbarItem`.

 This badge provides a way to display small visual indicators, such as counts and text labels, within a toolbar item. Badges can be used to highlight important information,
 such as unread notifications or status indicators.
 */
API_AVAILABLE(macos(26.0)) NS_REFINED_FOR_SWIFT
@interface NSItemBadge : NSObject

/**
 Creates a badge displaying a localized numerical count.
 
 @param count The integer value to localize and display in the badge.
 @return A new NSItemBadge instance with the localized specified count.
 */
+ (NSItemBadge *)badgeWithCount:(NSInteger)count;

/**
 Creates a badge displaying a text.

 @param text The text to be displayed inside the badge.
 @return A new `NSItemBadge` instance with the specified text.
 */
+ (NSItemBadge *)badgeWithText:(NSString *)text;

/**
 Creates a badge styled as an indicator. In this context, an indicator is simply a badge without any text.

 @return A new `NSItemBadge` instance styled as an indicator.
 */
+ (NSItemBadge *)indicatorBadge;

/**
 The text to be displayed within the badge.
 */
@property (readonly, copy) NSString *text;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

