/*
    NSMagnificationGestureRecognizer.h
    Application Kit
    Copyright (c) 2013-2024, Apple Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/NSGestureRecognizer.h>
#import <AppKit/AppKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

API_AVAILABLE(macos(10.10))
@interface NSMagnificationGestureRecognizer : NSGestureRecognizer

@property CGFloat magnification;

@end

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
