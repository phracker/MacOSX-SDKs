//
//  MXCPUExceptionDiagnostic.h
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
@class         MXCPUExceptionDiagnostic
@abstract      An MXDiagnostic subclass that encapsulates CPU exception diagnostic reports.
@discussion    CPU exceptions occur when your application consumes excessive CPU time in a short period of time.
@discussion    CPU exceptions can be both fatal and non-fatal to your application.
*/
API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXCPUExceptionDiagnostic : MXDiagnostic


/*!
 @property      callStackTree
 @abstract      The application call stack tree associated with the excessive CPU consumption.
 */
@property (readonly, strong, nonnull) MXCallStackTree *callStackTree;

/*!
@property      totalCPUTime
@abstract      Total CPU time consumed in the scope of this CPU exception.
@discussion    Dimensioned as NSUnitDuration.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *totalCPUTime;

/*!
@property      totalSampledTime
@abstract      Total time that the application was sampled for during the CPU exception.
@discussion    Dimensioned as NSUnitDuration.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *totalSampledTime;

@end

NS_ASSUME_NONNULL_END
