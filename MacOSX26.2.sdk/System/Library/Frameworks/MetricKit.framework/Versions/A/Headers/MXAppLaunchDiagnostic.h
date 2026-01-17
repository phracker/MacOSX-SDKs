//  Copyright (c) 2022 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXDiagnostic.h>
#import <MetricKit/MXCallStackTree.h>


/*!
@class         MXAppLaunchDiagnostic
@abstract      An MXDiagnostic subclass that encapsulates app launch diagnostic reports.
*/
API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(macos, tvos, watchos)
@interface MXAppLaunchDiagnostic : MXDiagnostic

/*!
@property      callStackTree
@abstract      The application call stack tree associated with the app launch.
*/
@property (readonly, strong, nonnull) MXCallStackTree *callStackTree;

/*!
@property      launchDuration
@abstract      Total app launch duration.
@discussion    Dimensioned as NSUnitDuration.
*/
@property (readonly, strong, nonnull) NSMeasurement<NSUnitDuration *> *launchDuration;

@end

