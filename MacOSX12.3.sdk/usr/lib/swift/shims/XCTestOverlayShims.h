//===--- XCTestOverlayShims.h -----------------------------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_STDLIB_SHIMS_XCTEST_OVERLAY_H
#define SWIFT_STDLIB_SHIMS_XCTEST_OVERLAY_H

#define _SWIFT_XCTEST_DEPRECATED __attribute((deprecated("The _SwiftXCTestOverlayShims module is obsolete. Please stop importing it.")))

@import Foundation;

@class XCTestCase;

NS_ASSUME_NONNULL_BEGIN

_SWIFT_XCTEST_DEPRECATED
XCTestCase *_XCTCurrentTestCase(void);

_SWIFT_XCTEST_DEPRECATED
NSDictionary<NSString *, NSString *> * _Nullable
_XCTRunThrowableBlockBridge(void (^ _Nonnull NS_NOESCAPE block)());

_SWIFT_XCTEST_DEPRECATED
extern NSString * XCTActivityTypeUserCreated;

@protocol XCTActivity;
@class XCTContext;

_SWIFT_XCTEST_DEPRECATED
XCTContext *_XCTContextCurrent(void);

_SWIFT_XCTEST_DEPRECATED
BOOL _XCTContextShouldStartActivity(XCTContext *context, NSString *activityType);

_SWIFT_XCTEST_DEPRECATED
id<XCTActivity> _XCTContextWillStartActivity(XCTContext *context, NSString *name, NSString *activityType);

_SWIFT_XCTEST_DEPRECATED
void _XCTContextDidFinishActivity(XCTContext *context, id<XCTActivity> activity);

NS_ASSUME_NONNULL_END

#endif // SWIFT_STDLIB_SHIMS_XCTEST_OVERLAY_H

