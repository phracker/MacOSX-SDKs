//
//  MXHangDiagnostic.h
//  MetricKit
//
//  Copyright (c) 2019 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXDiagnostic.h>
#import <MetricKit/MXCallStackTree.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@class         MXHangDiagnostic
@abstract      An MXDiagnostic subclass that encapsulates hang diagnostic reports.
@discussion    Applications are considered to be "hanging" when they are unable to handle user input responsively.
@discussion    This generally occurs when your applications main thread is blocked.
*/
API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXHangDiagnostic : MXDiagnostic

/*!
@property      callStackTree
@abstract      The application call stack tree associated with the hang.
*/
@property (readonly, strong, nonnull) MXCallStackTree *callStackTree;

/*!
@property      hangDuration
@abstract      Total hang duration for this diagnostic.
@discussion    Dimensioned as NSUnitDuration.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *hangDuration;

@end

NS_ASSUME_NONNULL_END
