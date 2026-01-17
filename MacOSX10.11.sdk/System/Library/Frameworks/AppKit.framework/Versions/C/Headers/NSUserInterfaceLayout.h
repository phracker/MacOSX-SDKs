/*
    NSUserInterfaceLayout.h
    Application Kit
    Copyright (c) 2015-2015, Apple Inc.
    All rights reserved.
 */

#import <AppKit/AppKitDefines.h>

typedef NS_ENUM(NSInteger, NSUserInterfaceLayoutDirection) {
    NSUserInterfaceLayoutDirectionLeftToRight = 0,
    NSUserInterfaceLayoutDirectionRightToLeft = 1
};

typedef NS_ENUM(NSInteger, NSUserInterfaceLayoutOrientation) {
    NSUserInterfaceLayoutOrientationHorizontal = 0,
    NSUserInterfaceLayoutOrientationVertical = 1
} NS_ENUM_AVAILABLE_MAC(10_9);