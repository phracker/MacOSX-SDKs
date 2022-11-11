//
//  MXDiagnosticPayload.h
//  MetricKit
//
//  Copyright (c) 2019 Apple Inc.
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <os/availability.h>
#import <MetricKit/MXDiagnostic.h>
#import <MetricKit/MXMetaData.h>
#import <MetricKit/MXCPUExceptionDiagnostic.h>
#import <MetricKit/MXDiskWriteExceptionDiagnostic.h>
#import <MetricKit/MXHangDiagnostic.h>
#import <MetricKit/MXCrashDiagnostic.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 @class         MXDiagnosticPayload
 @abstract      A wrapper class which contains a diagnostic payload and associated properties of that payload.
 @discussion    MXDiagnosticPayload encapsulates currently supported diagnostics that can be vended by MetricKit. Arrays of MXDiangostic subclasses on MXDiagnosticPayload are nullable. If an array of MXDiagnostic subclasses is nil, it indicates that the diagnostics are not available for this payload.
 @discussion    MXDiagnosticPayload exposes a convenience function, JSONRepresentation, to convert the contents of the payload to a human readable JSON. This should be used in conjunction with other APIs that accept NSData.
 @discussion    An MXDiagnosticPayload contains diagnostics that cover a 24 hour period of application usage. The properties timeStampBegin and timeStampEnd should be used to determine which time range the payload covers.
 @discussion    It is possible for an MXDiagnosticPayload to cover regions of time where an application was updated, and thus each MXDiagnostic subclass will contain its own application version string. This is in contrast to MXMetricPayload, where only the latest application version string is included as metadata of the payload. Each MXDiagnostic subclass application version string should be inspected prior to processing.
 */
API_AVAILABLE(ios(14.0), macos(12.0)) API_UNAVAILABLE(tvos, watchos)
@interface MXDiagnosticPayload : NSObject <NSSecureCoding>

/*!
@property      cpuExceptionDiagnostics
@abstract      An array containing CPU exception diagnostics for this application.
*/
@property (readonly, strong, nullable) NSArray<MXCPUExceptionDiagnostic *> *cpuExceptionDiagnostics;

/*!
@property      diskWriteExceptionDiagnostics
@abstract      An array containing disk write exception diagnostics for this application.
*/
@property (readonly, strong, nullable) NSArray<MXDiskWriteExceptionDiagnostic *> *diskWriteExceptionDiagnostics;

/*!
@property      hangDiagnostics
@abstract      An array containing hang diagnostics for this application.
*/
@property (readonly, strong, nullable) NSArray<MXHangDiagnostic *> *hangDiagnostics;

/*!
@property      crashDiagnostics
@abstract      An array containing crash diagnostics for this application.
*/
@property (readonly, strong, nullable) NSArray<MXCrashDiagnostic *> *crashDiagnostics;

/*!
 @property      timeStampBegin
 @abstract      An NSDate object that indicates the start time for which the payload was generated.
 */
@property (readonly, strong, nonnull) NSDate *timeStampBegin;

/*!
 @property      timeStampEnd
 @abstract      An NSDate object that indicates the end time for which the payload was generated.
 */
@property (readonly, strong, nonnull) NSDate *timeStampEnd;

/*!
 @method        JSONRepresentation
 @abstract      Convenience method to return a JSON representation of this diagnostic payload.
 @result        An NSData object containing the JSON representation
 */
- (NSData *)JSONRepresentation;

/*!
 @method        dictionaryRepresentation
 @abstract      Convenience method to return a NSDictionary representation of this diagnostic payload.
 @result        An NSDictionary object containing the dictionary representation
 */
- (NSDictionary *)dictionaryRepresentation;

@end

NS_ASSUME_NONNULL_END
