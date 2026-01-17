//
//  MXCrashDiagnostic.h
//  MetricKit
//
//  Copyright (c) 2019 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXDiagnostic.h>
#import <MetricKit/MXCallStackTree.h>
#import <MetricKit/MXCrashDiagnosticObjectiveCExceptionReason.h>

NS_ASSUME_NONNULL_BEGIN

/*!
@class         MXCrashDiagnostic
@abstract      An MXDiagnostic subclass that encapsulates crash reports.
@discussion    See "Analyzing a Crash Report" for more information on crash diagnostics.
*/
API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXCrashDiagnostic : MXDiagnostic


/*!
 @property      callStackTree
 @abstract      The application call stack tree associated with this crash.
 @discussion    This call stack tree includes those stack frames present at the time of the crash.
 */
@property (readonly, strong, nonnull) MXCallStackTree *callStackTree;

/*!
@property      terminationReason
@abstract      The termination reason associated with this crash.
@discussion    Exit reason information specified when a process is terminated. Key system components, both inside and outside of a process, will terminate the process upon encountering a fatal error (e.g. a bad code signature, a missing dependent library, or accessing privacy sensitive information without the proper entitlement).
*/
@property (readonly, strong, nullable) NSString *terminationReason;

/*!
@property      virtualMemoryRegionInfo
@abstract      Details about memory that the app incorrectly accessed in relation to other sections of the app’s virtual memory address space.
@discussion    This property is set when a bad memory access crash occurs.
*/
@property (readonly, strong, nullable) NSString *virtualMemoryRegionInfo;

/*!
@property      exceptionType
@abstract      The name of the Mach exception that terminated the app.
@see           sys/exception_types.h
*/
@property (readonly, strong, nullable) NSNumber *exceptionType;

/*!
@property      exceptionCode
@abstract      Processor specific information about the exception encoded into one or more 64-bit hexadecimal numbers
@see           sys/exception_types.h
*/
@property (readonly, strong, nullable) NSNumber *exceptionCode;


/*!
@property      signal
@abstract      The signal associated with this crash.
@see           sys/signal.h
*/
@property (readonly, strong, nullable) NSNumber *signal;

/*!
@property      exceptionReason
@abstract      The MXCrashDiagnosticObjectiveCExceptionReason object associated with this crash.
@see           <MetricKit/MXCrashDiagnosticObjectiveCExceptionReason.h>
*/
@property (readonly, strong, nullable) MXCrashDiagnosticObjectiveCExceptionReason *exceptionReason API_AVAILABLE(macos(14.0), ios(17.0)) API_UNAVAILABLE(tvos, watchos);

@end

NS_ASSUME_NONNULL_END
