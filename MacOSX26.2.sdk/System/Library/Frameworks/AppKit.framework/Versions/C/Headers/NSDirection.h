/*
 NSDirection.h
 Application Kit
 Copyright (c) 2024-2024, Apple Inc.
 All rights reserved.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The absolute directions on the horizontal axis.
typedef NS_OPTIONS(NSUInteger, NSHorizontalDirections) {
    /// The left direction.
    NSHorizontalDirectionsLeft = (1 << 0),
    /// The right direction.
    NSHorizontalDirectionsRight = (1 << 1),
    /// All horizontal directions (left and right).
    NSHorizontalDirectionsAll = (NSHorizontalDirectionsLeft | NSHorizontalDirectionsRight),
} NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

/// The directions on the vertical axis.
typedef NS_OPTIONS(NSUInteger, NSVerticalDirections) {
    /// The upwards direction.
    NSVerticalDirectionsUp = (1 << 0),
    /// The downward direction.
    NSVerticalDirectionsDown = (1 << 1),
    /// All vertical directions (up and down).
    NSVerticalDirectionsAll = (NSVerticalDirectionsUp | NSVerticalDirectionsDown),
} NS_REFINED_FOR_SWIFT API_AVAILABLE(macos(15.0));

NS_ASSUME_NONNULL_END
