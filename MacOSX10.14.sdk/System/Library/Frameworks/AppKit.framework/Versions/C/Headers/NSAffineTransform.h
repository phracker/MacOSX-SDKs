/*
        NSAffineTransform.h
        Application Kit
        Copyright (c) 1997-2018, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSAffineTransform.h>

NS_ASSUME_NONNULL_BEGIN

@class NSBezierPath;

@interface NSAffineTransform (NSAppKitAdditions)
// Transform a path
- (NSBezierPath *)transformBezierPath:(NSBezierPath *)path;

// Setting a transform in NSGraphicsContext
- (void)set;
- (void)concat;
@end

NS_ASSUME_NONNULL_END
