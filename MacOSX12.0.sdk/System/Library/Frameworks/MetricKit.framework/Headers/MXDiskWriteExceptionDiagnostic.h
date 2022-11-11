//
//  MXDiskWriteExceptionDiagnostic.h
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
@class         MXDiskWriteExceptionDiagnostic
@abstract      An MXDiagnostic subclass that encapsulates disk write exception reports.
@discussion    Disk write exceptions occur when your application writes data excessively to disk.
*/
API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXDiskWriteExceptionDiagnostic : MXDiagnostic

/*!
@property      callStackTree
@abstract      The application call stack tree associated with the excessive disk writes.
*/
@property (readonly, strong, nonnull) MXCallStackTree *callStackTree;

/*!
@property      totalWritesCaused
@abstract      Total disk writes caused in the scope of this disk write exception.
@discussion    Dimensioned as NSUnitInformationStorage.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitInformationStorage *> *totalWritesCaused;

@end

NS_ASSUME_NONNULL_END
