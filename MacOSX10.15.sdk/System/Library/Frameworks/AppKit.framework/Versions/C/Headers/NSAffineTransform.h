/*
        NSAffineTransform.h
        Application Kit
        Copyright (c) 1997-2019, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSAffineTransform.h>

NS_ASSUME_NONNULL_BEGIN
API_UNAVAILABLE_BEGIN(ios)

@class NSBezierPath;

@interface NSAffineTransform (NSAppKitAdditions)
// Transform a path
- (NSBezierPath *)transformBezierPath:(NSBezierPath *)path;

// Setting a transform in NSGraphicsContext
- (void)set;
- (void)concat;
@end

API_UNAVAILABLE_END
NS_ASSUME_NONNULL_END
